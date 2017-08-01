/**
 * @skyasker    At: 2017.07.14
 */

#include <stdio.h>
#include <stdlib.h>     // srand() | rand()
#include <string.h>     // strncpy()
#include <time.h>       // time()


#include "utilities.h"       // bool | kbhit()
#include "snake.h"


// 变量申明
// 初始化快照
char snapshot[21][20 * BLOCK_WIDTH + 1] = {
    "口口口口口口口口口口口口口口口口口口口口\n",
    "口　　　　　　　　　　　　　　　　　　口\n",
    "口　　　　　　　　　　　　　　　　　　口\n",
    "口　　　　　　　　　　　　　　　　　　口\n",
    "口　　　　　　　　　　　　　　　　　　口\n",
    "口　　　　　　　　　　　　　　　　　　口\n",
    "口　　　　　　　　　　　　　　　　　　口\n",
    "口　　　　　　　　　　　　　　　　　　口\n",
    "口　　　　　　　　　　　　　　　　　　口\n",
    "口　　　　　　　　　　　　　　　　　　口\n",
    "口　　　　　　　　　　　　　　　　　　口\n",
    "口　　　　　　　　　　　　　　　　　　口\n",
    "口　　　　　　　　　　　　　　　　　　口\n",
    "口　　　　　　　　　　　　　　　　　　口\n",
    "口　　　　　　　　　　　　　　　　　　口\n",
    "口　　　　　　　　　　　　　　　　　　口\n",
    "口　　　　　　　　　　　　　　　　　　口\n",
    "口　　　　　　　　　　　　　　　　　　口\n",
    "口　　　　　　　　　　　　　　　　　　口\n",            
    "口口口口口口口口口口口口口口口口口口口口\n",
    "\n"
}; 

// 用数组表示蛇的信息，三元组数组，数组长度表示当前蛇的长度
// 三元组前两两个元素表示蛇的位置，最后一个元素表示蛇的该节点移动方向
int snake[MAX_SNAKE_LENGTH][3] = {0};

// 蛇的长度
int snake_length = 3;

// 蛇的当前移动方向
direction current_direction = LEFT;

// 是否存在食物
bool is_has_food = FALSE;

// 定义食物
int food_x, food_y;

// 到边指示
bool is_at_edge = FALSE;

// 得分
int score = 0;


// 函数定义
/**
 * @parameter: [void]
 * @return: [void]
 * @description: 打印问候语
 */
void greeting()
{
    printf("\n    [Hello! Welcom]\n");
    printf("\n  输入 b 回车开始游戏\n\n");
}


/**
 * @parameter: [void]
 * @return: [void]
 * @description: 打印快照
 */
void print_snapshot()
{
    printf("\n[[      @skyasker At: 2017.07.14      ]]\n\n");
    printf("%s", snapshot[0]);
    printf("[[ Score: %3d        Snake Length: %2d ]]\n\n", score, snake_length);
}


/**
* @parameter: [void]
* @return: [void]
* @description: 遍历蛇数组将蛇画到背景上
*/
void draw_snake()
{
    int i;
    for (i = 0; 0 != snake[i][0]; i++)
    {
        // TEST
        // printf("%d %d %d\n", snake[i][0], snake[i][1], snake[i][2]);

        strncpy(&snapshot[snake[i][0]][snake[i][1]], BLOCK, BLOCK_WIDTH);
    }
}


/**
* @parameter: [void]
* @return: [void]
* @description: 产生一个随机位置作为蛇头
*/
void init_snake()
{
    int x, y;

    srand(time(NULL));

    x = rand() % 18 + 1;
    y = rand() % 12 + 5;

    // printf("%d %d", x, y);

    int i = 0;
    for (i = 0; i < 3; i++)
    {
        snake[i][0] = x;                                    // 行
        snake[i][1] = BLOCK_WIDTH * y + i * BLOCK_WIDTH;    // 列
        snake[i][2] = LEFT;                                 // 方向
    }

    // 画蛇
    draw_snake();

}


/**
* @parameter: [void]
* @return: [void]
* @description: 对蛇数组进行处理，从新画蛇
*/
void move_snake()
{
    int last = snake_length - 1;
  
    // 处理蛇尾残留在背景上的数据：方法一
    // int i = 0;
    // for (i = 0; i < snake_length; i++)
    //     strncpy(&snapshot[snake[i][0]][snake[i][1]], NON_BLOCK, BLOCK_WIDTH);

    // 处理蛇尾残留在背景上的数据：方法二
    strncpy(&snapshot[snake[last][0]][snake[last][1]], NON_BLOCK, BLOCK_WIDTH);
    
    // 更新蛇数组，使其符合移动后的位置
    // 处理蛇身的数据
    for (last = snake_length - 1; last > 0; last--)
    {
        snake[last][0] = snake[last - 1][0];
        snake[last][1] = snake[last - 1][1];
        snake[last][2] = snake[last - 1][2];            
    }

    // 处理蛇头的数据
    snake[0][2] = current_direction;
    
    if (LEFT == snake[0][2] || RIGHT == snake[0][2])
        snake[0][1] += snake[0][2];
    else
        snake[0][0] += snake[0][2];

    // 将新蛇画到快照上
    draw_snake();
}


