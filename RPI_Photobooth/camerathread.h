#ifndef CAMERATHREAD_H
#define CAMERATHREAD_H

#include <QThread>
#include <QString>
#include <QProcess>
class CameraThread : public QThread
{
    Q_OBJECT
public:
    void acquireImage(int exit_code, QProcess::ExitStatus status);
signals:
    void imageReady(unsigned char* image);
    void acquiringVideo();
private:
    void run();

};

#endif // CAMERATHREAD_H
