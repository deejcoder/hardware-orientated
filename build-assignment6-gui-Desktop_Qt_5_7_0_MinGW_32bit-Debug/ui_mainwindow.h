/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QSlider *servoSpeed;
    QLabel *servoPowerL;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QLabel *label;
    QWidget *tab_2;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QSlider *stepperSpeed;
    QRadioButton *stepperClock;
    QCheckBox *stepperPower;
    QLabel *stepperDirL;
    QLabel *stepperPowerL;
    QLabel *stepperSpeedL;
    QRadioButton *stepperAnti;
    QWidget *tab_3;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_3;
    QCheckBox *ultraPower;
    QProgressBar *ultraDistance;
    QLabel *ultraPowerL;
    QLabel *ultraDistanceL;
    QWidget *tab_4;
    QWidget *gridLayoutWidget_4;
    QGridLayout *gridLayout_4;
    QCheckBox *ledgPower;
    QCheckBox *ledbPower;
    QLabel *ledgPowerL;
    QLabel *ledbPowerL;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 300);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 401, 241));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(verticalLayoutWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayoutWidget = new QWidget(tab);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 381, 82));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(30, 30, 30, 30);
        servoSpeed = new QSlider(gridLayoutWidget);
        servoSpeed->setObjectName(QStringLiteral("servoSpeed"));
        servoSpeed->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(servoSpeed, 0, 1, 1, 1);

        servoPowerL = new QLabel(gridLayoutWidget);
        servoPowerL->setObjectName(QStringLiteral("servoPowerL"));

        gridLayout->addWidget(servoPowerL, 0, 0, 1, 1);

        pushButton = new QPushButton(tab);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(60, 120, 75, 23));
        pushButton->setCheckable(false);
        lineEdit = new QLineEdit(tab);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(180, 120, 113, 20));
        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(100, 170, 47, 13));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayoutWidget_2 = new QWidget(tab_2);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(0, 0, 381, 152));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(30);
        gridLayout_2->setVerticalSpacing(20);
        gridLayout_2->setContentsMargins(30, 30, 30, 30);
        stepperSpeed = new QSlider(gridLayoutWidget_2);
        stepperSpeed->setObjectName(QStringLiteral("stepperSpeed"));
        stepperSpeed->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(stepperSpeed, 2, 1, 1, 1);

        stepperClock = new QRadioButton(gridLayoutWidget_2);
        stepperClock->setObjectName(QStringLiteral("stepperClock"));

        gridLayout_2->addWidget(stepperClock, 1, 1, 1, 1);

        stepperPower = new QCheckBox(gridLayoutWidget_2);
        stepperPower->setObjectName(QStringLiteral("stepperPower"));

        gridLayout_2->addWidget(stepperPower, 0, 1, 1, 1);

        stepperDirL = new QLabel(gridLayoutWidget_2);
        stepperDirL->setObjectName(QStringLiteral("stepperDirL"));

        gridLayout_2->addWidget(stepperDirL, 1, 0, 1, 1);

        stepperPowerL = new QLabel(gridLayoutWidget_2);
        stepperPowerL->setObjectName(QStringLiteral("stepperPowerL"));

        gridLayout_2->addWidget(stepperPowerL, 0, 0, 1, 1);

        stepperSpeedL = new QLabel(gridLayoutWidget_2);
        stepperSpeedL->setObjectName(QStringLiteral("stepperSpeedL"));

        gridLayout_2->addWidget(stepperSpeedL, 2, 0, 1, 1);

        stepperAnti = new QRadioButton(gridLayoutWidget_2);
        stepperAnti->setObjectName(QStringLiteral("stepperAnti"));

        gridLayout_2->addWidget(stepperAnti, 1, 2, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        gridLayoutWidget_3 = new QWidget(tab_3);
        gridLayoutWidget_3->setObjectName(QStringLiteral("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(0, 0, 381, 118));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setHorizontalSpacing(30);
        gridLayout_3->setVerticalSpacing(20);
        gridLayout_3->setContentsMargins(30, 30, 30, 30);
        ultraPower = new QCheckBox(gridLayoutWidget_3);
        ultraPower->setObjectName(QStringLiteral("ultraPower"));

        gridLayout_3->addWidget(ultraPower, 0, 1, 1, 1);

        ultraDistance = new QProgressBar(gridLayoutWidget_3);
        ultraDistance->setObjectName(QStringLiteral("ultraDistance"));
        ultraDistance->setValue(24);

        gridLayout_3->addWidget(ultraDistance, 1, 1, 1, 1);

        ultraPowerL = new QLabel(gridLayoutWidget_3);
        ultraPowerL->setObjectName(QStringLiteral("ultraPowerL"));

        gridLayout_3->addWidget(ultraPowerL, 0, 0, 1, 1);

        ultraDistanceL = new QLabel(gridLayoutWidget_3);
        ultraDistanceL->setObjectName(QStringLiteral("ultraDistanceL"));

        gridLayout_3->addWidget(ultraDistanceL, 1, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        gridLayoutWidget_4 = new QWidget(tab_4);
        gridLayoutWidget_4->setObjectName(QStringLiteral("gridLayoutWidget_4"));
        gridLayoutWidget_4->setGeometry(QRect(0, 0, 381, 106));
        gridLayout_4 = new QGridLayout(gridLayoutWidget_4);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setHorizontalSpacing(30);
        gridLayout_4->setVerticalSpacing(20);
        gridLayout_4->setContentsMargins(30, 30, 30, 30);
        ledgPower = new QCheckBox(gridLayoutWidget_4);
        ledgPower->setObjectName(QStringLiteral("ledgPower"));

        gridLayout_4->addWidget(ledgPower, 0, 1, 1, 1);

        ledbPower = new QCheckBox(gridLayoutWidget_4);
        ledbPower->setObjectName(QStringLiteral("ledbPower"));

        gridLayout_4->addWidget(ledbPower, 1, 1, 1, 1);

        ledgPowerL = new QLabel(gridLayoutWidget_4);
        ledgPowerL->setObjectName(QStringLiteral("ledgPowerL"));

        gridLayout_4->addWidget(ledgPowerL, 0, 0, 1, 1);

        ledbPowerL = new QLabel(gridLayoutWidget_4);
        ledbPowerL->setObjectName(QStringLiteral("ledbPowerL"));

        gridLayout_4->addWidget(ledbPowerL, 1, 0, 1, 1);

        tabWidget->addTab(tab_4, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        servoPowerL->setText(QApplication::translate("MainWindow", "Speed", 0));
        pushButton->setText(QApplication::translate("MainWindow", "PushButton", 0));
        label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Servo Motor", 0));
        stepperClock->setText(QApplication::translate("MainWindow", "Clockwise", 0));
        stepperPower->setText(QString());
        stepperDirL->setText(QApplication::translate("MainWindow", "Direction", 0));
        stepperPowerL->setText(QApplication::translate("MainWindow", "Power", 0));
        stepperSpeedL->setText(QApplication::translate("MainWindow", "Speed", 0));
        stepperAnti->setText(QApplication::translate("MainWindow", "Anti-clockwise", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Stepper Motor", 0));
        ultraPower->setText(QString());
        ultraPowerL->setText(QApplication::translate("MainWindow", "Power", 0));
        ultraDistanceL->setText(QApplication::translate("MainWindow", "Distance", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Ultra Sonic Sensor", 0));
        ledgPower->setText(QString());
        ledbPower->setText(QString());
        ledgPowerL->setText(QApplication::translate("MainWindow", "Toggle Green LED", 0));
        ledbPowerL->setText(QApplication::translate("MainWindow", "Toggle Blue LED", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "LED", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
