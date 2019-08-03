
#include "MyParse.h"
#include <qDebug>

MyParse::MyParse(/* args */)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < PARSE_DATA_LEN; j++)
        {
            drawData[i].data[j] = 50;
            // orginalData[i].data[j] = 0;
        }
        for (int j = 0; j < FILTER_DATA_LEN; j++)
        {
            /* code */
            filterData[i].data[j] = 50;
        }

        drawData[i].position = 0;
        filterData[i].position = 0;
        // orginalData[i].position = 0;
        f[i] = nullptr;
        txtOutput[i] = nullptr;
    }
}

MyParse::~MyParse()
{
}

long MyParse::getADS1294Value(unsigned char *data)
{
    long temp = 0;

    temp = data[0] & 0x7F;
    temp = (temp << 8) | data[1];
    temp = (temp << 8) | data[2];
    if ((data[0] & 0x80) != 0)
    {
        temp |= 0xFF800000;
    }
    else
    {
        //        qDebug()<<temp;
    }

    return temp;
}
long MyParse::getADS1294Value(unsigned char *data, int id)
{
    long temp = getADS1294Value(data);
    putDrawData(temp, id);
    putOriginalData(temp, id);
    return temp;
}

void MyParse::putDrawData(long val, int id)
{
//    int value = val / 167773 + 50;
    int position = drawData[id].position;
    drawData[id].position = position = (position + PARSE_DATA_LEN - 1) % PARSE_DATA_LEN;
    drawData[id].data[position] = (val / 167773.0)*10 + 50;
//    filter50HZ(value, id);
    // if ((drawData[id].data[position] > 80) || (drawData[id].data[position] < 20))
    // {
    //     qDebug()<<drawData[id].data[position];
    // }
}
void MyParse::putOriginalData(long val, int id)
{
    // int position = orginalData[id].position;
    // orginalData[id].data[position] = val;
    // orginalData[id].position = (position + 1) % PARSE_DATA_LEN;
    if (txtOutput[id] != nullptr)
    {
        *txtOutput[id] << val << endl;
    }
}

int *MyParse::getDrawData(int &p, int id)
{
    p = drawData[id].position;

    return (int *)drawData[id].data;
}

int MyParse::filterHighPass(int data, int id)
{
    int val = 0;
    return data + id;
}

int MyParse::filter50HZ(int data, int id)
{

    filterHighPass(data, id);
    return 0;
}

bool MyParse::begin(QString path, QString timeStr)
{
    f[0] = new QFile(path + "\\data" + QString::number(0) + " " + timeStr + ".txt");
    f[1] = new QFile(path + "\\data" + QString::number(1) + " " + timeStr + ".txt");
    f[2] = new QFile(path + "\\data" + QString::number(2) + " " + timeStr + ".txt");

    for (unsigned char i = 0; i < 3; i++)
    {
        /* code */
        if (!f[i]->open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug() << timeStr;
            qDebug() << f[i]->fileName() << "fail";
            qDebug() << f[i]->exists();
            return false;
        }
        txtOutput[i] = new QTextStream(f[i]);
        // *txtOutput[i] << timeStr << endl;
    }
    return true;
}

void MyParse::end(void)
{
    for (unsigned char i = 0; i < 3; i++)
    {
        /* code */
        if (f[i] != nullptr)
        {
            f[i]->close();
            delete f[i];
            f[i] = nullptr;
        }
        if (txtOutput[i] != nullptr)
        {
            delete txtOutput[i];
            txtOutput[i] = nullptr;
        }
    }
}
