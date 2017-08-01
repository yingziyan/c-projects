#ifndef BASE_H
#define BASE_H

#define BLOCK_WIDTH         3       // 方块的字节宽度
#define BLOCK               "口"
#define NON_BLOCK           "　"    // 圆角空格
#define MAN_BLOCK           "＋"

const int UP    = -1;
const int DOWN  =  1;
const int RIGHT =  3;
const int LEFT  = -3;

typedef int status;

typedef struct {
    int x;
    int y;
} position;

// 函数
int kbhit();

#endif