#include "camerathread.h"
#include "mainwindow.h"
#include <QDebug>
void CameraThread::run()
{
    qDebug() << "thread started";

    //MainWindow::getInstance()->getCamera().grab();
    //allocate memory
    //unsigned char *image=new unsigned char[  MainWindow::getInstance()->getCamera().getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB )];
    //extract the image in rgb format
    //MainWindow::getInstance()->getCamera().retrieve ( image,raspicam::RASPICAM_FORMAT_RGB );//get camera image
    unsigned int length = MainWindow::getInstance()->getCamera().getImageBufferSize(); // Header + Image Data + Padding
    unsigned char * image = new unsigned char[length];
    MainWindow::getInstance()->getCamera().grab_retrieve ( image,length );//get camera image
    qDebug() << "emitting image ready signal";
    emit imageReady(image) ;
}

