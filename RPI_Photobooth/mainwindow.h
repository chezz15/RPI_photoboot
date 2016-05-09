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
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void button_pressed_callback();
     function_t* ptr_fun;
};

#endif // MAINWINDOW_H
