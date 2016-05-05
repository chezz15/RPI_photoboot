#include "mainwindow.h"
#include "button_lib.h"
#include <QApplication>


volatile int eventCounter = 0;

static void button_pressed_callback(void) {
   eventCounter++;
   //printf("Button Pressed!\r\n");
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    if (lib_init() < 0) {
        //printf ("Unable to setup wiringPi\r\n");
        return 1;
    }

    button_init(button_pressed_callback);

    return a.exec();
}
