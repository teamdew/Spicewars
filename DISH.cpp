#include "DISH.h"
#include "rest_query.h"
#include <QApplication>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include "boost/filesystem.hpp"
#include <boost/regex.hpp>
#include <QString>
#include <QLineEdit>
#include <string.h>
#include <QSystemTrayIcon>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>


using namespace std;
//using namespace boost;
using namespace boost::filesystem;

DISH::DISH()
{
    trayMenu = new QMenu(this);
    trayIcon = new QSystemTrayIcon();
    timer = new QTimer();
    getHostsList();
    findCurrentHosts();
    curl = curl_easy_init();
    setCurrentURL();
    setIcon();
    trayIcon->show();
    getCredentials();
}

int DISH::getIssueCount()
{
	Rest rest;
	return rest.rest_query(DESKTOP);
        
}

void DISH::setCurrentURL()
{
    string input = parseFile("config", boost::regex(".*community url.*"));
    vector<string> parsed;
    boost::split(parsed, input, boost::is_any_of(" "));
    current_url = parsed[2];
}

bool DISH::checkServer() 
{   

    long http_code;
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, current_url.c_str());
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 7L);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        //maybe we should ask someone how many redirects there are in spiceworks, it depends on the company
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 5L); 
        curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    }
    
    if ((http_code > 199) && (http_code < 300))
        return true;
    else 
        return false;
}

void DISH::changeURL()
{
    urlDialog showUrlDialog;
    
    if (showUrlDialog.exec())
    {
        QString url = showUrlDialog.urlText->text();
        urlSubmenu->setTitle(url);
        writeToConfigFile(boost::regex(".*community url.*"), "community url", url.toStdString());
        current_url = url.toStdString();
    }
    
    
}

void DISH::findCurrentHosts()
{
    FILE * mainHosts = fopen(MAIN_HOSTS, "r");
    FILE * currentHosts;
    bool foundMatch = false;
    string fileLocation;
    
    for (unsigned int x = 0; x < hostsVector.size(); x++)
    {
        fileLocation = HOSTS_DIR + hostsVector[x];
        currentHosts = fopen(fileLocation.c_str(), "r");
        if(compareFile(mainHosts, currentHosts))
        {
            currentHostsFileName = hostsVector[x];
            foundMatch = true;
            break;
        }
        fclose(currentHosts);
    }
    if (foundMatch == false)
        currentHostsFileName = "hosts.backup";
    fclose(mainHosts);
}

bool DISH::compareFile(FILE* file_compared, FILE* file_checked)
{
    bool diff = 0;
    int N = 65536;
    char* b1 = (char*) calloc (1, N+1);
    char* b2 = (char*) calloc (1, N+1);
    size_t s1, s2;

    do {
        s1 = fread(b1, 1, N, file_compared);
        s2 = fread(b2, 1, N, file_checked);
        
        if (s1 != s2 || memcmp(b1, b2, s1)) {
            diff = 1;
            break;
        }
      } while (!feof(file_compared) || !feof(file_checked));

    free(b1);
    free(b2);
    
    if (diff) return false;
    else return true;
}

void DISH::changeHosts(const QString &hostsName)
{
    path mainHosts = MAIN_HOSTS;
    path currentHosts = HOSTS_DIR + currentHostsFileName;
    path newHosts = HOSTS_DIR + hostsName.toStdString();
    
//    boost::filesystem3::copy_file(mainHosts, currentHosts, copy_option::overwrite_if_exists);
//    boost::filesystem3::copy_file(newHosts, mainHosts, copy_option::overwrite_if_exists);
}

void DISH::editHosts()
{
    system("sudo gedit //etc//hosts");
}

void DISH::newHosts()
{
    newHostsDialog showHostsFileDialog;
    
    if (showHostsFileDialog.exec())
    {
        QString fileName = showHostsFileDialog.fileNameText->text();
        cout << fileName.toStdString();
        
        string command = "sudo gedit //etc//" + fileName.toStdString();
        
        system(command.c_str());
        
        while (!(std::find(hostsVector.begin(), hostsVector.end(), fileName.toStdString()) != hostsVector.end())) 
        {
            hostsVector.clear();
            getHostsList();
        } 
//        else {
//            
//        }

//        free (trayMenu);
//        trayMenu = new QMenu(this);
      
//        trayMenu
//        trayMenu->clear();
        createMenu();
        trayIcon->setContextMenu(trayMenu);
//        setIcon();
        
  //      trayMenu->clear();
    //    createMenu();
      // DISH();
    }
}

void DISH::openHostsDir()
{
    system("gnome-open //etc");
}

