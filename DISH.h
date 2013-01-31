#ifndef DISH_H
#define DISH_H
#define HOSTS_DIR "C:\\Windows\\System32\\drivers\\etc\\hosts"
#define WORKING_PEPPER "pepper-icon.png"
#define BROKEN_PEPPER "broken-pepper-icon.png"
#include <QMenu>
#include <QSystemTrayIcon>

//QT_BEGIN_NAMESPACE
//class QAction;
//class QActionGroup;
//class QLabel;
//class QMenu;
//QT_END_NAMESPACE

class DISH{
        public:
                DISH();
//                bool checkServer();
                void createMenu();
                void iconSetup();
                QIcon icon;
        private:
                QMenu *trayMenu;
                QSystemTrayIcon *trayIcon;
                
                QMenu *urlSubmenu;
                QAction *changeURLButton;
                QAction *defaultURLButton;
                QAction *clearCacheButton;
                
                QAction *adminButton;
                QAction *tailProdButton;
                
                QMenu *hostsSubmenu;
                QAction *editButton;
                QAction *newHostsButton;
                QAction *refreshButton;
                QAction *hostsDirButton;
                QAction *messageButton;
                QAction *releaseButton;
                
                QMenu *settingsSubmenu;
                QAction *urlCheckButton;
                QAction *hostsCheckButton;
                QAction *tailProdCheckButton;
                QAction *messageCheckButton;
                QAction *releaseCheckButton;
                
                QAction *quit;
                void setIcon(bool up);
                        
                
                
};
#endif