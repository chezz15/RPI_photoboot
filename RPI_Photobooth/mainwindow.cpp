#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "button_lib.h"
#include <functional>
#include <QDebug>

MainWindow* MainWindow::instance = nullptr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    button_init(&button_pressed_callback);
}

MainWindow::~MainWindow()
{
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
    instance->ui->label->setText("Button pressed!");
}
