#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new QSerialPort("COM10", this);
    connect(serial, SIGNAL(readyRead()), SLOT(serialDataReady()));
    if(!serial->open(QIODevice::ReadWrite)) {
        printf("fatal");
        return;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::serialDataReady()
{
}

void MainWindow::on_stepperPower_clicked()
{
    serial->write(qPrintable('S'));
    serial->write("\n");
}

void MainWindow::on_checkBox_toggled(bool checked)
{
#pragma unused checked
    serial->write(qPrintable('T'));
    serial->write("\n");
}

void MainWindow::on_stepperSpeed_valueChanged(int value)
{
    QString string = QString("D %1\n").arg(value);
    serial->write(qPrintable(string));
}

void MainWindow::on_ledgPower_toggled(bool checked)
{
    serial->write(qPrintable('G'));
    serial->write("\n");
}

void MainWindow::on_ledbPower_toggled(bool checked)
{
    serial->write(qPrintable('B'));
    serial->write("\n");
}

void MainWindow::on_pushButton_clicked()
{

}


void MainWindow::on_pushButton_clicked(bool checked)
{

}
