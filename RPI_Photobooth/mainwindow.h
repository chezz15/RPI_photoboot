#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "camerathread.h"
#include "gallerythread.h"
#include "raspicam.h"
#include <QMainWindow>

typedef void function_t(void);

namespace Ui {
class MainWindow;
}

enum state_t: uint8_t
{
    IDLE,
    WAIT_FOR_BUTTON_PRESS,
    CAPTURING
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ~MainWindow();
    static MainWindow* getInstance();
    raspicam::RaspiCam& getCamera();
    state_t& getState();

private:
    enum state_t state;
    CameraThread cameraThread;
    GalleryThread galleryThread;
    MainWindow(QWidget *parent = 0);
    static MainWindow* instance;
    Ui::MainWindow *ui;
    raspicam::RaspiCam camera;
    void delay(int seconds);
    static void button_pressed_callback();
    static void motion_detected_callback();
    void updateCameraSettings();

private slots:
    void displayImage(unsigned char*);
    void displayGallery(QString);
};

#endif // MAINWINDOW_H
