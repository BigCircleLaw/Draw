#ifndef _MYPARSE_H
#define _MYPARSE_H

#include <QString>
#include <QFile>
#include <QTextStream>

#define PARSE_DATA_LEN 1000
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
    int data[FILTER_DATA_LEN];
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
    // OriginalData orginalData[3];
    QFile *f[3];
    QTextStream *txtOutput[3];

    void putDrawData(long val, int id);
    void putOriginalData(long val, int id);
    int filterHighPass(int data, int id);
    int filter50HZ(int data, int id);

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
