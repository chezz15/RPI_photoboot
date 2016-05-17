#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "button_lib.h"
#include "camerathread.h"
#include "raspicam.h"
#include "raspicam_still.h"
#include <functional>
#include <QDebug>
#include <QThread>
#include <fstream>
#include <QString>
#include <QTime>

MainWindow* MainWindow::instance = nullptr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    button_init(&button_pressed_callback);

    camera.setWidth ( 1280 );
    camera.setHeight ( 960 );
    camera.setISO(400);
    camera.setBrightness(50);
    camera.setAWB(raspicam::RASPICAM_AWB_AUTO);
    camera.setEncoding(raspicam::RASPICAM_ENCODING_BMP);

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

void MainWindow::displayImage(unsigned char* image)
{


    qDebug() << "received image ready signal";
    instance->ui->label->setText("Put image here!");
    //std::ofstream outFile ( "/home/pi/image.ppm",std::ios::binary );
    //outFile << "P6\n  1280 960 255\n";
    QString filename;
    filename = "images/picture_";
    filename += QTime::currentTime().toString("hh_mm_ss");
    filename += ".bmp";
    //outFile.write ( ( char* ) image,camera.getImageBufferSize() );
    qDebug() << filename;
    std::ofstream file (filename.toStdString(),std::ios::binary );
    file.write ( ( char* ) image, camera.getImageBufferSize() );


}


raspicam::RaspiCam_Still& MainWindow::getCamera()
{
    return camera;
}
