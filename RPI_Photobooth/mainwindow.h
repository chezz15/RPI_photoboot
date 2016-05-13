#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "camerathread.h"
#include "raspicam.h"
typedef void function_t(void);

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ~MainWindow();
    static MainWindow* getInstance();
    raspicam::RaspiCam& getCamera();

private:
    CameraThread cameraThread;
    MainWindow(QWidget *parent = 0);
    static MainWindow* instance;
    Ui::MainWindow *ui;
    raspicam::RaspiCam camera;
    static void button_pressed_callback();


private slots:
    void displayImage(unsigned char*);

};

#endif // MAINWINDOW_H
