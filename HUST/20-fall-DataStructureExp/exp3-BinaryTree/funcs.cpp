
#include "funcs.h"

#include <stdlib.h>
#include <iostream>

void strcpy(char* dest, const char* src) {
    for (int i = 0; src[i]; i++) {
        dest[i] = src[i];
    }
}

void CreateBiTreeWithInd(BiTree& T, TElemType* definition, int& curDef) {
    if (definition[curDef].key == -1)
        return;

    if (definition[curDef].key != 0) {
        T->lchild = (BiTree)malloc(sizeof(BiTNode));
        strcpy(T->lchild->data.others, definition[curDef].others);
        T->lchild->data.key = definition[curDef].key;
        CreateBiTreeWithInd(T->lchild, definition, ++curDef);
    } else {
        T->lchild = NULL;
        curDef++;
    }

    if (definition[curDef].key != 0) {
        T->rchild = (BiTree)malloc(sizeof(BiTNode));
        strcpy(T->rchild->data.others, definition[curDef].others);
        T->rchild->data.key = definition[curDef].key;
        CreateBiTreeWithInd(T->rchild, definition, ++curDef);
    } else {
        T->rchild = NULL;
        curDef++;
    }
}

int hasDuplicates(TElemType* definition) {
    for (int i = 0; definition[i].key != -1; i++) {
        for (int j = i + 1; definition[j].key != -1; j++) {
            if (definition[i].key == definition[j].key && definition[i].key)
                return TRUE;
        }
    }
    return FALSE;
}

