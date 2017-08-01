/**
 * @skyasker    At: 2017.07.13
 */

#include <stdio.h>          // getchar()
#include <termios.h>        // tcgetattr() | struct termios
#include <unistd.h>         // STDIN_FILENO
#include <fcntl.h>          // fcntl()


#include "base.h"


/**
* @parameter: [void]
* @return: [int]
* @description: Function kbhit() for Linux
*/
int kbhit()
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF)
    {
        // ungetc(ch, stdin);
        return ch;
    }

    return 0;
}
