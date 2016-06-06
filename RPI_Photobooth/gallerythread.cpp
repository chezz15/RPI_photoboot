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

    if (MainWindow::getInstance()->getState() == CAPTURING)
        return;

    else if (MainWindow::getInstance()->getState() == WAIT_FOR_BUTTON_PRESS){
        MainWindow::getInstance()->setState(RESTART_GALLERY);
        return;
    }

    if (it_gallery->hasNext()){
        qDebug() << "starting gallery..";
        qDebug() << "next image.." << it_gallery->next();
    }
    else{
        delete(it_gallery);
        it_gallery = new QDirIterator("/home/pi/images", QStringList() << "*.bmp", QDir::Files);
        qDebug() << "created new gallery.." << it_gallery->fileName();
        qDebug() << "next image.." << it_gallery->next();
    }
    filepath = it_gallery->filePath();
    qDebug() << "emitting show Gallery signal with filepath.." << filepath;
    emit showGallery(filepath);
}
