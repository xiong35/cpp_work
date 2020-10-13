
#ifndef __DEF_OF_FUNCS
#define __DEF_OF_FUNCS

#include <stdio.h>
#include <stdlib.h>
#include "def.h"

status InitList(LinkList& L);

status DestroyList(LinkList& L);

status ClearList(LinkList& L);

status ListEmpty(LinkList L);

status GetElem(LinkList L, int i, ElemType& e);

status LocateElem(LinkList L, ElemType e);

status PriorElem(LinkList L, ElemType e, ElemType& pre);

status NextElem(LinkList L, ElemType e, ElemType& next);

status ListInsert(LinkList& L, int i, ElemType e);

status ListDelete(LinkList& L, int i, ElemType& e);

status ListTraverse(LinkList L);

status SaveList(LinkList L, char FileName[]);

int ListLength(LinkList L);

status LoadList(LinkList& L, char FileName[]);

status AddList(Lists& lists, char ListName[]);

int strcmp(char* a, char* b);

status RemoveList(Lists& lists, char ListName[]);

int LocateList(Lists lists, char ListName[]);

#endif  // !__DEF_OF_FUNCS
