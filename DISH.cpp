

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
#include <QTimer>


using namespace std;
using namespace boost::filesystem;



DISH::DISH()
{
    trayMenu = new QMenu();
    trayIcon = new QSystemTrayIcon();
    timer = new QTimer();
    getHostsList();
    curl = curl_easy_init();
    trayIcon->show();
    setIcon();
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
    string urlCall = "url";
    dialog urlDialog(urlCall);
    
    if (urlDialog.exec())
    {
        QString url = urlDialog.urlText->text();
        cout << url.toStdString();
    }
}

void DISH::editHosts()
{
    system("sudo gedit //etc//hosts");
}

void DISH::newHosts()
{
    string hosts = "hosts";
    dialog hostsDialog(hosts);
    
    if (hostsDialog.exec())
    {
        QString fileName = hostsDialog.fileNameText->text();
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

void DISH::timeOut()
{
    setIcon();
    QTimer::singleShot(10000, this, SLOT(timeOut()));
}

void DISH::createMenu()
{
    urlSubmenu = trayMenu->addMenu("URL");

     
   changeURLButton = new QAction("&Change URL", urlSubmenu);
    urlSubmenu->addAction(changeURLButton);
    QObject::connect(changeURLButton, SIGNAL(triggered()), this, SLOT(changeURL()));

    
    defaultURLButton = new QAction("&Default URL", urlSubmenu);
    urlSubmenu->addAction(defaultURLButton);
    
    clearCacheButton = new QAction("&Clear cache", urlSubmenu);
    urlSubmenu->addAction(clearCacheButton);
    
    trayMenu->addSeparator();
    

    for (unsigned int x = 0; x < hostsVector.size(); x++)
    {
        userHostsSubMenu = trayMenu->addMenu(hostsVector[x].c_str());
        
        openPuttyButton = new QAction("&Open Putty", userHostsSubMenu);
        userHostsSubMenu->addAction(openPuttyButton);
        
        communityLogsButton = new QAction("&Community Logs", userHostsSubMenu);
        userHostsSubMenu->addAction(communityLogsButton);
        
        //trayMenu->addAction(new QAction(hostsVector[x].c_str(), trayMenu) );
    }
    
    trayMenu->addSeparator();

    adminButton = new QAction("&Make Spice admin", trayMenu);
    trayMenu->addAction(adminButton);
    
    tailProdButton = new QAction("&Tail production", trayMenu);
    trayMenu->addAction(tailProdButton);
   
    
    trayMenu->addSeparator();
    
    
    hostsSubmenu = trayMenu->addMenu("&Hosts");
    
    editButton = new QAction("&Edit current hosts file", hostsSubmenu);
    hostsSubmenu->addAction(editButton);
    QObject::connect(editButton, SIGNAL(triggered()), this, SLOT(editHosts()));
    
    newHostsButton = new QAction("&New hosts file", hostsSubmenu);
    hostsSubmenu->addAction(newHostsButton);
    QObject::connect(newHostsButton, SIGNAL(triggered()), this, SLOT(newHosts()));

    
    refreshButton = new QAction("&Refresh", hostsSubmenu);
    hostsSubmenu->addAction(refreshButton);
    
    hostsDirButton = new QAction("&Go to hosts file directory", hostsSubmenu);
    hostsSubmenu->addAction(hostsDirButton);
    QObject::connect(hostsDirButton, SIGNAL(triggered()), this, SLOT(openHostsDir()));
    
    messageButton = new QAction("&Message", trayMenu);
    trayMenu->addAction(messageButton);
    
    releaseButton = new QAction("&Release", trayMenu);
    trayMenu->addAction(releaseButton);
    
    
    
    settingsSubmenu = trayMenu->addMenu("&Settings");
    
    urlCheckButton = new QAction("&URL", this);
    urlCheckButton->setCheckable(true);
    urlCheckButton->setChecked(true);
    settingsSubmenu->addAction(urlCheckButton);
    
    hostsCheckButton = new QAction("&Hosts files", this);
    hostsCheckButton->setCheckable(true);
    hostsCheckButton->setChecked(true);
    settingsSubmenu->addAction(hostsCheckButton);
    
    tailProdCheckButton = new QAction("&Tail production", this);
    tailProdCheckButton->setCheckable(true);
    tailProdCheckButton->setChecked(true);
    settingsSubmenu->addAction(tailProdCheckButton);
    
    messageCheckButton = new QAction("&Message", this);
    messageCheckButton->setCheckable(true);
    messageCheckButton->setChecked(true);
    settingsSubmenu->addAction(messageCheckButton);
    
    
    releaseCheckButton = new QAction("&Release", this);
    releaseCheckButton->setCheckable(true);
    releaseCheckButton->setChecked(true);
    settingsSubmenu->addAction(releaseCheckButton);
    
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
//    trayIcon->setToolTip(QString("Tool tip test"));    
}

DISH::~DISH()
{
    curl_easy_cleanup(curl);
}
