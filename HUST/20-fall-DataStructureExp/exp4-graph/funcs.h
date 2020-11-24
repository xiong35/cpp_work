#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "def.h"

status CreateGraph(ALGraph& G, VertexType V[], KeyType VR[][2]);

status DestroyGraph(ALGraph& G);

int LocateVex(ALGraph G, KeyType u);

status PutVex(ALGraph& G, KeyType u, VertexType value);

int FirstAdjVex(ALGraph G, KeyType u);

int NextAdjVex(ALGraph G, KeyType v, KeyType w);

status InsertVex(ALGraph& G, VertexType v);

status DeleteVex(ALGraph& G, KeyType v);

status InsertArc(ALGraph& G, KeyType v, KeyType w);

status DeleteArc(ALGraph& G, KeyType v, KeyType w);

typedef struct {
    int* visited;
    int visitedNum;
} TraverseRecord;

void DFSWithRecord(const ALGraph& G,
                   TraverseRecord& record,
                   int curInd,
                   void (*visit)(VertexType));

status DFSTraverse(ALGraph& G, void (*visit)(VertexType));

status BFSTraverse(ALGraph& G, void (*visit)(VertexType));

void pushStack(KeyType stack[], int& top, KeyType e);

void popStack(KeyType stack[], int& top, KeyType& e);

status SaveGraph(ALGraph G, char FileName[]);

status LoadGraph(ALGraph& G, char FileName[]);
