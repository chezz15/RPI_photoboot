#include "gallerythread.h"
#include "mainwindow.h"
#include <QDebug>
#include <QString>
#include <QTimer>
//#include <QDateTime>
#include <QDirIterator>

void GalleryThread::run()
{
    qDebug() << "gallery thread started";
    QTimer timer;

    //it_gallery("/home/pi/images", QStringList() << "*.bmp", QDir::Files);

    connect(&timer, SIGNAL(timeout()), this, SLOT(timerHit()), Qt::DirectConnection);
    timer.setInterval(5000);
    timer.start();
    exec();
    timer.stop();
}

void GalleryThread::timerHit()
{
    QString filepath;
    //QDirIterator it_gallery("/home/pi/images", QStringList() << "*.bmp", QDir::Files);
//    QString newTime= QDateTime::currentDateTime().toString("ddd MMMM d yy, hh:mm:ss");
    qDebug() << "gallery timeout elapsed";
//    if(m_lastTime != newTime ){
//        m_lastTime = newTime;
    if (MainWindow::getInstance()->getState() != IDLE)
        return;

/*    filepath = it_gallery().filePath();
    if (it_gallery().hasNext())
        it_gallery().next();
*/
    qDebug() << "emitting show Gallery signal";
    emit showGallery(filepath);
//    }
}
