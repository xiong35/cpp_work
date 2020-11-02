#ifndef _TREE_DEFS
#define _TREE_DEFS

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define MAX_TREES 10

typedef int status;
typedef int KeyType;

typedef struct {
    KeyType key;
    char others[20];
} TElemType;  //二叉树结点类型定义

typedef struct BiTNode {  //二叉链表结点的定义
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

typedef struct {
    BiTree trees[MAX_TREES];
    char names[MAX_TREES][30];
    int length;
} Trees;

#endif  // !_TREE_DEFS