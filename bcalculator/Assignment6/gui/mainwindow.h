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
    void on_pushButton_clicked();

    void on_stepperPower_clicked();

    void on_checkBox_toggled(bool checked);

    void on_stepperSpeed_valueChanged(int value);

    void on_pushButton_clicked(bool checked);

    void on_ledgPower_toggled(bool checked);

    void on_ledbPower_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;

};

#endif // MAINWINDOW_H
