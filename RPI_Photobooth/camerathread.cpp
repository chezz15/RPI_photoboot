#include "camerathread.h"
#include "mainwindow.h"
#include <QDebug>
#include <QDateTime>
#include <QProcess>

void CameraThread::run()
{
    qDebug() << "camera thread started";
    QProcess process;

    process.start("raspivid", QStringList() << "-t 10000");
/*    unsigned int length = MainWindow::getInstance()->getCamera().getImageBufferSize(); // Header + Image Data + Padding
    unsigned char * image = new unsigned char[length];
    for (int i = 0; i < 1; i++) {
        qDebug() << "new image"<< QDateTime::currentMSecsSinceEpoch();
        MainWindow::getInstance()->getCamera().grab_retrieve ( image,length );//get camera image
        qDebug() << "grabbed" << QDateTime::currentMSecsSinceEpoch();
        emit acquiringImage(image) ;
    }*/


    qDebug() << "emitting image ready signal..";
    //emit imageReady(image) ;
}

