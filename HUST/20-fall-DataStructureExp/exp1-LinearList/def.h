
#ifndef __DEFS_OF_LINEARLIST
#define __DEFS_OF_LINEARLIST

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define FILE_NAME "list.dat"

typedef int status;
typedef int ElemType;  //数据元素类型定义

#define LIST_INIT_SIZE 100
#define NAME_LEN 30
#define MAX_LISTS 10

typedef struct {  //顺序表（顺序结构）的定义
    ElemType* elem;
    int length;
    int listsize;
} SqList;

typedef struct {
    char name[NAME_LEN];
    SqList L;
} Elem;

typedef struct {  //线性表的管理表定义
    Elem elem[MAX_LISTS];
    int length;
} LISTS;

#endif  // !__DEFS_OF_LINEARLIST