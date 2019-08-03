/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *startButton;
    QComboBox *serialPortBox;
    QTextBrowser *textBrowser;
    QPushButton *beginButton;
    QPushButton *endButton;
    QLabel *label;
    QLineEdit *pathText;
    QPushButton *startSave;
    QPushButton *endSave;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1000, 500);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setGeometry(QRect(40, 40, 75, 23));
        serialPortBox = new QComboBox(centralWidget);
        serialPortBox->setObjectName(QStringLiteral("serialPortBox"));
        serialPortBox->setGeometry(QRect(180, 40, 75, 23));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(40, 160, 220, 260));
        beginButton = new QPushButton(centralWidget);
        beginButton->setObjectName(QStringLiteral("beginButton"));
        beginButton->setEnabled(true);
        beginButton->setGeometry(QRect(40, 80, 75, 23));
        endButton = new QPushButton(centralWidget);
        endButton->setObjectName(QStringLiteral("endButton"));
        endButton->setEnabled(false);
        endButton->setGeometry(QRect(180, 80, 75, 23));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 10, 111, 20));
        pathText = new QLineEdit(centralWidget);
        pathText->setObjectName(QStringLiteral("pathText"));
        pathText->setGeometry(QRect(180, 10, 681, 20));
        pathText->setMaximumSize(QSize(681, 20));
        startSave = new QPushButton(centralWidget);
        startSave->setObjectName(QStringLiteral("startSave"));
        startSave->setEnabled(false);
        startSave->setGeometry(QRect(40, 120, 75, 23));
        endSave = new QPushButton(centralWidget);
        endSave->setObjectName(QStringLiteral("endSave"));
        endSave->setEnabled(false);
        endSave->setGeometry(QRect(180, 120, 75, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1000, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        startButton->setText(QApplication::translate("MainWindow", "\345\210\267\346\226\260\344\270\262\345\217\243", Q_NULLPTR));
        serialPortBox->setCurrentText(QString());
        beginButton->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213", Q_NULLPTR));
        endButton->setText(QApplication::translate("MainWindow", "\347\273\223\346\235\237", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\350\276\223\345\205\245\346\226\207\344\273\266\344\277\235\345\255\230\345\234\260\345\235\200\357\274\232", Q_NULLPTR));
        startSave->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\344\277\235\345\255\230", Q_NULLPTR));
        endSave->setText(QApplication::translate("MainWindow", "\347\273\223\346\235\237\344\277\235\345\255\230", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
