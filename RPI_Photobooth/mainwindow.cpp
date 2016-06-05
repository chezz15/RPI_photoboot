#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "button_lib.h"
#include "camerathread.h"
#include "gallerythread.h"
#include "raspicam.h"
#include "raspicam_still.h"
#include "settingsdialog.h"
#include <functional>
#include <QDebug>
#include <QThread>
#include <fstream>
#include <QString>
#include <QTime>
#include <QDateTime>
#include <QProcess>

MainWindow* MainWindow::instance = nullptr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    button_init(&button_pressed_callback);
    PIR_init(&motion_detected_callback,&end_motion_callback);

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
    //QObject::connect(&cameraThread, &CameraThread::acquiringVideo, this, &MainWindow::displayVideo, Qt::QueuedConnection);
    QObject::connect(&cameraThread, &CameraThread::imageReady, this, &MainWindow::saveImage, Qt::QueuedConnection);
    QObject::connect(&cameraThread, &CameraThread::countDownImage, this, &MainWindow::displayCountDown, Qt::QueuedConnection);
    QObject::connect(&galleryThread, &GalleryThread::showGallery, this, &MainWindow::displayGallery, Qt::QueuedConnection);
    //QObject::connect(&this->process, &QProcess::finished, &cameraThread, &CameraThread::acquireImage, Qt::QueuedConnection);
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

//void MainWindow::displayImage(unsigned char* image)
void MainWindow::displayVideo()
{
//    QPixmap q;

    showCamera();
    process.start("raspivid", QStringList() << "-t 10000 -o instance->ui->cameraLabel");
//    process.waitForFinished(10000);


//    QString filename;
//    filename += "temp.bmp";
//    std::ofstream file (filename.toStdString(),std::ios::binary );
//    file.write ( ( char* ) image, camera.getImageBufferSize() );
//    lastTakenPicture.load(filename);
//    qDebug() << "displaying" << QDateTime::currentMSecsSinceEpoch();
//    uint len = getCamera().getImageBufferSize();
//    q.loadFromData(image,len,"BMP");
//    qDebug() << "loaded" << QDateTime::currentMSecsSinceEpoch();
//    instance->ui->cameraLabel->setPixmap(q);
//    instance->ui->cameraLabel->setPixmap(QPixmap::fromImage(lastTakenPicture));

}


void MainWindow::saveImage(unsigned char* image)
{
    qDebug() << "received image ready signal";

    QImage lastTakenPicture;

    qDebug() << "received image ready signal";
	
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

	lastTakenPicture.load(filename);
    instance->ui->cameraLabel->setPixmap(QPixmap::fromImage(lastTakenPicture));
    showCamera();
    delay(5); //TODO To be replace by PIR PIN down event
    state = IDLE;
    cameraThread.terminate();
}

void MainWindow::motion_detected_callback()
{
    QImage introPicture;

    qDebug() << "motion detected";

    introPicture.load("/home/pi/intro.jpg");
    MainWindow::getInstance()->state = WAIT_FOR_BUTTON_PRESS;
    instance->ui->introLabel->setPixmap(QPixmap::fromImage(introPicture));
    MainWindow::getInstance()->showIntro();
}

void MainWindow::end_motion_callback()
{
    qDebug() << "motion ended callback";
    MainWindow::getInstance()->state = IDLE;
}


raspicam::RaspiCam_Still& MainWindow::getCamera()
{
    return camera;
}

raspicam::RaspiCam& MainWindow::getVideoCamera()
{
    return videocamera;
}

enum state_t& MainWindow::getState()
{
    return state;
}

void MainWindow::setState(enum state_t new_state)
{
    state = new_state;
}

void MainWindow::displayGallery(QString filepath)
{
    QImage currentPicture;

    currentPicture.load(filepath);
    instance->ui->cameraLabel->setPixmap(QPixmap::fromImage(currentPicture));
    showCamera();
}

void MainWindow::displayCountDown(int count)
{
    QImage  currentPicture;
    QString filepath;

    switch(count){
    case 5:
        filepath = "/home/pi/countdown/5.jpg";
        break;
    case 4:
        filepath = "/home/pi/countdown/4.jpg";
        break;
    case 3:
        filepath = "/home/pi/countdown/3.jpg";
        break;
    case 2:
        filepath = "/home/pi/countdown/2.jpg";
        break;
    case 1:
        filepath = "/home/pi/countdown/1.jpg";
        break;
    default:
        qDebug() << "camera count wrong value";
    }

    currentPicture.load(filepath);
    instance->ui->cameraLabel->setPixmap(QPixmap::fromImage(currentPicture));
    showCamera();
}


void MainWindow::delay(int seconds)
{
    QTime dieTime= QTime::currentTime().addSecs(seconds);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::showImageGallery()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::showIntro()
{
    ui->stackedWidget->setCurrentIndex(1);

}

void MainWindow::showCamera()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::keyPressEvent(QKeyEvent * event)
{
    Q_UNUSED(event);
    SettingsDialog::getInstance()->exec();
}
