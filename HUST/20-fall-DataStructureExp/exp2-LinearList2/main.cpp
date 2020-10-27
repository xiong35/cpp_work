/**
 * Author:
 *     Xiong35
 * Release Time:
 *     2020/10/13 19:24
 * Description:
 *     This is the program for data structure experiment 1: linear list
 * Github:
 *     https://github.com/xiong35
 */

#include <stdio.h>
#include <stdlib.h>

#include "def.h"
#include "func.h"
#include "menu.h"

int main(void) {
    Lists theLists;
    theLists.length = 0;
    for (int i = 0; i < MAX_LISTS; i++) {
        theLists.lists[i] = NULL;
    }

    while (1) {
        if (showMainMenu(theLists) == 0)
            break;
        getchar();
        printf("\n## press Enter to continue ##\n");
        getchar();
    }

    return 0;
}