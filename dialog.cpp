

#include <QtGui>
#include "dialog.h"
#include <QLineEdit>
#include <string>
#include <iostream>

using namespace std;

//
//using namespace std;

//dialog for changing URL
urlDialog::urlDialog() 
{
    QGridLayout *gLayout = new QGridLayout;
    gLayout->setColumnStretch(1, 2);

    urlLabel = new QLabel("URL:");
    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");

    urlText = new QLineEdit;

    gLayout->addWidget(urlLabel, 0, 0);
    gLayout->addWidget(urlText, 0, 1);

    setWindowTitle("Change URL");

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    gLayout->addLayout(buttonLayout, 3, 1, Qt::AlignRight);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    connect(okButton, SIGNAL(clicked()),
            this, SLOT(accept()));

    connect(cancelButton, SIGNAL(clicked()),
            this, SLOT(reject()));

}

//dialog for a new hosts file
newHostsDialog::newHostsDialog() 
{
    QGridLayout *gLayout = new QGridLayout;
    gLayout->setColumnStretch(1, 2);
     
    fileNameLabel = new QLabel("File Name:");
    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");

    fileNameText = new QLineEdit;

    gLayout->addWidget(fileNameLabel, 0, 0);
    gLayout->addWidget(fileNameText, 0, 1);

    setWindowTitle("New hosts file");

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    gLayout->addLayout(buttonLayout, 3, 1, Qt::AlignRight);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    connect(okButton, SIGNAL(clicked()),
            this, SLOT(accept()));

    connect(cancelButton, SIGNAL(clicked()),
            this, SLOT(reject()));
}
 
//dialog for making a spice admin
spiceAdminDialog::spiceAdminDialog(bool hasCred) 
{
    QGridLayout *gLayout = new QGridLayout;
//    gLayout->setColumnStretch(1, 2);

    //Make Spice admin with credentials
    if (hasCred == true)
    {
       emailLabel = new QLabel("Email:");
       okButton = new QPushButton("OK");
       cancelButton = new QPushButton("Cancel");

       emailText = new QLineEdit;

       gLayout->addWidget(emailLabel, 0, 0);
       gLayout->addWidget(emailText, 0, 1);
    }
    //Make Spice admin without credentials
    else
    {
        usernameLabel = new QLabel("Username:");
        passwordLabel = new QLabel("Password:");
        emailLabel = new QLabel("Email:");
        okButton = new QPushButton("OK");
        cancelButton = new QPushButton("Cancel");

        usernameText = new QLineEdit;
        passwordText = new QLineEdit;
        passwordText->setEchoMode(QLineEdit::Password);
        emailText = new QLineEdit;

        gLayout->addWidget(usernameLabel, 0, 0);
        gLayout->addWidget(usernameText, 0, 1);

        gLayout->addWidget(passwordLabel, 1, 0);
        gLayout->addWidget(passwordText, 1, 1);

        gLayout->addWidget(emailLabel, 2, 0);
        gLayout->addWidget(emailText, 2, 1);
     }
     QHBoxLayout *buttonLayout = new QHBoxLayout;
     buttonLayout->addWidget(okButton);
     buttonLayout->addWidget(cancelButton);

     gLayout->addLayout(buttonLayout, 3, 1, Qt::AlignLeft);

     QVBoxLayout *mainLayout = new QVBoxLayout;
     mainLayout->addLayout(gLayout);
     setLayout(mainLayout);

     connect(okButton, SIGNAL(clicked()),
             this, SLOT(accept()));

     connect(cancelButton, SIGNAL(clicked()),
             this, SLOT(reject()));

     setWindowTitle("Make a Spice admin");
}

settingsDialog::settingsDialog() 
{
    QGridLayout *gLayout = new QGridLayout;
    QVBoxLayout *showHideLayout = new QVBoxLayout;
    QGridLayout *credentialsLayout = new QGridLayout;
    
    showHideGroup = new QGroupBox(tr("Show/Hide these spicy options"));
    urlCheckBox = new QCheckBox("URL");
    hostsFilesCheckBox = new QCheckBox(tr("Hosts files"));
    prodLogCheckBox = new QCheckBox(tr("Production Logs"));
    messageCheckBox = new QCheckBox(tr("Message"));
    releaseCheckBox = new QCheckBox(tr("Release"));
    saveButton = new QPushButton("Save");
    cancelButton = new QPushButton("Cancel");
    
    showHideLayout->addWidget(urlCheckBox);
    showHideLayout->addWidget(hostsFilesCheckBox);
    showHideLayout->addWidget(prodLogCheckBox);
    showHideLayout->addWidget(messageCheckBox);
    showHideLayout->addWidget(releaseCheckBox);
    showHideGroup->setLayout(showHideLayout);
    gLayout->addWidget(showHideGroup, 0, 0);
    
    credentialsGroup = new QGroupBox(tr("Update/remove/add your credentials"));
    usernameLabel = new QLabel("Username:");
    passwordLabel = new QLabel("Password:");
    usernameText = new QLineEdit;
    passwordText = new QLineEdit;
    passwordText->setEchoMode(QLineEdit::Password);
    removeButton = new QPushButton("Clear");
    
    credentialsLayout->addWidget(usernameLabel, 0, 0);
    credentialsLayout->addWidget(usernameText, 0, 1);
    credentialsLayout->addWidget(passwordLabel, 1, 0);
    credentialsLayout->addWidget(passwordText, 1, 1);
    credentialsLayout->addWidget(removeButton, 2, 0, 1, 2, Qt::AlignHCenter);
    credentialsGroup->setLayout(credentialsLayout);
    gLayout->addWidget(credentialsGroup, 0, 1);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);
    gLayout->addLayout(buttonLayout, 5, 0, 1, 2, Qt::AlignHCenter);
            
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    connect(saveButton, SIGNAL(clicked()),
            this, SLOT(accept()));

    connect(cancelButton, SIGNAL(clicked()),
            this, SLOT(reject()));

    setWindowTitle("SuperSpicyFragilitstic Settings");
}