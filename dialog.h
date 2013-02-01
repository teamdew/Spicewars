/* 
 * File:   dialog.h
 * Author: asilvajr
 *
 * Created on January 31, 2013, 8:35 PM
 */

#ifndef DIALOG_H
#define	DIALOG_H

  #include <QDialog>
#include <QWidget>
#include <string>

using namespace std;

 class QLabel;
 class QPushButton;
 class QTextEdit;
 class QLineEdit;

 class dialog : public QDialog
 {
     Q_OBJECT
 public:
     dialog(string);
     dialog(bool);
     QLineEdit *fileNameText;
     QLineEdit *usernameText;
     QLineEdit *passwordText;
     QLineEdit *emailText;
     QLineEdit *urlText;

 private:
     QLabel *fileNameLabel;
     QLabel *usernameLabel;
     QLabel *passwordLabel;
     QLabel *emailLabel;
     QLabel *urlLabel;
     QPushButton *okButton;
     QPushButton *cancelButton;
 };

#endif	/* DIALOG_H */
