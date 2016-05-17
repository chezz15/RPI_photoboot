#include "gallerythread.h"
#include "mainwindow.h"
#include <QDebug>
#include <QString>
#include <QTimer>
//#include <QDateTime>
#include <QDirIterator>

GalleryThread::GalleryThread()
{
    it_gallery = new QDirIterator("/home/pi/images", QStringList() << "*.bmp", QDir::Files);
}

void GalleryThread::run()
{
    qDebug() << "gallery thread started";
    QTimer timer;

    connect(&timer, SIGNAL(timeout()), this, SLOT(timerHit()), Qt::DirectConnection);
    timer.setInterval(5000);
    timer.start();
    exec();
    timer.stop();
}

void GalleryThread::timerHit()
{
    QString filepath;

    qDebug() << "gallery timeout elapsed..current state: " << MainWindow::getInstance()->getState();

//    QString newTime= QDateTime::currentDateTime().toString("ddd MMMM d yy, hh:mm:ss");
//    if(m_lastTime != newTime ){
//        m_lastTime = newTime;

    if (MainWindow::getInstance()->getState() == CAPTURING)
        return;
    else if (MainWindow::getInstance()->getState() == WAIT_FOR_BUTTON_PRESS)
        MainWindow::getInstance()->setState(RESTART_GALLERY);

    qDebug() << "starting gallery..";

    filepath = it_gallery->filePath();
    if (it_gallery->hasNext()){
        qDebug() << "next image.." << it_gallery->next();
        it_gallery->next();
    }
    else{
        delete(it_gallery);
        it_gallery = new QDirIterator("/home/pi/images", QStringList() << "*.bmp", QDir::Files);
        qDebug() << "created new gallery..";
    }

    qDebug() << "emitting show Gallery signal..";
    emit showGallery(filepath);
//    }
}
