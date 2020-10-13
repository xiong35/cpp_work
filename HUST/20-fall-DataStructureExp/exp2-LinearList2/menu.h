
#ifndef __MENU_FOR_LINEARLOIST
#define __MENU_FOR_LINEARLOIST

#include <stdio.h>
#include <windows.h>
#include "def.h"
#include "func.h"

#define CLEAR "cls"

int showMainMenu(Lists& lists);

int getIndByName(const Lists& lists);

void mutateList(Lists& lists);

void showListsNames(const Lists& lists);

#endif  // !__MENU_FOR_LINEARLOIST