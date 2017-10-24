#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new QSerialPort("COM10", this);
    connect(serial, SIGNAL(readyRead()), SLOT(serialDataReady()));
    if(!serial->open(QIODevice::ReadWrite)) {
        printf("Unable to open the serial port!");
        return;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Recieve a line of data through the serial port, if matches criteria...
void MainWindow::serialDataReady()
{
    if(serial->canReadLine()) {
        char input[80];
        input[strlen(input)-1] = '\0';
        serial->readLine(input, 80);

        char cmd; int time;
        sscanf(input, "%c %d", &cmd, &time);
        switch(cmd) {
        case 'u': //ultra sonic sensor data: distance ready to update
        case 'U': {
            if(time) {
                int distance = (int)rint(0.017*time);
                //limit it to 200. We weren't given a suitable limit? I know it's 5000, but not really practical
                if(distance > 200) distance = 200;
                ui->ultraDistance->setValue(distance);
                //qDebug() << distance; //I used the debugging feature
            }
        }
        }

    }
}
//Slots that push data to the nucleo board through the serial port..
void MainWindow::on_stepperPower_clicked()
{
    serial->write(qPrintable('S'));
    serial->write("\n");
}

void MainWindow::on_checkBox_toggled(bool checked)
{
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

void MainWindow::on_servoSpeed_valueChanged(int value)
{
    QString string = QString("A %1\n").arg(value);
    serial->write(qPrintable(string));
}

void MainWindow::on_ultraPower_toggled(bool checked)
{
    serial->write(qPrintable('U'));
    serial->write("\n");
}

void MainWindow::on_lcdMsg_cursorPositionChanged(int arg1, int arg2)
{
    QString string = QString("M %1\n").arg(ui->lcdMsg->text());
    serial->write(qPrintable(string));
}