void DISH::getHostsList()
{
    path dir_path = path (HOSTS_DIR);
    directory_iterator end_itr;
    //prevents matches for hosts, hosts~ (or any other modified hosts,, hosts.deny and hosts.allow
    boost::regex re("^hosts\.(?!allow|deny).*(?<!~)");

    for (directory_iterator itr(dir_path); itr != end_itr; ++itr)
        if(is_regular_file(itr->status())  && boost::regex_match(itr->path().filename().c_str(), re))
            hostsVector.push_back(itr->path().filename().c_str());
        
}

void DISH::toggleMenu(QCheckBox* checkBox, QMenu* menu)
{
    if(checkBox->isChecked())
        menu->menuAction()->setVisible(true);
    else
        menu->menuAction()->setVisible(false);
}

void DISH::toggleAction(QCheckBox *checkBox, QAction* action)
{
    if(checkBox->isChecked())
        action->setVisible(true);
    else
        action->setVisible(false);
}

void DISH::settings()
{
    settingsDialog showSettingsDialog;
    
    if (showSettingsDialog.exec())
    {
        
        if (showSettingsDialog.updated == true)
        {
            toggleMenu(showSettingsDialog.urlCheckBox, urlSubmenu);
            toggleAction(showSettingsDialog.urlCheckBox, separatorsVector[0]);

            toggleAction(showSettingsDialog.hostsFilesCheckBox, separatorsVector[1]);
            
            for (unsigned int x = 0; x < hostsMenusToHideVector.size(); x++)
            {
                toggleMenu(showSettingsDialog.hostsFilesCheckBox, hostsMenusToHideVector[x]);
            }
            toggleAction(showSettingsDialog.hostsFilesCheckBox,  separatorsVector[2]);
            toggleAction(showSettingsDialog.hostsFilesCheckBox, adminButton);
            toggleMenu(showSettingsDialog.hostsFilesCheckBox, hostsSubmenu);
                
            toggleAction(showSettingsDialog.prodLogCheckBox, tailProdButton);

            toggleAction(showSettingsDialog.messageCheckBox, messageButton);
            
            toggleAction(showSettingsDialog.releaseCheckBox, releaseButton);
            
             QString username = showSettingsDialog.getUsername()->text();
             QString password = showSettingsDialog.getPassword()->text();
             
             if(showSettingsDialog.urlCheckBox->isChecked())
                writeToConfigFile(boost::regex(".*Url Checkbox.*"), "Url Checkbox", "1");
             else
                writeToConfigFile(boost::regex(".*Url Checkbox.*"), "Url Checkbox", "0");
             
             if(showSettingsDialog.hostsFilesCheckBox->isChecked())
                writeToConfigFile(boost::regex(".*Hosts Checkbox.*"), "Hosts Checkbox", "1");
             else
                writeToConfigFile(boost::regex(".*Hosts Checkbox.*"), "Hosts Checkbox", "0");
             
             if(showSettingsDialog.prodLogCheckBox->isChecked())
                writeToConfigFile(boost::regex(".*Prod Log Checkbox.*"), "Prod Log Checkbox", "1");
             else
                writeToConfigFile(boost::regex(".*Prod Log Checkbox.*"), "Prod Log Checkbox", "0");
             
             if(showSettingsDialog.messageCheckBox->isChecked())
                writeToConfigFile(boost::regex(".*Message Checkbox.*"), "Message Checkbox", "1");
             else
                writeToConfigFile(boost::regex(".*Message Checkbox.*"), "Message Checkbox", "0");
             
             if(showSettingsDialog.releaseCheckBox->isChecked())
                writeToConfigFile(boost::regex(".*Release Checkbox.*"), "Release Checkbox", "1");
             else
                writeToConfigFile(boost::regex(".*Release Checkbox.*"), "Release Checkbox", "0");
      
             
             if(username.toStdString() != "" && password.toStdString() != "")
             {
                writeToConfigFile(boost::regex(".*putty username.*"), "putty username", username.toStdString());
                writeToConfigFile(boost::regex(".*putty password.*"), "putty password", password.toStdString());
                
                getCredentials();
             }
             
        }
    }
}

void DISH::writeToConfigFile(boost::regex re, string key, string replacement)
{
    ifstream input("config");
    ofstream output("config.backup");
    string line;
    bool found = false;
    
    boost::regex whitespace("\s*");
    
    while(input.good())
    {
        getline(input, line);
        if(boost::regex_match(line, re))
        {
                found = true;
                line = key + ": " + replacement;
        }
        
        if(!boost::regex_match(line, whitespace) )
                output << line << endl;
                 
    }
    
    if(!found)
    {
        output << key + ": " + replacement;
    }
    
    
    output.close();
    input.close();
    boost::filesystem3::copy_file("config.backup", "config", copy_option::overwrite_if_exists);
    boost::filesystem3::remove("config.backup");
    

}

