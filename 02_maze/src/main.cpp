/**
 * @skyasker    At: 2017.07.29
 */

/**
 * 目标:
 * 了解 c++ 基本类库的基本用法
 * 巩固 c++ 的基本语法
 * 了解 c++ 项目的基本结构
 * 锻炼自己分析问题解决问题的能力
 */
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <unistd.h>
#include "base.h"
#include "map.h"
#include "man.h"


using namespace std;

int main()
{

    vector<string> maps;
    maps.push_back("01");
    maps.push_back("02");
    maps.push_back("03");

    time_t start, over;

    // 欢迎
    system("clear");
    cout << "\n\n" << endl;
    cout << "    [[ UP: w  DOWN: s  LEFT: a  RIGHT: d  ]]" << endl;
    cout << "    [[ GAME WILL START AT 3 SECONDS LATER ]]\n\n\n" << endl;
    cout << "\n\n" << endl;
    sleep(4);

    vector<string>::iterator iter = maps.begin();
    for (; iter != maps.end(); iter ++)
    {
        // 初始化 map
        Map map(*iter);

        // 初始化 man
        Man man(map);

        // 迷宫初始化完成, 打印迷宫
        map.printMap();

        // 开始计时
        start = time(NULL);

        // 检测键盘输入
        while (true) {
            switch (kbhit())
            {
                case 'w':
                    man.move(map, UP);
                    break;
                case 's':
                    man.move(map, DOWN);
                    break;
                case 'a':
                    man.move(map, LEFT);
                    break;
                case 'd':
                    man.move(map, RIGHT);
                    break;
            }

            // 判断小人是否走出迷宫
            if (man.isOut(map))
            {
                system("clear");
                over = time(NULL);

                cout << "\n\n" << endl;
                cout << "    [[ TIME LENGTH: " << right << setw(20) << over - start << "]]" << endl;
                cout << "    [[ TOTAL STEPS: " << right << setw(20) << man.getSteps() << "]]" << endl;
                cout << "    [[ 3 SECONDS LATER GO TO NEXT LEVEL ]]" << endl;
                cout << "\n\n" << endl;

                sleep(3);    
                break;
            }
        }

        system("clear");
        cout << "\n\n" << endl;
        cout << "[[        !! CONGRATULATIONS !!       ]]" << endl;
        cout << "[[ !! YOU ALREADY PASSED ALL LEVELS!! ]]" << endl;
        cout << "\n\n" << endl;
        
    }

    return 0;
}