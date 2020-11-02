
#ifndef __MENU_FOR_TREE
#define __MENU_FOR_TREE

#include <stdio.h>
#include <windows.h>
#include "def.h"
#include "funcs.h"

#define CLEAR "cls"

int showMainMenu(Trees& trees);

int getIndByName(const Trees& trees);

void mutateTree(Trees& trees);

void showTreesNames(const Trees& trees);

#endif  // !__MENU_FOR_TREE