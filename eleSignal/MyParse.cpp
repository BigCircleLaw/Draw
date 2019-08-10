/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-08-05 21:16:21
 * @LastEditTime: 2019-08-10 15:37:58
 * @LastEditors: Please set LastEditors
 */

#include "MyParse.h"
#include "public.h"
#include <qDebug>

#define PI 3.1415926
#define CUT_FRE 1
#define SAMPLE_FRE 1000

#define FILTER_50HZ_LEN 20

MyParse::MyParse(/* args */)
{
    drawDivisor = 16777216.0 / (double)PLOT_HEIGHT;
    drawBase = PLOT_HEIGHT / 2;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < PARSE_DATA_LEN; j++)
        {
            drawData[i].data[j] = drawBase;
            // orginalData[i].data[j] = 0;
        }
        for (int j = 0; j < FILTER_DATA_LEN; j++)
        {
            /* code */
            filterData[i].data[j] = 0;
        }

        drawData[i].position = 0;
        filterData[i].position = 0;
        // orginalData[i].position = 0;
        f[i] = nullptr;
        txtOutput[i] = nullptr;
    }
    //    double RC = 0.5 / 3.1415926 / CUT_FRE;
    //    coff = RC / (RC + 1 / SAMPLE_FRE);
    coff[0] = 1 / (1 + 2 * PI * 10 / SAMPLE_FRE);
    coff[1] = 1 / (1 + 2 * PI * 5 / SAMPLE_FRE);
    coff[2] = 1 / (1 + 2 * PI * 5 / SAMPLE_FRE);
    double b = 2 * PI * 100.0 / SAMPLE_FRE;
    coff2 = b / (1 + b);
    multiple[0] = 500;
    multiple[1] = 200;
    multiple[2] = 200;
}

MyParse::~MyParse()
{
    end();
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
    double value = val / drawDivisor;
    int position = drawData[id].position;
    drawData[id].position = position = (position + PARSE_DATA_LEN - 1) % PARSE_DATA_LEN;

    value = filterHighPass(value, id);

    //    value = filterLowPass(value, id);

    value = filter50HZ(value, id);

    value = value * multiple[id];

    drawData[id].data[position] = value + drawBase;
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

double MyParse::filterHighPass(double data, int id)
{
    static double last_data[3] = {0, 0, 0};
    static double last_out[3] = {0, 0, 0};
    double val = coff[id] * (data - last_data[id] + last_out[id]);
    last_data[id] = data;
    last_out[id] = val;
    return val;
}

double MyParse::filterLowPass(double data, int id)
{
    static double last_out[3] = {0, 0, 0};
    double val = coff2 * data + (1 - coff2) * last_out[id];
    last_out[id] = val;
    return val;
}

double MyParse::filter50HZ(double data, int id)
{
    double *p = filterData[id].data;
    unsigned int position = filterData[id].position;
    position = (position + FILTER_DATA_LEN - 1) % FILTER_DATA_LEN;
    //    p[position] = filterHighPass(data, id);
    p[position] = data;
    filterData[id].position = position;
    //    p[position] = data;
    double sum = 0;
    for (int i = 0; i < FILTER_50HZ_LEN; i += 1)
    {
        sum += p[(position + i) % FILTER_DATA_LEN];
    }
    double val = (sum / FILTER_DATA_LEN + (p[position] - p[(position + FILTER_DATA_LEN) % FILTER_DATA_LEN]) / FILTER_DATA_LEN * (FILTER_DATA_LEN - 1) / 2);
    return val;
}

bool MyParse::begin(QString path, QString timeStr)
{
    f[0] = new QFile(path + "\\" + timeStr + " data" + QString::number(0) + ".txt");
    f[1] = new QFile(path + "\\" + timeStr + " data" + QString::number(1) + ".txt");
    f[2] = new QFile(path + "\\" + timeStr + " data" + QString::number(2) + ".txt");

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
