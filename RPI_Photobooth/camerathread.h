#ifndef CAMERATHREAD_H
#define CAMERATHREAD_H

#include <QThread>
#include <QString>
#include <QProcess>
#include <QTimer>

class CameraThread : public QThread
{
    Q_OBJECT
signals:
    void imageReady(unsigned char* image);
    void countDownImage(int count);
private:
    QTimer *timer;
    int  count;
    void run();
private slots:
    void timerHit();

};

#endif // CAMERATHREAD_H
