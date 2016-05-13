#include "mainwindow.h"
#include "button_lib.h"
#include <QApplication>
#include <iostream>
#include <QDebug>
#include <ctime>
#include <fstream>
#include <iostream>
#include "raspicam.h"


int raspicam_test(void)
{
/*     //Cmaera object
    //Open camera
    //capture
    Camera.grab();
    //allocate memory
    unsigned char *data=new unsigned char[  Camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB )];
    //extract the image in rgb format
    Camera.retrieve ( data,raspicam::RASPICAM_FORMAT_RGB );//get camera image
    //save
    std::ofstream outFile ( "raspicam_image.ppm",std::ios::binary );
    outFile<<"P6\n"<<Camera.getWidth() <<" "<<Camera.getHeight() <<" 255\n";
    outFile.write ( ( char* ) data, Camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB ) );
    qDebug()<< "Image saved at raspicam_image.ppm";
    //free resrources
    delete data;*/
    return 0;
}


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    if (raspicam_test() < 0){
        qDebug() << "Error during raspicam test";
        return -1;
    }

    if (lib_init() < 0) {
        qDebug() << "Error during lib_init";
        return -2;
    }

    MainWindow::getInstance()->show();

    return a.exec();
}

