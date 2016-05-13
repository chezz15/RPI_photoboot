#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "button_lib.h"
#include "camerathread.h"
#include "raspicam.h"
#include <functional>
#include <QDebug>
#include <QThread>


MainWindow* MainWindow::instance = nullptr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    button_init(&button_pressed_callback);

    qDebug()  <<"Opening Camera...";
    if ( !camera.open()) {
        qDebug() <<"Error opening camera";
    }
    QObject::connect(&cameraThread, &CameraThread::imageReady, this, &MainWindow::displayImage, Qt::QueuedConnection);
    //cameraThread.start();
}

MainWindow::~MainWindow()
{
    cameraThread.quit();
    cameraThread.wait();
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
    MainWindow::getInstance()->cameraThread.start();
}

void MainWindow::displayImage(unsigned char*)
{
    qDebug() << "received image ready signal";
    instance->ui->label->setText("Put image here!");
}


raspicam::RaspiCam& MainWindow::getCamera()
{
    return camera;
}
