/**
 * @skyasker    At:2017.07.14
 */

// 宏定义
#define MAX_SNAKE_LENGTH    30      // 蛇的最大长度
#define BLOCK_WIDTH         3       // 方块的字节宽度
#define BLOCK               "口"
#define NON_BLOCK           "　"    // 圆角空格
#define FOOD                "Ｏ"

// 蛇节点方向
typedef enum {UP = -1, RIGHT = BLOCK_WIDTH, DOWN = 1, LEFT = -BLOCK_WIDTH} direction;


// 功能参看函数定义
void greeting();
void print_snapshot();
void init_snake();
void draw_snake();
void move_snake();
void change_direction();
bool is_snake_die();
void create_food();
void eat_a_food();