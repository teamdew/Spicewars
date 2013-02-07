#include <QtGui>
#include "dialog.h"
#include <QLineEdit>
#include <fstream>
#include <boost/algorithm/string.hpp>


using namespace std;

//
//using namespace std;

void urlDialog::changeURL() {

}

void urlDialog::doNothing() {
    QDialog::setVisible(false);
}

//dialog for changing URL

urlDialog::urlDialog() {
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
            this, SLOT(doNothing()));

}

void newHostsDialog::makeNewHostsFile() {

}

void newHostsDialog::doNothing() {
    QDialog::setVisible(false);
}

//dialog for a new hosts file

newHostsDialog::newHostsDialog() {
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

void spiceAdminDialog::runSpiceAdminScript() {

}

void spiceAdminDialog::doNothing() {
    QDialog::setVisible(false);
}

//dialog for making a spice admin

spiceAdminDialog::spiceAdminDialog(bool hasCred) {
    QGridLayout *gLayout = new QGridLayout;
    //    gLayout->setColumnStretch(1, 2);

    //Make Spice admin with credentials
    if (hasCred == true) {
        emailLabel = new QLabel("Email:");
        okButton = new QPushButton("OK");
        cancelButton = new QPushButton("Cancel");

        emailText = new QLineEdit;

        gLayout->addWidget(emailLabel, 0, 0);
        gLayout->addWidget(emailText, 0, 1);
    }        //Make Spice admin without credentials
    else {
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

void settingsDialog::updateMenu() {

    this->setVisible(false);
    updated = true;
    QDialog::accept();
}

void settingsDialog::doNothing() {
    this->setVisible(false);
    updated = false;
    QDialog::accept();
}

void settingsDialog::deleteCreds() {

}

QLineEdit * settingsDialog::getUsername() {
    return usernameText;
}

QLineEdit * settingsDialog::getPassword() {
    return passwordText;
}

settingsDialog::settingsDialog() {
    QGridLayout *gLayout = new QGridLayout;
    QVBoxLayout *showHideLayout = new QVBoxLayout;
    QGridLayout *credentialsLayout = new QGridLayout;

    showHideGroup = new QGroupBox(tr("Show/hide these spicy options"));

    urlCheckBox = new QCheckBox("URL");
    string input = parseFile("config", boost::regex(".*Url Checkbox.*"));
    vector<string> parsed;
    boost::split(parsed, input, boost::is_any_of(" "));
    if (parsed[2] == "1")
        urlCheckBox->setCheckState(Qt::Checked);
    else
        urlCheckBox->setCheckState(Qt::Unchecked);

    hostsFilesCheckBox = new QCheckBox("Hosts files");
    input = parseFile("config", boost::regex(".*Hosts Checkbox.*"));
    boost::split(parsed, input, boost::is_any_of(" "));
    if (parsed[2] == "1")
        hostsFilesCheckBox->setCheckState(Qt::Checked);
    else
        hostsFilesCheckBox->setCheckState(Qt::Unchecked);

    prodLogCheckBox = new QCheckBox("Production Logs");
    input = parseFile("config", boost::regex(".*Prod Log Checkbox.*"));
    boost::split(parsed, input, boost::is_any_of(" "));
    if (parsed[3] == "1")
        prodLogCheckBox->setCheckState(Qt::Checked);
    else
        prodLogCheckBox->setCheckState(Qt::Unchecked);

    messageCheckBox = new QCheckBox("Message");
    input = parseFile("config", boost::regex(".*Message Checkbox.*"));
    boost::split(parsed, input, boost::is_any_of(" "));
    if (parsed[2] == "1")
        messageCheckBox->setCheckState(Qt::Checked);
    else
        messageCheckBox->setCheckState(Qt::Unchecked);

    releaseCheckBox = new QCheckBox("Release");
    input = parseFile("config", boost::regex(".*Release Checkbox.*"));
    boost::split(parsed, input, boost::is_any_of(" "));
    if (parsed[2] == "1")
        releaseCheckBox->setCheckState(Qt::Checked);
    else
        releaseCheckBox->setCheckState(Qt::Unchecked);

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
    removeButton = new QPushButton("Remove credentials from DISH");
    cout << "inside exec" << endl;
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

    connect(removeButton, SIGNAL(clicked()),
            this, SLOT(deleteCreds()));

    connect(saveButton, SIGNAL(clicked()),
            this, SLOT(updateMenu()));

    connect(cancelButton, SIGNAL(clicked()),
            this, SLOT(doNothing()));

    setWindowTitle("SuperSpicyFragilitstic Settings");
}

string settingsDialog::parseFile(string location, boost::regex re) {
    ifstream myFile(location.c_str());
    string input;
    bool found = false;

    while (!found && getline(myFile, input)) {
        if (boost::regex_match(input, re))
            found = true;
    }

    return input;
}

messageDialog::messageDialog() {
    QGridLayout *gLayout = new QGridLayout;
    gLayout->setColumnStretch(1, 2);

    fileNameLabel = new QLabel("Message:");
    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");

    fileNameText = new QLineEdit;

    gLayout->addWidget(fileNameLabel, 0, 0);
    gLayout->addWidget(fileNameText, 1, 0, 1, 3);

    setWindowTitle("Send Message");

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    gLayout->addLayout(buttonLayout, 3, 1, 1, 2, Qt::AlignRight);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    connect(okButton, SIGNAL(clicked()),
            this, SLOT(accept()));

    connect(cancelButton, SIGNAL(clicked()),
            this, SLOT(reject()));
}