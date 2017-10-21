#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new QSerialPort("COM7", this);
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
    if(serial->canReadLine())
    {
        char s[80];
        serial->readLine(s,80);
        s[strlen(s)-1] = '\0';
        ui->label->setText(s);

    }
}

void MainWindow::on_pushButton_clicked()
{
    serial->write(qPrintable(ui->lineEdit->text()));
    serial->write("\n");
}

void MainWindow::on_stepperPower_clicked()
{
    serial->write(qPrintable('S'));
    serial->write("\n");
}
