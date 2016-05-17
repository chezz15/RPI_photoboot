#include "mainwindow.h"
#include "button_lib.h"
#include <QApplication>
#include <iostream>
#include <QDebug>
#include <ctime>
#include <fstream>
#include <iostream>
#include "raspicam.h"


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    if (lib_init() < 0) {
        qDebug() << "Error during lib_init";
        return -2;
    }

    MainWindow::getInstance()->show();

    return a.exec();
}

