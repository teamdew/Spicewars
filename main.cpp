/*
 * File:   main.cpp
 * Author: asilvajr
 *
 * Created on January 30, 2013, 5:44 PM
 */

#include <QApplication>
#include "DISH.h"

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);

    // create and show your widgets here
    //return 0;
    
    DISH d;
    d.createMenu();
    d.iconSetup();
    return app.exec();
}