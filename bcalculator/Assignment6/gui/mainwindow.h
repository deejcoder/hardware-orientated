#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void serialDataReady();

private slots:

    void on_stepperPower_clicked();

    void on_checkBox_toggled(bool checked);

    void on_stepperSpeed_valueChanged(int value);

    void on_ledgPower_toggled(bool checked);

    void on_ledbPower_toggled(bool checked);

    void on_servoSpeed_valueChanged(int value);

    void on_ultraPower_toggled(bool checked);

    void on_lcdMsg_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;

};

#endif // MAINWINDOW_H
