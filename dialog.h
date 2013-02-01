/* 
 * File:   dialog.h
 * Author: asilvajr
 *
 * Created on January 31, 2013, 8:35 PM
 */

#ifndef DIALOG_H
#define	DIALOG_H

 #include <QtGui>
 #include "adddialog.h"

 dialog::AddDialog(QWidget *parent)
     : QDialog(parent)
 {
     nameLabel = new QLabel("Name");
     okButton = new QPushButton("OK");
     cancelButton = new QPushButton("Cancel");

     nameText = new QLineEdit;
     addressText = new QTextEdit;

     QGridLayout *gLayout = new QGridLayout;
     gLayout->setColumnStretch(1, 2);
     gLayout->addWidget(nameLabel, 0, 0);
     gLayout->addWidget(nameText, 0, 1);

     gLayout->addWidget(addressLabel, 1, 0, Qt::AlignLeft|Qt::AlignTop);
     gLayout->addWidget(addressText, 1, 1, Qt::AlignLeft);

     QHBoxLayout *buttonLayout = new QHBoxLayout;
     buttonLayout->addWidget(okButton);
     buttonLayout->addWidget(cancelButton);

     gLayout->addLayout(buttonLayout, 2, 1, Qt::AlignRight);

     QVBoxLayout *mainLayout = new QVBoxLayout;
     mainLayout->addLayout(gLayout);
     setLayout(mainLayout);

     connect(okButton, SIGNAL(clicked()),
             this, SLOT(accept()));

     connect(cancelButton, SIGNAL(clicked()),
             this, SLOT(reject()));

     setWindowTitle(tr("Add a Contact"));
 }

#endif	/* DIALOG_H */

