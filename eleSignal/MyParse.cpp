
#include "MyParse.h"

MyParse::MyParse(/* args */)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < PARSE_DATA_LEN; j++)
        {
            drawData[i].data[j] = 0;
            orginalData[i].data[j] = 0;
        }
        drawData[i].position = 0;
        orginalData[i].position = 0;
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
    int position = drawData[id].position;
    drawData[id].data[position] = val / 83, 887 + 50;
    drawData[id].position = (position + PARSE_DATA_LEN - 1) % PARSE_DATA_LEN;
}
void MyParse::putOriginalData(long val, int id)
{
    int position = orginalData[id].position;
    orginalData[id].data[position] = val;
    orginalData[id].position = (position + 1) % PARSE_DATA_LEN;
}

int *MyParse::getDrawData(int &p, int id)
{
    p = drawData[id].position;

    return (int *)drawData[id].data;
}
