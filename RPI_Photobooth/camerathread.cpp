#include "camerathread.h"
#include "mainwindow.h"
#include <QDebug>
#include <QDateTime>
#include <QProcess>

void CameraThread::run()
{
    qDebug() << "camera thread started";


#if 0
    MainWindow::getInstance()->getVideoCamera().open();
    for (int i = 0; i < 1; i++) {
        qDebug() << "new image"<< QDateTime::currentMSecsSinceEpoch();
        //capture
        MainWindow::getInstance()->getVideoCamera().grab();
        //allocate memory
        unsigned char *data=new unsigned char[ MainWindow::getInstance()->getVideoCamera().getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB )];
        //extract the image in rgb format
        MainWindow::getInstance()->getVideoCamera().retrieve ( data,raspicam::RASPICAM_FORMAT_RGB );//get camera image
        qDebug() << "grabbed" << QDateTime::currentMSecsSinceEpoch();
        emit acquiringImage(data) ;
    }
    MainWindow::getInstance()->getVideoCamera().release();
#endif
    emit acquiringVideo() ;
    //MainWindow::getInstance()->getCamera().grab_retrieve ( image,length );//get camera image
    //qDebug() << "emitting image ready signal..";
    //emit imageReady(image) ;
}

void CameraThread::acquireImage(int exit_code, QProcess::ExitStatus status)
{

    qDebug() << "acquiring image";

    unsigned int length = MainWindow::getInstance()->getVideoCamera().getImageBufferSize(); // Header + Image Data + Padding
    unsigned char * image = new unsigned char[length];

    MainWindow::getInstance()->getCamera().grab_retrieve ( image,length );//get camera image
    qDebug() << "emitting image ready signal..";
    emit imageReady(image) ;

}
