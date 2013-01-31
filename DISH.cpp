

#include "DISH.h"
#include <QApplication>
#include <iostream>
#include <fstream>

using namespace std;



DISH::DISH()
{
    trayMenu = new QMenu();
    trayIcon = new QSystemTrayIcon();
}

//bool checkServer() 
//{    
//    return true;
//}

//still need to do connect for all of the buttons sans Quit
//creates the menu

void DISH::editHosts()
{
    system("gedit //etc//hosts");
}
void DISH::createMenu()
{
    
    
        
    
    urlSubmenu = trayMenu->addMenu("URL");
    
    changeURLButton = new QAction("&Change URL", urlSubmenu);
    urlSubmenu->addAction(changeURLButton);
    
    defaultURLButton = new QAction("&Default URL", urlSubmenu);
    urlSubmenu->addAction(defaultURLButton);
    
    clearCacheButton = new QAction("&Clear cache", urlSubmenu);
    urlSubmenu->addAction(clearCacheButton);
    
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
    
    refreshButton = new QAction("&Refresh", hostsSubmenu);
    hostsSubmenu->addAction(refreshButton);
    
    hostsDirButton = new QAction("&Go to hosts file directory", hostsSubmenu);
    hostsSubmenu->addAction(hostsDirButton);
    
    messageButton = new QAction("&Message", trayMenu);
    trayMenu->addAction(messageButton);
    
    releaseButton = new QAction("&Release", trayMenu);
    trayMenu->addAction(releaseButton);
    
    
    
    settingsSubmenu = trayMenu->addMenu("&Settings");
    
    urlCheckButton = new QAction("&URL", settingsSubmenu);
    urlCheckButton->setCheckable(true);
    urlCheckButton->setChecked(true);
    settingsSubmenu->addAction(urlCheckButton);
    
    hostsCheckButton = new QAction("&Hosts files", settingsSubmenu);
    hostsCheckButton->setCheckable(true);
    hostsCheckButton->setChecked(true);
    settingsSubmenu->addAction(hostsCheckButton);
    
    tailProdCheckButton = new QAction("&Tail production", settingsSubmenu);
    tailProdCheckButton->setCheckable(true);
    tailProdCheckButton->setChecked(true);
    settingsSubmenu->addAction(tailProdCheckButton);
    
    messageCheckButton = new QAction("&Message", settingsSubmenu);
    messageCheckButton->setCheckable(true);
    messageCheckButton->setChecked(true);
    settingsSubmenu->addAction(messageCheckButton);
    
    
    releaseCheckButton = new QAction("&Release", settingsSubmenu);
    releaseCheckButton->setCheckable(true);
    releaseCheckButton->setChecked(true);
    settingsSubmenu->addAction(releaseCheckButton);
    
    
    
    
    quit = new QAction("&Quit", trayMenu);
    trayMenu->addAction(quit);
    QObject::connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));
}

//sets the tray icon
void DISH::iconSetup()
{

    icon = QIcon(WORKING_PEPPER);
    
    trayIcon->setIcon(icon);
    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();
    
}

void DISH::setIcon(bool up)
{
    if(up)
        icon = QIcon(WORKING_PEPPER);
    else
        icon = QIcon(BROKEN_PEPPER);
    
    trayIcon->setIcon(icon);
    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();
        
}
