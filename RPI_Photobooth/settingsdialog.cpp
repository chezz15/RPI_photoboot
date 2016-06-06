#include "settingsdialog.h"
#include "ui_SettingsDialog.h"
#include "mainwindow.h"
#include <QDialog>
#include <QButtonGroup>
#include <QDebug>

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
    ui->ISOCombo->addItem("100",100);
    ui->ISOCombo->addItem("200",200);
    ui->ISOCombo->addItem("300",300);
    ui->ISOCombo->addItem("400",400);
    ui->ISOCombo->addItem("500",500);
    ui->ISOCombo->addItem("600",600);
    ui->ISOCombo->addItem("700",700);
    ui->ISOCombo->addItem("800",800);
    ui->ISOCombo->setCurrentIndex(3);

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

void SettingsDialog::updateCameraSettings()
{

    qDebug() << "Brightness: "  << instance->ui->brightnessSlider->value();
    qDebug() << "Contrast: "    << instance->ui->contrastSlider->value();
    qDebug() << "ISO: "         << instance->ui->ISOCombo->currentText().toInt();

    MainWindow::getInstance()->getCamera().release();
    MainWindow::getInstance()->getCamera().setBrightness(instance->ui->brightnessSlider->value());
    MainWindow::getInstance()->getCamera().setContrast(instance->ui->contrastSlider->value());
    MainWindow::getInstance()->getCamera().setISO(instance->ui->ISOCombo->currentText().toInt());
    MainWindow::getInstance()->getCamera().open();
}
