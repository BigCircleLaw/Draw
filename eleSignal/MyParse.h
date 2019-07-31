#ifndef _MYPARSE_H
#define _MYPARSE_H

#define PARSE_DATA_LEN 1000

typedef struct _DrawData
{
    /* data */
    int data[PARSE_DATA_LEN];
    unsigned int position;
} DrawData;

typedef struct _OriginalData
{
    /* data */
    long data[PARSE_DATA_LEN];
    unsigned int position;
} OriginalData;

class MyParse
{
private:
    /* data */
    DrawData drawData[3];
    OriginalData orginalData[3];

    void putDrawData(long val, int id);
    void putOriginalData(long val, int id);

public:
    MyParse(/* args */);
    ~MyParse();

    long getADS1294Value(unsigned char *data);
    long getADS1294Value(unsigned char *data, int id);
    int *getDrawData(int &p, int id);
};

#endif
