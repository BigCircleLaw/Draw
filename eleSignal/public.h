
#ifndef _PUBLIC_H
#define _PUBLIC_H

#define MSG_START_TAG 0xFF
#define MSG_END_TAG 0xFE
#define MSG_TRANSLATE_TAG 0xFD //转义字符

#define PLOT_WIDTH 500
#define PLOT_HEIGHT 100

#define MSG_MAX_LENGTH_ALL 50 //消息包最大长度，不是内容长度
typedef struct _ReceiveData
{
    unsigned char buf[MSG_MAX_LENGTH_ALL];
    unsigned char index;
} ReceiveData;

#endif