void DISH::timeOut()
{
    setIcon();
    QTimer::singleShot(10000, this, SLOT(timeOut()));
}

void DISH::openPutty()
{ 
    string input = parseFile(MAIN_HOSTS, boost::regex(".*community.*"));
    vector<string> parsed;
    boost::split(parsed, input, boost::is_any_of(" "));
    string command = "putty -ssh -l " + username + " -pw " + password + " " + parsed[0];
    
    system(command.c_str());
}

void DISH::openCommunityLogs()
{
    string input = parseFile(MAIN_HOSTS, boost::regex(".*community.*"));
    vector<string> parsed;
    boost::split(parsed, input, boost::is_any_of(" "));
    string command = "putty -ssh -l " + username + " -pw " + password + " " + parsed[0] + " -t -m scripts//tail.sh";

    system(command.c_str());
    
}

void DISH::getCredentials()
{
     string input = parseFile(CONFIG, boost::regex("putty username.*"));
     
     vector<string> parsed;
     boost::split(parsed, input, boost::is_any_of(" "));
     username = parsed.at(parsed.size() - 1);
     
     input = parseFile(CONFIG, boost::regex("putty password.*"));
     
     boost::split(parsed, input, boost::is_any_of(" "));
     password = parsed.at(parsed.size() - 1);
}

string DISH::parseFile(string location, boost::regex re)
{
    ifstream myFile(location.c_str());
    string input;
    bool found = false;
    
    while(!found && getline(myFile, input))
    {
            if(boost::regex_match(input, re))
                found = true;
    }
    
    return input;
}

void DISH::makeSpiceAdmin()
{
    
    string input = parseFile(MAIN_HOSTS, boost::regex(".*community.*"));
    vector<string> parsed;
    boost::split(parsed, input, boost::is_any_of(" ")); 
    
    string command = "putty -ssh -l " + username + " -pw " + password + " " + parsed[0] + " -t -m scripts//spiceadmin.sh";
    
    system(command.c_str());
}

void DISH::flushCache()
{
    system("gnome-terminal --command 'sh scripts//flush.sh'");
}

