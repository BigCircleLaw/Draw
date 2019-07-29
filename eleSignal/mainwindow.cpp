#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_pressed()
{
    static int count = 0;
    ui->startButton->setText("开始");
    ui->serialPortBox->clear();
    auto infos = QSerialPortInfo::availablePorts();
    for(const QSerialPortInfo &info : infos)
    {
        ui->serialPortBox->addItem(info.portName());
        ui->textBrowser->setText(QString::number(info.productIdentifier()));
        qDebug()<<info.portName();

    }
//    ui->serialPortBox->addItem(QString::number(count));
    count++;
}

void MainWindow::on_startButton_released()
{
    ui->startButton->setText("结束");

}
