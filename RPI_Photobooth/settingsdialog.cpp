#include "settingsdialog.h"
#include "ui_SettingsDialog.h"
#include "mainwindow.h"
#include <QDialog>
#include <QButtonGroup>

SettingsDialog* SettingsDialog::instance = nullptr;

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    ui->brightnessSlider->setRange(0,100);
    ui->brightnessSlider->setValue(50);
    ui->contrastSlider->setRange(0,100);
    ui->contrastSlider->setValue(50);
    connect(ui->buttonBox, SIGNAL (accepted()),this, SLOT (updateCameraSettings()));
}

SettingsDialog* SettingsDialog::getInstance()
{
    if(instance == nullptr)
    {
        instance = new SettingsDialog();
    }

    return instance;
}

void SettingsDialog::updateCameraSettings() {
    MainWindow::getInstance()->getCamera().setBrightness(instance->ui->brightnessSlider->value());
    MainWindow::getInstance()->getCamera().setContrast(instance->ui->contrastSlider->value());
}
