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
#include <string>
#include <QGroupBox>

using namespace std;

class QLabel;
class QPushButton;
class QTextEdit;
class QLineEdit;

class urlDialog : public QDialog
{
    Q_OBJECT
public:
    urlDialog();
    QLineEdit *urlText;

private:
    QLabel *urlLabel;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

class newHostsDialog : public QDialog
{
    Q_OBJECT
public:
    newHostsDialog();
    QLineEdit *fileNameText;

private:
    QLabel *fileNameLabel;
    QPushButton *okButton;
    QPushButton *cancelButton;   
};
 
class spiceAdminDialog : public QDialog
{
    Q_OBJECT
public:
    spiceAdminDialog(bool);
    QLineEdit *usernameText;
    QLineEdit *passwordText;
    QLineEdit *emailText;

private:
    QLabel *usernameLabel;
    QLabel *passwordLabel;
    QLabel *emailLabel;
    QPushButton *okButton;
    QPushButton *cancelButton;  
};
 
class settingsDialog : public QDialog
{
    Q_OBJECT
public:
    settingsDialog();
    QLineEdit *usernameText;
    QLineEdit *passwordText;

private:
    QLabel *usernameLabel;
    QLabel *passwordLabel;
    QPushButton *saveButton;
    QPushButton *cancelButton;
    QPushButton *removeButton;
    QCheckBox *urlCheckBox;
    QCheckBox *hostsFilesCheckBox;
    QCheckBox *prodLogCheckBox;
    QCheckBox *messageCheckBox;
    QCheckBox *releaseCheckBox;
    QGroupBox *showHideGroup;
    QGroupBox *credentialsGroup;
    
};

 

#endif	/* DIALOG_H */