/**
* @parameter: [void]
* @return: [void]
* @description: 通过上下左右按键来改变蛇的移动方向
*/
void change_direction()
{
    direction current = snake[0][2];
    switch (kbhit())
    {
        case 'w':
            if (current == UP || current == DOWN)
                break;
            current_direction = UP;
            is_at_edge = FALSE; // 参看 is_snake_die() 到边不意味着蛇死了，如果此时改变方向，到边属性将被置为 FALSE            
            break;
        case 's':
            if (current == UP || current == DOWN)
                break;            
            current_direction = DOWN;
            is_at_edge = FALSE;
            break;
        case 'a':
            if (current == LEFT || current == RIGHT)
                break;
            current_direction = LEFT;
            is_at_edge = FALSE;            
            break;
        case 'd':
            if (current == LEFT || current == RIGHT)
                break;        
            current_direction = RIGHT;
            is_at_edge = FALSE;
    }
}


/**
* @parameter: [void]
* @return: [bool]
* @description: 通过对下一个蛇头位置的判断确定蛇是否死亡
*/
bool is_snake_die()
{
    if (is_at_edge)
        return TRUE;

    if (LEFT == snake[0][2] || RIGHT == snake[0][2])
    {
        if(0 == strncmp(&snapshot[snake[0][0]][snake[0][1] + snake[0][2]], BLOCK, BLOCK_WIDTH))
            is_at_edge = TRUE;
    }
    else
    {
        if(0 == strncmp(&snapshot[snake[0][0] + snake[0][2]][snake[0][1]], BLOCK, BLOCK_WIDTH))
            is_at_edge = TRUE;
    }
    return FALSE;
}


/**
* @parameter: [void]
* @return: [void]
* @description: 检测食物是否被吃，如果是则随机再产生一个
*/
void create_food()
{
    // 检查食物存在状态
    if (is_has_food)
        return;

    // 如果食物不存在，产生食物
    srand(time(NULL));

    // 通过对随机产生的位置进行检查确保食物位置不在蛇上
    while (0 == strncmp(&snapshot[food_x = rand() % 18 + 1][food_y = (rand() % 18 + 1) * BLOCK_WIDTH], BLOCK, BLOCK_WIDTH))
        ;

    // 把食物画到快照上
    strncpy(&snapshot[food_x][food_y], FOOD, BLOCK_WIDTH);

    // 改变是否食物存在状态
    is_has_food = TRUE;
}


/**
* @parameter: [void]
* @return: [void]
* @description: 检测蛇头是否与食物重合，如果重合表示蛇吃了一个食物
*/
void eat_a_food()
{
    if (food_x == snake[0][0] && food_y == snake[0][1])
    {
        is_has_food = FALSE;
        if (snake_length < MAX_SNAKE_LENGTH) {
            
            // 给蛇增加一节: 想法多余，虽能实现但过程多余
            // if (snake[snake_length - 1][2] == UP || snake[snake_length - 1][2] == DOWN)
            // {
            //     snake[snake_length][0] = snake[snake_length - 1][0] - snake[snake_length - 1][2];
            //     snake[snake_length][1] = snake[snake_length - 1][1];
            //     snake[snake_length][2] = snake[snake_length - 1][2];
            // }
            // if (snake[snake_length - 1][2] == LEFT || snake[snake_length - 1][2] == RIGHT)
            // {
            //     snake[snake_length][0] = snake[snake_length - 1][0];
            //     snake[snake_length][1] = snake[snake_length - 1][1] - snake[snake_length - 1][2];
            //     snake[snake_length][2] = snake[snake_length - 1][2];
            // }

            // 给蛇增加一节：参看 snake_move() ，当蛇移动时，最后一节将被前一节赋值，又由于蛇的此节
            // 从增加到被覆盖并没有被画到快照上，因此其初始化为何值并无要求，但要注意三元组的第二个元素必须是
            // 方块字节数的倍数，因为此数据被用来清空一次快照。
            snake[snake_length][0] = snake[snake_length][1] = snake[snake_length][2] = BLOCK_WIDTH;

            // 蛇长加一
            ++snake_length;

            // 得分加十
            score += 10;
        }
    }
}