void DISH::createMenu()
{
    trayMenu->clear();
    urlSubmenu = trayMenu->addMenu(current_url.c_str());
    urlSubmenu->setFont(QFont ("Arial", 10, QFont::Bold));
     
    changeURLButton = new QAction("&Change URL", this);
    urlSubmenu->addAction(changeURLButton);
    connect(changeURLButton, SIGNAL(triggered()), this, SLOT(changeURL()));

    
    clearCacheButton = new QAction("&Clear cache", this);
    urlSubmenu->addAction(clearCacheButton);
    
    separatorsVector.push_back(trayMenu->addSeparator());
    
    string input = parseFile("config", boost::regex(".*Url Checkbox.*"));
    vector<string> parsed;
    boost::split(parsed, input, boost::is_any_of(" "));
    if (parsed[2] == "1"){
        urlSubmenu->menuAction()->setVisible(true);
         separatorsVector[0]->setVisible(true);
    }
    else{
        urlSubmenu->menuAction()->setVisible(false);
        separatorsVector[0]->setVisible(false);
    }
    
    
    input = parseFile("config", boost::regex(".*Hosts Checkbox.*"));
    boost::split(parsed, input, boost::is_any_of(" "));
    bool includeHosts;
    
    if (parsed[2] == "1")
        includeHosts = true;
    else
        includeHosts = false;
        
    
    for (unsigned int x = 0; x < hostsVector.size(); x++)
    {
        userHostsSubMenu = new QMenu(hostsVector[x].c_str(), this); 
        userHostsActionsVector.push_back(trayMenu->addMenu(userHostsSubMenu));
        hostsMenusToHideVector.push_back(userHostsSubMenu);
        
        openPuttyButton = new QAction("&Open Putty", this);
        userHostsSubMenu->addAction(openPuttyButton);
        QObject::connect(openPuttyButton, SIGNAL(triggered()), this, SLOT(openPutty()));
        
        communityLogsButton = new QAction("&Community Logs", this);
        userHostsSubMenu->addAction(communityLogsButton);
        QObject::connect(communityLogsButton, SIGNAL(triggered()), this, SLOT(openCommunityLogs()));
        
        string hostsFileName = hostsVector[x];
        string hostsFileButtonTitle = "&Switch to " + hostsFileName.substr(6, hostsFileName.length());
        
        mapper = new QSignalMapper(this);        
        changeHostsButton = new QAction(hostsFileButtonTitle.c_str(), this);
        mapper->setMapping(changeHostsButton, hostsFileName.c_str()); 
        connect(changeHostsButton, SIGNAL(triggered()), mapper, SLOT(map()));
        userHostsSubMenu->addAction(changeHostsButton);
        connect(mapper, SIGNAL(mapped(const QString &)), SLOT(changeHosts(const QString &)));
        
        if (includeHosts)
            userHostsSubMenu->menuAction()->setVisible(true);
        else
            userHostsSubMenu->menuAction()->setVisible(false);
    }
    
    separatorsVector.push_back(trayMenu->addSeparator());

    adminButton = new QAction("&Make Spice admin", this);
    trayMenu->addAction(adminButton);
    connect(adminButton, SIGNAL(triggered()), this, SLOT(makeSpiceAdmin()));
    
    hostsSubmenu = trayMenu->addMenu("&Hosts");
    
    editButton = new QAction("&Edit current hosts file", this);
    hostsSubmenu->addAction(editButton);
    connect(editButton, SIGNAL(triggered()), this, SLOT(editHosts()));
    
    newHostsButton = new QAction("&New hosts file", this);
    hostsSubmenu->addAction(newHostsButton);
    connect(newHostsButton, SIGNAL(triggered()), this, SLOT(newHosts()));

    
    refreshButton = new QAction("&Refresh", this);
    hostsSubmenu->addAction(refreshButton);
    
    hostsDirButton = new QAction("&Go to hosts file directory", this);
    hostsSubmenu->addAction(hostsDirButton);
    connect(hostsDirButton, SIGNAL(triggered()), this, SLOT(openHostsDir()));
 
     
    separatorsVector.push_back(trayMenu->addSeparator());
    
    if (includeHosts)
    {
        hostsSubmenu->menuAction()->setVisible(true);
        adminButton->setVisible(true);
        separatorsVector[1]->setVisible(true);
        separatorsVector[2]->setVisible(true);
    }
    else
    {
        hostsSubmenu->menuAction()->setVisible(false);
        adminButton->setVisible(false);
        separatorsVector[1]->setVisible(false);
        separatorsVector[2]->setVisible(false);
    }
    
    tailProdButton = new QAction("&Tail production", this);
    trayMenu->addAction(tailProdButton);
    
    input = parseFile("config", boost::regex(".*Prod Log Checkbox.*"));
    boost::split(parsed, input, boost::is_any_of(" "));
    if (parsed[3] == "1")
        tailProdButton->setVisible(true);
    else
        tailProdButton->setVisible(false);
    

    messageButton = new QAction("&Message", this);
    trayMenu->addAction(messageButton);
    connect(messageButton, SIGNAL(triggered()), this, SLOT(messages()));
    
    input = parseFile("config", boost::regex(".*Message Checkbox.*"));
    boost::split(parsed, input, boost::is_any_of(" "));
    if (parsed[2] == "1")
        messageButton->setVisible(true);
    else
        messageButton->setVisible(false);
   
    //releaseButton = new QAction("&Release", this);
    cout << boost::lexical_cast<std::string>(getIssueCount())  + " open community tickets left" << endl;
    releaseButton = new QAction((boost::lexical_cast<std::string>(getIssueCount())  + " open community tickets left").c_str(), this);
    releaseButton->setFont(QFont ("Arial", 10, QFont::Bold));
    trayMenu->addAction(releaseButton);
    //connect(relButton, SIGNAL(triggered()), this, SLOT(settings()));
    
    input = parseFile("config", boost::regex(".*Release Checkbox.*"));
    boost::split(parsed, input, boost::is_any_of(" "));
    if (parsed[2] == "1")
        releaseButton->setVisible(true);
    else
        releaseButton->setVisible(false);
    
    
    settingsButton = new QAction("&Settings", this);
    trayMenu->addAction(settingsButton);
    connect(settingsButton, SIGNAL(triggered()), this, SLOT(settings()));
    
    
    trayIcon->setToolTip("test test");
    
    
    quit = new QAction("&Quit", this);
    trayMenu->addAction(quit);
    QObject::connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));
    
    timeOut();
}

void DISH::messages()
{
    messageDialog showMessageDialog;
    showMessageDialog.exec();
    
}
//sets the tray icon
void DISH::setIcon()
{
    if(checkServer())
        icon = QIcon(WORKING_PEPPER);
    else
        icon = QIcon(BROKEN_PEPPER);
    
    trayIcon->setIcon(icon);
    trayIcon->setToolTip(tr("toopTIP"));
    trayIcon->setContextMenu(trayMenu);
}

DISH::~DISH()
{
    curl_easy_cleanup(curl);
}
