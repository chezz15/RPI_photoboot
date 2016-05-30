#ifndef CAMERATHREAD_H
#define CAMERATHREAD_H

#include <QThread>
#include <QString>

class CameraThread : public QThread
{
    Q_OBJECT
signals:
    void acquiringImage(unsigned char* image);
    void imageReady(unsigned char* image);
private:
    void run();

};

#endif // CAMERATHREAD_H
