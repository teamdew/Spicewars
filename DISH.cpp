#include "DISH.h"
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


using namespace std;
//using namespace boost;
using namespace boost::filesystem;

DISH::DISH()
{
    trayMenu = new QMenu();
    trayIcon = new QSystemTrayIcon();
    timer = new QTimer();
    getHostsList();
    curl = curl_easy_init();
    setIcon();
    trayIcon->show();
    getCredentials();
}

bool DISH::checkServer() 
{   

    long http_code;
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "community.spiceworks.com");
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

//still need to do connect for all of the buttons sans Quit
//creates the menu

void DISH::changeURL()
{
    urlDialog showUrlDialog;
    
    if (showUrlDialog.exec())
    {
        QString url = showUrlDialog.urlText->text();
        cout << url.toStdString();
    }
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
    boost::regex re("^hosts.*");

    for (directory_iterator itr(dir_path); itr != end_itr; ++itr)
        if(is_regular_file(itr->status())  && boost::regex_match(itr->path().filename().c_str(), re))
            hostsVector.push_back(itr->path().filename().c_str());
    
}


void DISH::settings()
{
    settingsDialog showSettingsDialog;
    
    if (showSettingsDialog.exec())
    {
        cout << "SETTINGS" << endl;
    }
}

void DISH::timeOut()
{
    setIcon();
    QTimer::singleShot(10000, this, SLOT(timeOut()));
}

void DISH::openPutty()
{ 
    string input = parseFile(CURRENT_HOST, boost::regex(".*community.*"));
    vector<string> parsed;
    boost::split(parsed, input, boost::is_any_of(" "));
    string command = "putty -ssh -l " + username + " -pw " + password + " " + parsed[0];
    
    system(command.c_str());
}

void DISH::openCommunityLogs()
{
    string input = parseFile(CURRENT_HOST, boost::regex(".*community.*"));
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

void DISH::createMenu()
{
    urlSubmenu = trayMenu->addMenu("URL");
    urlSubmenu->setFont(QFont ("Arial", 10, QFont::Bold));

     
    changeURLButton = new QAction("&Change URL", this);
    urlSubmenu->addAction(changeURLButton);
    QObject::connect(changeURLButton, SIGNAL(triggered()), this, SLOT(changeURL()));

    
    clearCacheButton = new QAction("&Clear cache", this);
    urlSubmenu->addAction(clearCacheButton);
    
    trayMenu->addSeparator();
    

    for (unsigned int x = 0; x < hostsVector.size(); x++)
    {
        userHostsSubMenu = trayMenu->addMenu(hostsVector[x].c_str());
        
        openPuttyButton = new QAction("&Open Putty", this);
        userHostsSubMenu->addAction(openPuttyButton);
        QObject::connect(openPuttyButton, SIGNAL(triggered()), this, SLOT(openPutty()));
        
        communityLogsButton = new QAction("&Community Logs", this);
        userHostsSubMenu->addAction(communityLogsButton);
        QObject::connect(communityLogsButton, SIGNAL(triggered()), this, SLOT(openCommunityLogs()));
        
 
    }
    
    trayMenu->addSeparator();

    adminButton = new QAction("&Make Spice admin", this);
    trayMenu->addAction(adminButton); 
    
    hostsSubmenu = trayMenu->addMenu("&Hosts");
    
    editButton = new QAction("&Edit current hosts file", this);
    hostsSubmenu->addAction(editButton);
    QObject::connect(editButton, SIGNAL(triggered()), this, SLOT(editHosts()));
    
    newHostsButton = new QAction("&New hosts file", this);
    hostsSubmenu->addAction(newHostsButton);
    QObject::connect(newHostsButton, SIGNAL(triggered()), this, SLOT(newHosts()));

    
    refreshButton = new QAction("&Refresh", this);
    hostsSubmenu->addAction(refreshButton);
    
    hostsDirButton = new QAction("&Go to hosts file directory", this);
    hostsSubmenu->addAction(hostsDirButton);
    QObject::connect(hostsDirButton, SIGNAL(triggered()), this, SLOT(openHostsDir()));
 
    
    
    trayMenu->addSeparator();
    
    tailProdButton = new QAction("&Tail production", this);
    trayMenu->addAction(tailProdButton);

    messageButton = new QAction("&Message", this);
    trayMenu->addAction(messageButton);
    
    releaseButton = new QAction("&Release", this);
    releaseButton->setFont(QFont ("Arial", 10, QFont::Bold));
    trayMenu->addAction(releaseButton);
    
    
    
    settingsButton = new QAction("&Settings", this);
    trayMenu->addAction(settingsButton);
    QObject::connect(settingsButton, SIGNAL(triggered()), this, SLOT(settings()));
    
//    urlCheckButton = new QAction("&URL", this);
//    urlCheckButton->setCheckable(true);
//    urlCheckButton->setChecked(true);
//    settingsSubmenu->addAction(urlCheckButton);
//    
//    hostsCheckButton = new QAction("&Hosts files", this);
//    hostsCheckButton->setCheckable(true);
//    hostsCheckButton->setChecked(true);
//    settingsSubmenu->addAction(hostsCheckButton);
//    
//    tailProdCheckButton = new QAction("&Production Logs", this);
//    tailProdCheckButton->setCheckable(true);
//    tailProdCheckButton->setChecked(true);
//    settingsSubmenu->addAction(tailProdCheckButton);
//    
//    messageCheckButton = new QAction("&Message", this);
//    messageCheckButton->setCheckable(true);
//    messageCheckButton->setChecked(true);
//    settingsSubmenu->addAction(messageCheckButton);
//    
//    
//    releaseCheckButton = new QAction("&Release", this);
//    releaseCheckButton->setCheckable(true);
//    releaseCheckButton->setChecked(true);
//    settingsSubmenu->addAction(releaseCheckButton);
    
    trayIcon->setToolTip("test test");
    
    
    quit = new QAction("&Quit", this);
//    quit->setToolTip(tr("i is quitting?"));
    trayMenu->addAction(quit);
    QObject::connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));
    
    timeOut();
}

//sets the tray icon
void DISH::setIcon()
{
    if(checkServer())
        icon = QIcon(WORKING_PEPPER);
    else
        icon = QIcon(BROKEN_PEPPER);
    
    trayIcon->setIcon(icon);
    trayIcon->setContextMenu(trayMenu);
}

DISH::~DISH()
{
    curl_easy_cleanup(curl);
}
