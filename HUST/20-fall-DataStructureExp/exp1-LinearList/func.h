#ifndef __FUNCS_OF_LINEARLIST
#define __FUNCS_OF_LINEARLIST

#include "def.h"

status InitList(SqList& L);

status DestroyList(SqList& L);

status ClearList(SqList& L);

status ListEmpty(SqList L);

status ListLength(SqList L);

status GetElem(SqList L, int i, ElemType& e);

status LocateElem(SqList L, ElemType e);

status PriorElem(SqList L, ElemType e, ElemType& pre);

status NextElem(SqList L, ElemType e, ElemType& next);

status ListInsert(SqList& L, int i, ElemType e);

status ListDelete(SqList& L, int i, ElemType& e);

status ListTraverse(SqList L);

status SaveList(SqList L, char FileName[]);

status LoadList(SqList& L, char FileName[]);

status AddList(LISTS& Lists, char ListName[]);

status RemoveList(LISTS& Lists, char ListName[]);

int LocateList(LISTS Lists, char ListName[]);

int strcmp(char* a, char* b);

#endif  // !__FUNCS_OF_LINEARLIST