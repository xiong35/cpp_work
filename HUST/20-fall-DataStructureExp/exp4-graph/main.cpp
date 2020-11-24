/**
 * Author:
 *     Xiong35
 * Release Time:
 *     2020/11/24 19:24
 * Description:
 *     This is the program for data structure experiment 4: graph
 * Github:
 *     https://github.com/xiong35
 */

#include <stdio.h>

#include "def.h"
#include "menu.h"

int main(void) {
    ALGraph g;
    g.vexnum = 0;
    g.arcnum = 0;
    while (1) {
        if (showMainMenu(g) == 0)
            break;
        getchar();
        printf("\n## press Enter to continue ##\n");
        getchar();
    }

    return 0;
}