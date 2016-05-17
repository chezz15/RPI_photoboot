#ifndef GALLERYTHREAD_H
#define GALLERYTHREAD_H
#include <QString>
#include <QThread>
#include <QDirIterator>

class GalleryThread : public QThread
{
    Q_OBJECT
public:
    explicit GalleryThread();

signals:
    void showGallery(QString filepath);
    void sendTime(QString time);
private:
    QDirIterator* it_gallery;
    void run();

private slots:
    void timerHit();

};

#endif // GALLERYTHREAD_H
