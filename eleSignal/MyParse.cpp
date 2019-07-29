
#include "MyParse.h"

long getADS1294Value(unsigned char *data)
{
    long temp = 0;
    temp = data[0] & 0x7F;
    temp = (temp << 8) | data[1];
    temp = (temp << 8) | data[2];
    if ((data[0] & 0x80) != 0)
    {
        temp |= 0x80000000;
    }
    return temp;
}
