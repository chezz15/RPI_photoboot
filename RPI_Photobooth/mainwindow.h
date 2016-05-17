#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "camerathread.h"
#include "gallerythread.h"
#include "raspicam.h"
#include "raspicam_still.h"
#include <QMainWindow>

typedef void function_t(void);

namespace Ui {
class MainWindow;
}

enum state_t: uint8_t
{
    IDLE = 1,
    WAIT_FOR_BUTTON_PRESS,
    CAPTURING,
    RESTART_GALLERY
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ~MainWindow();
    static MainWindow* getInstance();
    raspicam::RaspiCam_Still &getCamera();
    state_t& getState();
    void setState(enum state_t new_state);

private:
    enum state_t state;
    CameraThread cameraThread;
    GalleryThread galleryThread;
    MainWindow(QWidget *parent = 0);
    static MainWindow* instance;
    Ui::MainWindow *ui;
    //raspicam::RaspiCam camera;
    raspicam::RaspiCam_Still camera;
    void delay(int seconds);
    static void button_pressed_callback();
    static void motion_detected_callback();
    static void end_motion_callback();

    void showImageGallery();
    void showIntro();
    void showCamera();

private slots:
    void displayImage(unsigned char*);
    void displayGallery(QString);
};

#endif // MAINWINDOW_H
