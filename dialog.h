/* 
 * File:   dialog.h
 * Author: asilvajr
 *
 * Created on January 31, 2013, 8:35 PM
 */

#ifndef DIALOG_H
#define	DIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <QGroupBox>
#include <boost/regex.hpp>

using namespace std;

class QLabel;
class QPushButton;
class QTextEdit;
class QLineEdit;

class urlDialog : public QDialog
{
    Q_OBJECT;

    public:
        urlDialog();
        QLineEdit *urlText;
        
    private slots:
        void changeURL();
        void doNothing();

    private:
        QLabel *urlLabel;
        QPushButton *okButton;
        QPushButton *cancelButton;
};

class newHostsDialog : public QDialog
{
    Q_OBJECT;
    public:
        newHostsDialog();
        QLineEdit *fileNameText;
        
    private slots:
        void makeNewHostsFile();
        void doNothing();

    private:
        QLabel *fileNameLabel;
        QPushButton *okButton;
        QPushButton *cancelButton;   
};
 
class spiceAdminDialog : public QDialog
{
    Q_OBJECT;
    
    public:
        spiceAdminDialog(bool);
        QLineEdit *usernameText;
        QLineEdit *passwordText;
        QLineEdit *emailText;
    
    private slots:
        void runSpiceAdminScript();
        void doNothing();
        
    private:
        QLabel *usernameLabel;
        QLabel *passwordLabel;
        QLabel *emailLabel;
        QPushButton *okButton;
        QPushButton *cancelButton;  
};
 
class settingsDialog : public QDialog
{
    Q_OBJECT;
    
    public:
        settingsDialog();
        QLineEdit *usernameText;
        QLineEdit *passwordText;
        QCheckBox *urlCheckBox;
        QCheckBox *hostsFilesCheckBox;
        QCheckBox *prodLogCheckBox;
        QCheckBox *messageCheckBox;
        QCheckBox *releaseCheckBox;
        bool updated;
        QLineEdit * getUsername();
        QLineEdit * getPassword();
    
    private slots:
        void updateMenu();
        void doNothing();
        void deleteCreds();

    private:
        QLabel *usernameLabel;
        QLabel *passwordLabel;
        QPushButton *saveButton;
        QPushButton *cancelButton;
        QPushButton *removeButton;
        QGroupBox *showHideGroup;
        QGroupBox *credentialsGroup;
        string parseFile(string location, boost::regex re);
    
};

class messageDialog : public QDialog
{
    Q_OBJECT;
    public:
        messageDialog();
        QLineEdit *fileNameText;
        
    private slots:
        //void makeNewHostsFile();
        //void doNothing();

    private:
        QLabel *fileNameLabel;
        QPushButton *okButton;
        QPushButton *cancelButton;   
};
 

#endif	/* DIALOG_H */