
#ifndef __DEFS_OF_LINEARLIST
#define __DEFS_OF_LINEARLIST

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType;  //数据元素类型定义

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef int ElemType;

typedef struct LNode {  //单链表（链式结构）结点的定义
    ElemType data;
    struct LNode* next;
} LNode, *LinkList;

#endif  // !__DEFS_OF_LINEARLIST
