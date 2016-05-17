#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H
#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    static SettingsDialog* getInstance();
    SettingsDialog(QWidget *parent = 0);
private:
    static SettingsDialog* instance;
    Ui::SettingsDialog *ui;
    void updateCameraSettings();
};

#endif // SETTINGSDIALOG_H