status CreateBiTree(BiTree& T, TElemType definition[]) {
    /*根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，
    如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/

    if (hasDuplicates(definition))
        return ERROR;

    int curDef = 0;
    T = (BiTree)malloc(sizeof(BiTNode));
    strcpy(T->data.others, definition[curDef].others);
    T->data.key = definition[curDef].key;

    CreateBiTreeWithInd(T, definition, ++curDef);

    return OK;
}

status ClearBiTree(BiTree& T) {
    //将二叉树设置成空，并删除所有结点，释放结点空间
    if (!T)
        return OK;

    ClearBiTree(T->lchild);
    ClearBiTree(T->rchild);
    free(T);
    T = NULL;

    return OK;
}

int BiTreeDepth(BiTree T) {
    //求二叉树T的深度
    if (!T)
        return 0;
    int leftDep = BiTreeDepth(T->lchild);
    int rightDep = BiTreeDepth(T->rchild);

    return (leftDep > rightDep ? leftDep : rightDep) + 1;
}

BiTNode* LocateNode(BiTree T, KeyType e) {
    //查找结点
    if (!T)
        return NULL;
    if (T->data.key == e)
        return T;

    BiTree temp = LocateNode(T->lchild, e);
    if (temp)
        return temp;

    return LocateNode(T->rchild, e);
}

status Assign(BiTree& T, KeyType e, TElemType value) {
    //实现结点赋值。此题允许通过增加其它函数辅助实现本关任务
    BiTree target = LocateNode(T, e);
    if (!target)
        return ERROR;
    BiTree duplicate = LocateNode(T, value.key);

    if (duplicate && target != duplicate)
        return ERROR;

    target->data = value;

    return OK;
}

BiTNode* GetSibling(BiTree T, KeyType e) {
    //实现获得兄弟结点
    if (!T)
        return NULL;

    if (!T->rchild || !T->lchild)
        return NULL;

    if (T->lchild->data.key == e)
        return T->rchild;
    if (T->rchild->data.key == e)
        return T->lchild;

    BiTree temp = GetSibling(T->rchild, e);
    if (temp)
        return temp;
    return GetSibling(T->lchild, e);
}

status InsertNode(BiTree& T, KeyType e, int LR, TElemType c) {
    //插入结点。此题允许通过增加其它函数辅助实现本关任务
    BiTree duplicate = LocateNode(T, c.key);
    if (duplicate)
        return ERROR;

    if (LR == -1) {
        BiTree newHead = (BiTree)malloc(sizeof(BiTNode));
        newHead->rchild = T;
        newHead->lchild = NULL;
        newHead->data = c;
        T = newHead;
        return OK;
    }

    BiTree target = LocateNode(T, e);
    if (!target)
        return ERROR;

    BiTree newNode = (BiTree)malloc(sizeof(BiTNode));
    newNode->data = c;

    newNode->rchild = target;
    if (LR == 0) {
        newNode->rchild = target->lchild;
        target->lchild = newNode;
        newNode->lchild = NULL;
    } else {
        newNode->rchild = target->rchild;
        target->rchild = newNode;
        newNode->rchild = NULL;
    }

    return OK;
}

BiTNode* LocateNode_2(BiTree T) {
    if (!T->rchild)
        return T;
    BiTree t = NULL;
    t = LocateNode_2(T->rchild);
    return t;
}

status DeleteNode(BiTree& T, KeyType e) {
    //删除结点。此题允许通过增加其它函数辅助实现本关任务
    BiTree E = T;
    if (E->data.key == e) {
        if (E->lchild && E->rchild) {
            BiTree r_max = LocateNode_2(E->lchild);
            r_max->rchild = E->rchild;
            T = E->lchild;
        } else if (E->lchild) {
            T = E->lchild;
        } else {
            T = E->rchild;
        }
        free(E);
        return OK;
    }
    BiTree t;
    t = LocateNode(T, e);
    if (!t)
        return ERROR;
    int flag;
    if (t->lchild && t->lchild->data.key == e) {
        E = t->lchild;
        flag = 0;
    } else {
        E = t->rchild;
        flag = 1;
    }
    if (E->lchild && E->rchild) {
        BiTree r_max = LocateNode_2(E->lchild);
        r_max->rchild = E->rchild;
        if (flag) {
            t->rchild = E->lchild;
        } else {
            t->lchild = E->lchild;
        }
    } else if (E->lchild) {
        if (flag) {
            t->rchild = E->lchild;
        } else {
            t->lchild = E->lchild;
        }
    } else {
        if (flag) {
            t->rchild = E->rchild;
        } else {
            t->lchild = E->rchild;
        }
    }
    free(E);
    return OK;
}

status PreOrderTraverse(BiTree T, void (*visit)(BiTree)) {
    //先序遍历二叉树T
    if (!T)
        return OK;
    else
        visit(T);
    if (T->lchild)
        PreOrderTraverse(T->lchild, visit);
    if (T->rchild)
        PreOrderTraverse(T->rchild, visit);
    return OK;
}

status InOrderTraverse(BiTree T, void (*visit)(BiTree)) {
    //中序遍历二叉树T
    if (T->lchild)
        InOrderTraverse(T->lchild, visit);
    if (!T)
        return OK;
    else
        visit(T);
    if (T->rchild)
        InOrderTraverse(T->rchild, visit);
    return OK;
}

status PostOrderTraverse(BiTree T, void (*visit)(BiTree)) {
    //后序遍历二叉树T
    if (T->lchild)
        PostOrderTraverse(T->lchild, visit);
    if (T->rchild)
        PostOrderTraverse(T->rchild, visit);
    if (!T)
        return OK;
    else
        visit(T);
    return OK;
}

status LevelOrderTraverse(BiTree T, void (*visit)(BiTree)) {
    //按层遍历二叉树T
    BiTree t[100];
    t[0] = T;
    int i = 0, j = 1;
    for (i = 0; i < j; i++) {
        visit(t[i]);
        if (t[i]->lchild)
            t[j++] = t[i]->lchild;
        if (t[i]->rchild)
            t[j++] = t[i]->rchild;
    }
    return OK;
}

status PreOrderTraverse_1(BiTree T, FILE* fp) {
    //先序遍历存入二叉树T(特殊)
    if (!T) {
        fprintf(fp, "0 NULL ");
        return OK;
    } else
        fprintf(fp, "%d %s ", T->data.key, T->data.others);
    PreOrderTraverse_1(T->lchild, fp);
    PreOrderTraverse_1(T->rchild, fp);
    return OK;
}

int PreOrderTraverse_2(BiTree f, FILE* fp, int flag) {
    TElemType data;
    fscanf(fp, "%d", &data.key);
    fscanf(fp, "%s", data.others);
    if (data.key == 0) {
        if (flag) {
            f->rchild = NULL;
        } else {
            f->lchild = NULL;
        }
        return OK;
    }
    BiTree child = (BiTree)malloc(sizeof(BiTNode));
    child->data.key = data.key;
    strcpy(child->data.others, data.others);
    if (flag) {
        f->rchild = child;
    } else {
        f->lchild = child;
    }
    PreOrderTraverse_2(child, fp, 0);
    PreOrderTraverse_2(child, fp, 1);
    return OK;
}

status SaveBiTree(BiTree T, char FileName[]) {
    //将二叉树的结点数据写入到文件FileName中
    FILE* fp = NULL;
    if ((fp = fopen(FileName, "w")) == NULL) {
        return ERROR;
    }
    status flag = PreOrderTraverse_1(T, fp);
    fclose(fp);
    return flag;
}

status LoadBiTree(BiTree& T, char FileName[]) {
    //读入文件FileName的结点数据，创建二叉树
    if (T)
        return ERROR;
    FILE* fp = NULL;
    if ((fp = fopen(FileName, "r")) == NULL) {
        return ERROR;
    }
    TElemType data;
    fscanf(fp, "%d", &data.key);
    fscanf(fp, "%s", data.others);
    if (data.key == 0) {
        T = NULL;
        return OK;
    }
    T = (BiTree)malloc(sizeof(BiTNode));
    T->data.key = data.key;
    strcpy(T->data.others, data.others);
    PreOrderTraverse_2(T, fp, 0);
    PreOrderTraverse_2(T, fp, 1);
    fclose(fp);
    return OK;
}
