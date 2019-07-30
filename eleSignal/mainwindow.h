#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "public.h"

#include <QMainWindow>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QPixmap>
#include <QPainter>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *);

private slots:

    void on_startButton_pressed();

    void on_startButton_released();

    void on_beginButton_pressed();

    void on_endButton_pressed();

    void serialPut();

    void translate(unsigned char * buf);
    void Receiver_put(unsigned char data);
    void RequestHandle(unsigned char*  data, unsigned char len);

    void on_pushButton_pressed();

    void on_pushButton_released();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    QPixmap *pix[3];
    QPainter *plot[3];

    ReceiveData buf;//存放原始数据
    ReceiveData package;//存放转义后数据

    long currentValue[3];
};


#endif // MAINWINDOW_H
