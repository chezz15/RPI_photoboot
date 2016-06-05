#include "camerathread.h"
#include "mainwindow.h"
#include <QDebug>
#include <QDateTime>
#include <QTimer>

void CameraThread::run()
{
    qDebug() << "camera thread started";

    count = 5;
    qDebug() << "timer: " << timer;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerHit()), Qt::DirectConnection);
    timer->setInterval(1000);
    timer->start();
    exec();
}

void CameraThread::timerHit()
{

    qDebug() << "camera timer hit"<< count;

    if (count > 0){
        emit countDownImage(count) ;
        count --;
    }
    else{
        timer->stop();
        unsigned int length = MainWindow::getInstance()->getCamera().getImageBufferSize(); // Header + Image Data + Padding
        unsigned char * image = new unsigned char[length];
        //for (int i = 0; i < 1; i++) {
        //    qDebug() << "new image"<< QDateTime::currentMSecsSinceEpoch();
            MainWindow::getInstance()->getCamera().grab_retrieve ( image,length );//get camera image
        //    qDebug() << "grabbed" << QDateTime::currentMSecsSinceEpoch();
        //    emit acquiringImage(image) ;
        //}

        qDebug() << "emitting image ready signal..";
        emit imageReady(image);
    }
}
