#include "mainwindow.h"
#include "button_lib.h"
#include <QApplication>
#include <iostream>
#include <QDebug>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    if (lib_init() < 0) {
        //printf ("Unable to setup wiringPi\r\n");
        return 1;
    }

    MainWindow w;
    w.show();



    return a.exec();
}
