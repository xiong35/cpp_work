
#ifndef _TREE_FUNCS
#define _TREE_FUNCS

#include <iostream>
#include "def.h"

// void strcpy(char* dest, const char* src);

void CreateBiTreeWithInd(BiTree& T, TElemType* definition, int& curDef);

int hasDuplicates(TElemType* definition);

status CreateBiTree(BiTree& T, TElemType definition[]);

status ClearBiTree(BiTree& T);

int BiTreeDepth(BiTree T);

BiTNode* LocateNode(BiTree T, KeyType e);

status Assign(BiTree& T, KeyType e, TElemType value);

BiTNode* GetSibling(BiTree T, KeyType e);

status InsertNode(BiTree& T, KeyType e, int LR, TElemType c);

BiTNode* LocateNode_2(BiTree T);

status DeleteNode(BiTree& T, KeyType e);

status PreOrderTraverse(BiTree T, void (*visit)(BiTree));

status InOrderTraverse(BiTree T, void (*visit)(BiTree));

status PostOrderTraverse(BiTree T, void (*visit)(BiTree));

status LevelOrderTraverse(BiTree T, void (*visit)(BiTree));

status PreOrderTraverse_1(BiTree T, FILE* fp);

int PreOrderTraverse_2(BiTree f, FILE* fp, int flag);

status SaveBiTree(BiTree T, char FileName[]);

status LoadBiTree(BiTree& T, char FileName[]);

#endif  // !_TREE_FUNCS