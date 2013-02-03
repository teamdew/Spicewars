#ifndef DISH_H
#define DISH_H
//#define HOSTS_DIR "C:\\Windows\\System32\\drivers\\etc\\hosts"
//if testing on a linux box use this instead
#define HOSTS_DIR "//etc"
#define WORKING_PEPPER "pepper-icon.png"
#define BROKEN_PEPPER "broken-pepper-icon.png"
#include <QMenu>
#include <QSystemTrayIcon>
#include <QDialog>
#include <dialog.h>
#include <curl/curl.h>
#include <QTimer>

using namespace std;

//QT_BEGIN_NAMESPACE
//class QAction;
//class QActionGroup;
//class QLabel;
//class QMenu;
//QT_END_NAMESPACE

class DISH : public QDialog{
       Q_OBJECT;
       
       public:
                DISH();
                ~DISH();
                void createMenu();
                QIcon icon;
                
        
       private slots:
                void timeOut();
                void changeURL(); 
                void editHosts();
                void newHosts();
                void openHostsDir();
                void settings();
                
                
                
       private:
                CURL *curl;
                
                vector<string> hostsVector;
                QMenu *trayMenu;
                QSystemTrayIcon *trayIcon;
                
                QMenu *urlSubmenu;
                QAction *changeURLButton;
                QAction *defaultURLButton;
                QAction *clearCacheButton;
                
                QMenu *userHostsSubMenu;
                QAction *openPuttyButton;
                QAction *communityLogsButton;
                
                QAction *adminButton;
                QAction *tailProdButton;
                
                QMenu *hostsSubmenu;
                QAction *editButton;
                QAction *newHostsButton;
                QAction *refreshButton;
                QAction *hostsDirButton;
                QAction *messageButton;
                QAction *releaseButton;
                
                QAction *settingsButton;
                QAction *urlCheckButton;
                QAction *hostsCheckButton;
                QAction *tailProdCheckButton;
                QAction *messageCheckButton;
                QAction *releaseCheckButton;
                
                QAction *quit;
                void setIcon();
                void getHostsList();
                bool checkServer();
                QTimer *timer;        
                        
                
                
};
#endif