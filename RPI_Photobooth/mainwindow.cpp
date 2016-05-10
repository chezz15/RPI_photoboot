#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "button_lib.h"
#include <functional>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //button_init(&MainWindow::button_pressed_callback);

    std::function<void(MainWindow&)> f = &MainWindow::button_pressed_callback;

    ptr_fun = f.target<function_t>();
    qDebug() << &MainWindow::button_pressed_callback;
    button_init(ptr_fun);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::button_pressed_callback()
{
    ui->label->setText("Button pressed!");
}

