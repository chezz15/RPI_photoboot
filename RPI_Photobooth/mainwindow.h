#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
typedef void function_t(void);

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ~MainWindow();
    static MainWindow* getInstance();

private:
    MainWindow(QWidget *parent = 0);
    static MainWindow* instance;
    Ui::MainWindow *ui;
    static void button_pressed_callback();

};

#endif // MAINWINDOW_H
