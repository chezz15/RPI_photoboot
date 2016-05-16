#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "button_lib.h"
#include "camerathread.h"
#include "gallerythread.h"
#include "raspicam.h"
#include <functional>
#include <QDebug>
#include <QThread>
#include <QString>
#include <QTime>

MainWindow* MainWindow::instance = nullptr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    button_init(&button_pressed_callback);
    PIR_init(&motion_detected_callback);

    qDebug()  <<"Opening Camera...";
    if ( !camera.open()) {
        qDebug() <<"Error opening camera";
    }

    QObject::connect(&cameraThread, &CameraThread::imageReady, this, &MainWindow::displayImage, Qt::QueuedConnection);
    QObject::connect(&galleryThread, &GalleryThread::showGallery, this, &MainWindow::displayGallery, Qt::QueuedConnection);
    state = IDLE;
    galleryThread.start();
}

MainWindow::~MainWindow()
{
    cameraThread.quit();
    cameraThread.wait();
    galleryThread.quit();
    galleryThread.wait();
    camera.release();
    delete ui;
}

MainWindow* MainWindow::getInstance()
{
    if(instance == nullptr)
    {
        instance = new MainWindow();
    }

    return instance;
}

void MainWindow::button_pressed_callback()
{
    qDebug() << "button pressed";
    MainWindow::getInstance()->state = CAPTURING;
    MainWindow::getInstance()->cameraThread.start();
}

void MainWindow::motion_detected_callback()
{
    qDebug() << "motion detected";
    MainWindow::getInstance()->state = WAIT_FOR_BUTTON_PRESS;
}


void MainWindow::displayImage(unsigned char*)
{
    QImage lastTakenPicture;

    qDebug() << "received image ready signal";

    lastTakenPicture.load("");
    instance->ui->label->setPixmap(QPixmap::fromImage(lastTakenPicture));
    instance->ui->label->show();
    delay(5);
    state = IDLE;
}


raspicam::RaspiCam& MainWindow::getCamera()
{
    return camera;
}

enum state_t& MainWindow::getState()
{
    return state;
}

void MainWindow::displayGallery(QString filepath)
{
    QImage currentPicture;

    currentPicture.load(filepath);
    instance->ui->label->setPixmap(QPixmap::fromImage(currentPicture));
    instance->ui->label->show();
}

void MainWindow::updateCameraSettings()
{
    camera.setBrightness(50);
}

void MainWindow::delay(int seconds)
{
    QTime dieTime= QTime::currentTime().addSecs(seconds);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
