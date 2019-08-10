#ifndef _MYPARSE_H
#define _MYPARSE_H

#include <QString>
#include <QFile>
#include <QTextStream>

#define DRAW_STEP_VAL   2
#define PARSE_DATA_LEN 2000
typedef struct _DrawData
{
    /* data */
    int data[PARSE_DATA_LEN];
    unsigned int position;
} DrawData;

#define FILTER_DATA_LEN 50
typedef struct _FilterData
{
    /* data */
    double data[FILTER_DATA_LEN];
    unsigned int position;
} FilterData;

// typedef struct _OriginalData
// {
//     /* data */
//     long data[PARSE_DATA_LEN];
//     unsigned int position;
// } OriginalData;

class MyParse
{
private:
    /* data */
    DrawData drawData[3];
    FilterData filterData[3];
    double multiple[3];
    // OriginalData orginalData[3];
    double coff[3], coff2;
    QFile *f[3];
    QTextStream *txtOutput[3];
    double drawDivisor;
    int drawBase;

    void putDrawData(long val, int id);
    void putOriginalData(long val, int id);
    double filterHighPass(double data, int id);
    double filterLowPass(double data, int id);
    double filter50HZ(double data, int id);

public:
    MyParse(/* args */);
    ~MyParse();

    long getADS1294Value(unsigned char *data);
    long getADS1294Value(unsigned char *data, int id);
    int *getDrawData(int &p, int id);
    bool begin(QString path, QString timeStr);
    void end(void);
};

#endif
