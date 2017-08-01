/**
 * @skyasker    At: 2017.07.12
 */

#include <stdio.h>
#include <stdlib.h>     // system()
#include <unistd.h>     // sleep() | STDIN_FILENO


// 自定义头文件
#include "utilities.h"       // bool | kbhit()
#include "snake.h"


int main(void)
{
    // 欢迎界面
    greeting();

    // TODO: 播放音乐函数

    // 键盘检测：若是回车继续执行
    iskey('b');

    // TODO: 暂停音乐播放

    // 清空欢迎界面
    system("clear");

    // 用随机数初始化蛇的位置
    init_snake();

    // 进入游戏界面
    while (TRUE)
    {
        // 检测是否有键盘输入改变方向
        change_direction();

        // 清除上一次移动的快照
        system("clear");

        // 把蛇移动到下一位置
        move_snake();

        // 判断此位置蛇是否死亡
        if (is_snake_die()) {
            printf("\n\n\tOOPS!!! SNAKE DEAD.\n\n  \n");
            break;
        }
        
        // 检测此位置是否有食物可吃
        eat_a_food();

        // 若食物成功被吃则生产一个新的食物
        create_food();

        // 绘制本次移动快照
        print_snapshot();

        sleep(1);
    }

    return 0;
}
