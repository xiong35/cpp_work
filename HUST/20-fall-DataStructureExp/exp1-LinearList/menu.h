
#ifndef __MENU_FOR_LINEARLIST
#define __MENU_FOR_LINEARLIST

#include <stdio.h>
#include <windows.h>
#include "def.h"
#include "func.h"

#define CLEAR "cls"

int showMainMenu(LISTS& lists);

int getIndByName(const LISTS& lists);

void mutateList(LISTS& lists);

void showListsNames(const LISTS& lists);

#endif  // !__MENU_FOR_LINEARLIST