

 #include <QtGui>
 #include "dialog.h"
 #include <QLineEdit>
 #include <string>
//
//using namespace std;

//dialog for new hosts and for change URL
 dialog::dialog(string type) 

 {
     
     QGridLayout *gLayout = new QGridLayout;
     gLayout->setColumnStretch(1, 2);
     
     if (type == "hosts")
     {
        fileNameLabel = new QLabel("File Name:");
        okButton = new QPushButton("OK");
        cancelButton = new QPushButton("Cancel");

        fileNameText = new QLineEdit;

        gLayout->addWidget(fileNameLabel, 0, 0);
        gLayout->addWidget(fileNameText, 0, 1);
        
        setWindowTitle("New hosts file");
     }
     else
     {
        urlLabel = new QLabel("URL:");
        okButton = new QPushButton("OK");
        cancelButton = new QPushButton("Cancel");

        urlText = new QLineEdit;

        gLayout->addWidget(urlLabel, 0, 0);
        gLayout->addWidget(urlText, 0, 1);
        
        setWindowTitle("Change URL");
     }

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
 
 //dialog for spice admin
 dialog::dialog(bool hasCred) 

 {
     QGridLayout *gLayout = new QGridLayout;
     gLayout->setColumnStretch(1, 2);
        
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
 