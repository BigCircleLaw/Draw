#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = nullptr;

    for (int i = 0; i < 3; i++)
    {
        pix[i] = new QPixmap(PLOT_WIDTH, PLOT_HEIGHT);
        pix[i]->fill(Qt::black);
        plot[i] = new QPainter(pix[i]);
    }
    plot[0]->setPen(QPen(QColor(Qt::yellow), 1));
    plot[1]->setPen(QPen(QColor(Qt::blue), 1));
    plot[2]->setPen(QPen(QColor(Qt::green), 1));
    drawTim = new QTimer(this);
    connect(drawTim, SIGNAL(timeout()), this, SLOT(drawPlot()));
    drawTim->start(30);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawPlot()
{
    int *data = nullptr, startPosition;
    data = myparse.getDrawData(startPosition,1);
    pix[0]->fill(Qt::black);
    for (int i = 0; i < (pix[0]->width() - 1); i++)
    {
        int position = (startPosition + i) % PARSE_DATA_LEN;
        plot[0]->drawLine(i,data[position],i+1, data[(position + 1) % PARSE_DATA_LEN]);
        qDebug() << data[position] << data[(position + 1) % PARSE_DATA_LEN];
    }
    repaint();
//    QDateTime time = QDateTime::currentDateTime();
//    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
//    ui->textBrowser->setText(str);
}
void MainWindow::on_pushButton_pressed()
{
//    plot[0]->drawLine(0,0,499, 99);

//    plot[1]->drawRect(100,10,300,80);
//    plot[2]->drawEllipse(225,25,50,50);
//    repaint();
}

void MainWindow::on_pushButton_released()
{
//     for (int i = 0; i < 3; i++)
//     {
//         pix[i]->fill(Qt::black);
//     }
//     repaint();
}

void MainWindow::on_startButton_pressed()
{
    static int count = 0;
    ui->serialPortBox->clear();
    auto infos = QSerialPortInfo::availablePorts();
    for(const QSerialPortInfo &info : infos)
    {
        ui->serialPortBox->addItem(info.portName());
        ui->textBrowser->setText(QString::number(info.productIdentifier()) + "\r\n");
        qDebug()<<info.portName()<<", PID:"<<info.productIdentifier() << ", VID:" << info.vendorIdentifier();

    }
    
    count++;
}

void MainWindow::on_startButton_released()
{
//    ui->startButton->setText("结束");
}

void MainWindow::on_beginButton_pressed()
{
    if(serial == nullptr)
        serial = new QSerialPort();

    if(serial->isOpen())//如果串口已经打开了 先给他关闭了
    {
        serial->clear();
        serial->close();
    }

    qDebug()<<ui->serialPortBox->currentText();
    serial->setPortName(ui->serialPortBox->currentText());

    if(!serial->open(QIODevice::ReadWrite))//用ReadWrite 的模式尝试打开串口
    {
        qDebug()<<ui->serialPortBox->currentText()<<"打开失败!";
        return;
    }
    //打开成功
    qDebug()<<serial->isOpen();
    serial->setBaudRate(QSerialPort::Baud115200,QSerialPort::AllDirections);//设置波特率和读写方向
    serial->setDataBits(QSerialPort::Data8);      //数据位为8位
    serial->setFlowControl(QSerialPort::NoFlowControl);//无流控制
    serial->setParity(QSerialPort::NoParity); //无校验位
    serial->setStopBits(QSerialPort::OneStop); //一位停止位
    serial->setDataTerminalReady(true);
    serial->setReadBufferSize(2048);
    connect(serial,SIGNAL(readyRead()),this,SLOT(serialPut()));
}

void MainWindow::on_endButton_pressed()
{
    if(serial != nullptr)
    {
        if(serial->isOpen())
        {

            serial->clear();
            serial->close();
            qDebug()<<serial->isOpen();
        }
        delete serial;
        serial = nullptr;
    }
}

void MainWindow::serialPut()
{
    QByteArray temp = serial->readAll();
//    qDebug()<<temp.size();
    ui->textBrowser->setText(QString::number(temp.size()));
    for (int i = 0; i < temp.size(); i++)
    {
//        ui->textBrowser->append(QString::number((unsigned char)temp[i], 16));
//        ui->textBrowser->append(" ");
        Receiver_put((unsigned char)temp[i]);
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    p.drawPixmap(370, 40, PLOT_WIDTH, PLOT_HEIGHT, *pix[0]);
    p.drawPixmap(370, 180, PLOT_WIDTH, PLOT_HEIGHT, *pix[1]);
    p.drawPixmap(370, 320, PLOT_WIDTH, PLOT_HEIGHT, *pix[2]);
}

void MainWindow::RequestHandle(unsigned char*  data, unsigned char len)
{
    if(9 == len)
    {

        for (int i = 0; i < 3; i++)
        {
            currentValue[i] = myparse.getADS1294Value(data + i * 3,i);
//            ui->textBrowser->append(QString::number(currentValue[i]));
        }
//        qDebug()<<currentValue[0]<<currentValue[1]<<currentValue[2];
    }
    else
    {
        switch (data[0])
        {
        }
    }
}

/**
  * @brief  判断一个包是否完成
  * @param  data：字节数据
  * @retval None
*/
void MainWindow::Receiver_put(unsigned char data)
{
   if(0xFF == data)
   {
      this->buf.index = 0;
   }

   this->buf.buf[this->buf.index++] = data;
//#if defined WONDERBITS_STM32||defined WONDERBITS_STM32GUN||defined WONDERBITS_STM32BIG||defined WONDERBITS_STM32BIG_GUN
   if (this->buf.index >= MSG_MAX_LENGTH_ALL)
     this->buf.index = MSG_MAX_LENGTH_ALL - 1;
//#endif

   if(0xFE == data)
   {
     translate(this->buf.buf+1);//掠过包起始位
     {
       RequestHandle(this->package.buf, this->package.index);
     }
   }
}



/**
  * @brief  数据转义
* @param  buf:去掉包起始位的缓存区
  * @retval None
*/
void MainWindow::translate(unsigned char * buf)
{
  int i;
  unsigned char DataBuffer;
  unsigned char index;

  index = 0;
  for (i = 0; buf[i] != MSG_END_TAG; )
  {
      DataBuffer = buf[i++];
      if (DataBuffer == MSG_TRANSLATE_TAG)
        DataBuffer += buf[i++]; //Combine the value that have been broke up(0xFD, 0xFE and 0xFF)
      this->package.buf[index++] = DataBuffer;
  }

  this->package.index = index;
}

