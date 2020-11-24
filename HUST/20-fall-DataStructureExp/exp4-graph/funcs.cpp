#include "funcs.h"

status CreateGraph(ALGraph& G, VertexType V[], KeyType VR[][2]) {
    /*根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
    如果有相同的关键字，返回ERROR。*/
    int i = 0, j = 0;
    G.arcnum = 0, G.vexnum = 0;

    // check whether have duplicate key & V length
    while (V[i].key != -1) {
        if (i >= MAX_VERTEX_NUM)
            return ERROR;
        int j = i + 1;
        while (V[j].key == -1)
            if (V[j++].key == V[i].key)
                return ERROR;
        i++;
    }

    i = 0, j = 0;
    // check whether have wrong key in arcs
    while (VR[i][0] != -1) {
        j = 0;
        int haveKeyAt0 = 0;
        int haveKeyAt1 = 0;
        while (V[j].key != -1) {
            if (V[j].key == VR[i][0])
                haveKeyAt0 = 1;
            if (V[j].key == VR[i][1])
                haveKeyAt1 = 1;
            j++;
        }
        if (!haveKeyAt0 || !haveKeyAt1)
            return ERROR;
        i++;
    }

    // init nodes
    while (V[G.vexnum].key != -1) {
        G.vertices[G.vexnum].data.key = V[G.vexnum].key;
        strcpy(G.vertices[G.vexnum].data.others, V[G.vexnum].others);
        G.vertices[G.vexnum].firstarc = NULL;
        G.vexnum++;
    }

    // init arcs
    while (VR[G.arcnum][0] != -1) {
        int m = -1, n = -1;
        while (V[++m].key != VR[G.arcnum][0])
            ;
        while (V[++n].key != VR[G.arcnum][1])
            ;
        ArcNode* mOld = G.vertices[m].firstarc;
        ArcNode* nOld = G.vertices[n].firstarc;
        ArcNode* mNew = (ArcNode*)malloc(sizeof(ArcNode));
        ArcNode* nNew = (ArcNode*)malloc(sizeof(ArcNode));
        mNew->nextarc = mOld;
        nNew->nextarc = nOld;
        mNew->adjvex = n;
        nNew->adjvex = m;
        G.vertices[m].firstarc = mNew;
        G.vertices[n].firstarc = nNew;

        G.arcnum++;
    }

    return OK;
}

status DestroyGraph(ALGraph& G) {
    /*销毁无向图G*/
    for (int i = 0; i < G.vexnum; i++) {
        ArcNode* temp = G.vertices[i].firstarc;
        while (temp) {
            ArcNode* next = temp->nextarc;
            free(temp);
            temp = next;
        }
        G.vertices[i].firstarc = NULL;
    }

    G.vexnum = 0;
    G.arcnum = 0;
    return OK;
}

int LocateVex(ALGraph G, KeyType u) {
    //根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
    for (int i = 0; i < G.vexnum; i++) {
        if (G.vertices[i].data.key == u)
            return i;
    }
    return -1;
}

status PutVex(ALGraph& G, KeyType u, VertexType value) {
    //根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
    //如果查找失败或关键字不唯一，返回ERROR
    int ind = LocateVex(G, u);

    if (ind == -1)
        return ERROR;

    if (G.vertices[ind].data.key == value.key) {
        strcpy(G.vertices[ind].data.others, value.others);
        return OK;
    }

    for (int i = 0; i < G.vexnum; i++) {
        if (value.key == G.vertices[i].data.key)
            return ERROR;
    }

    strcpy(G.vertices[ind].data.others, value.others);
    G.vertices[ind].data.key = value.key;
    return OK;
}

int FirstAdjVex(ALGraph G, KeyType u) {
    //根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
    for (int i = 0; i < G.vexnum; i++) {
        if (G.vertices[i].data.key == u && G.vertices[i].firstarc)
            return G.vertices[i].firstarc->adjvex;
    }
    return -1;
}

int NextAdjVex(ALGraph G, KeyType v, KeyType w) {
    //根据u在图G中查找顶点，查找成功返回顶点v的邻接顶点相对于w的下一邻接顶点的位序，查找失败返回-1；
    for (int i = 0; i < G.vexnum; i++) {
        if (G.vertices[i].data.key == v) {
            ArcNode* temp = G.vertices[i].firstarc;
            while (temp) {
                if (G.vertices[temp->adjvex].data.key == w && temp->nextarc)
                    return temp->nextarc->adjvex;
                temp = temp->nextarc;
            }
        }
    }
    return -1;
}

status InsertVex(ALGraph& G, VertexType v) {
    //在图G中插入顶点v，成功返回OK,否则返回ERROR
    if (G.vexnum >= MAX_VERTEX_NUM)
        return ERROR;

    for (int i = 0; i < G.vexnum; i++) {
        if (v.key == G.vertices[i].data.key)
            return ERROR;
    }
    G.vertices[G.vexnum].data = v;
    G.vertices[G.vexnum++].firstarc = NULL;
    return OK;
}

status DeleteVex(ALGraph& G, KeyType v) {
    //在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
    int ind = LocateVex(G, v);
    if (ind == -1)
        return ERROR;
    if (ind == 0 && G.vexnum == 1)
        return ERROR;

    // del ArcNode
    for (int i = 0; i < G.vexnum; i++) {
        ArcNode* curPt = G.vertices[i].firstarc;
        while (curPt && curPt->nextarc) {
            if (curPt->nextarc->adjvex == ind) {
                ArcNode* next = curPt->nextarc->nextarc;
                free(curPt->nextarc);
                curPt->nextarc = next;
            }
            curPt = curPt->nextarc;
        }
        if (G.vertices[i].firstarc && G.vertices[i].firstarc->adjvex == ind) {
            ArcNode* next = G.vertices[i].firstarc->nextarc;
            free(G.vertices[i].firstarc);
            G.vertices[i].firstarc = next;
        }

        // decrease the adjvex nums
        curPt = G.vertices[i].firstarc;
        while (curPt) {
            if (curPt->adjvex >= ind)
                curPt->adjvex--;
            curPt = curPt->nextarc;
        }
    }

    // move VNodes
    for (int i = ind + 1; i < G.vexnum; i++) {
        G.vertices[i - 1] = G.vertices[i];
    }

    G.vexnum--;

    return OK;
}

status InsertArc(ALGraph& G, KeyType v, KeyType w) {
    //在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
    int vInd = LocateVex(G, v);
    int wInd = LocateVex(G, w);
    if (vInd == -1 || wInd == -1)
        return ERROR;

    ArcNode* temp = G.vertices[vInd].firstarc;

    while (temp) {
        if (G.vertices[temp->adjvex].data.key == w)
            return ERROR;
        temp = temp->nextarc;
    }

    ArcNode* vNew = (ArcNode*)malloc(sizeof(ArcNode));
    ArcNode* wNew = (ArcNode*)malloc(sizeof(ArcNode));

    vNew->adjvex = wInd;
    wNew->adjvex = vInd;
    vNew->nextarc = G.vertices[vInd].firstarc;
    G.vertices[vInd].firstarc = vNew;

    wNew->nextarc = G.vertices[wInd].firstarc;
    G.vertices[wInd].firstarc = wNew;

    return OK;
}

status DeleteArc(ALGraph& G, KeyType v, KeyType w) {
    //在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
    int vInd = LocateVex(G, v);
    int wInd = LocateVex(G, w);
    if (vInd == -1 || wInd == -1 || !G.vertices[vInd].firstarc ||
        !G.vertices[wInd].firstarc)
        return ERROR;

    ArcNode *temp, *curPt;
    int flagV = 0, flagW = 0;

    if (G.vertices[G.vertices[vInd].firstarc->adjvex].data.key == w) {
        flagW = 1;
    }
    curPt = G.vertices[vInd].firstarc;
    while (curPt && curPt->nextarc) {
        if (G.vertices[curPt->nextarc->adjvex].data.key == w) {
            flagW = 1;
            break;
        }
        curPt = curPt->nextarc;
    }

    if (G.vertices[G.vertices[wInd].firstarc->adjvex].data.key == v) {
        flagV = 1;
    }
    curPt = G.vertices[wInd].firstarc;
    while (curPt && curPt->nextarc) {
        if (G.vertices[curPt->nextarc->adjvex].data.key == v) {
            flagV = 1;
            break;
        }
        curPt = curPt->nextarc;
    }

    if (!(flagV && flagW))
        return ERROR;

    if (G.vertices[G.vertices[vInd].firstarc->adjvex].data.key == w) {
        temp = G.vertices[vInd].firstarc->nextarc;
        free(G.vertices[vInd].firstarc);
        G.vertices[vInd].firstarc = temp;
    }
    curPt = G.vertices[vInd].firstarc;
    while (curPt && curPt->nextarc) {
        if (G.vertices[curPt->nextarc->adjvex].data.key == w) {
            temp = curPt->nextarc->nextarc;
            free(curPt->nextarc);
            curPt->nextarc = temp;
            break;
        }
        curPt = curPt->nextarc;
    }

    if (G.vertices[G.vertices[wInd].firstarc->adjvex].data.key == v) {
        temp = G.vertices[wInd].firstarc->nextarc;
        free(G.vertices[wInd].firstarc);
        G.vertices[wInd].firstarc = temp;
    }
    curPt = G.vertices[wInd].firstarc;
    while (curPt && curPt->nextarc) {
        if (G.vertices[curPt->nextarc->adjvex].data.key == v) {
            temp = curPt->nextarc->nextarc;
            free(curPt->nextarc);
            curPt->nextarc = temp;
            break;
        }
        curPt = curPt->nextarc;
    }

    return OK;
}

void DFSWithRecord(const ALGraph& G,
                   TraverseRecord& record,
                   int curInd,
                   void (*visit)(VertexType)) {
    for (int i = 0; i < record.visitedNum; i++) {
        if (record.visited[i] == G.vertices[curInd].data.key)
            return;
    }

    visit(G.vertices[curInd].data);
    record.visited[record.visitedNum++] = G.vertices[curInd].data.key;

    ArcNode* curPt = G.vertices[curInd].firstarc;
    while (curPt) {
        DFSWithRecord(G, record, curPt->adjvex, visit);
        curPt = curPt->nextarc;
    }
}

status DFSTraverse(ALGraph& G, void (*visit)(VertexType)) {
    //对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
    TraverseRecord record;
    record.visited = (int*)malloc(sizeof(int) * G.vexnum);
    record.visitedNum = 0;
    for (int i = 0; i < G.vexnum; i++)
        record.visited[i] = 0;

    for (int i = 0; i < G.vexnum; i++) {
        DFSWithRecord(G, record, i, visit);
    }
}

status BFSTraverse(ALGraph& G, void (*visit)(VertexType)) {
    //对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
    int* visitList = (int*)malloc(sizeof(int) * G.vexnum);
    int begin = 0, end = 0;
    for (int i = 0; i < G.vexnum; i++)
        visitList[i] = -1;

    for (int i = 0; i < G.vexnum; i++) {
        int isInList = 0;
        for (int j = 0; j < end; j++) {
            if (visitList[j] == i)
                isInList = 1;
        }
        if (!isInList) {
            visitList[end++] = i;
        }
        VNode& curNode = G.vertices[visitList[begin]];
        ArcNode* temp = curNode.firstarc;
        while (temp) {
            int isInList = 0;
            for (int j = 0; j < end; j++) {
                if (visitList[j] == temp->adjvex)
                    isInList = 1;
            }
            if (!isInList)
                visitList[end++] = temp->adjvex;
            temp = temp->nextarc;
        }
        begin++;
    }
    for (int i = 0; i < G.vexnum; i++) {
        visit(G.vertices[visitList[i]].data);
    }
}

void pushStack(KeyType stack[], int& top, KeyType e) {
    //栈的入栈操作
    if (top >= 99) {
        printf("The stack is full.");
    } else {
        stack[top++] = e;
    }
}
void popStack(KeyType stack[], int& top, KeyType& e) {
    //栈的出栈操作
    if (top == 0) {
        printf("The stack is empty.");
    } else {
        e = stack[--top];
    }
}

status SaveGraph(ALGraph G, char FileName[])
//将图的数据写入到文件FileName中
{
    int book[100][100];
    memset(book, 0, sizeof(book));
    KeyType stack[100];
    int top = 0;
    KeyType tmp;
    ArcNode* ptr;
    FILE* fp = fopen(FileName, "w");
    if (!fp)
        return ERROR;
    for (int i = 0; i < G.vexnum; i++) {
        fprintf(fp, "%d %s ", G.vertices[i].data.key,
                G.vertices[i].data.others);
    }
    fprintf(fp, "%d %s ", -1, "nil");
    for (int i = 0; i < G.vexnum; i++) {
        ptr = G.vertices[i].firstarc;
        while (ptr) {
            if (!book[i][ptr->adjvex]) {
                pushStack(stack, top, G.vertices[ptr->adjvex].data.key);
                book[ptr->adjvex][i] = 1;
            }
            ptr = ptr->nextarc;
        }
        while (top != 0) {
            popStack(stack, top, tmp);
            fprintf(fp, " %d %d ", G.vertices[i].data.key, tmp);
        }
    }
    fprintf(fp, "%d %d", -1, -1);
    fclose(fp);
    return OK;
}

status LoadGraph(ALGraph& G, char FileName[])
//读入文件FileName的图数据，创建图的邻接表
{
    VertexType V[21];
    KeyType VR[100][2];
    FILE* fp = fopen(FileName, "r");
    if (!fp)
        return ERROR;
    int i = 0;
    do {
        fscanf(fp, "%d%s", &V[i].key, &V[i].others);
    } while (V[i++].key != -1);
    i = 0;
    do {
        fscanf(fp, "%d%d", &VR[i][0], &VR[i][1]);
    } while (VR[i++][0] != -1);
    CreateGraph(G, V, VR);
    fclose(fp);
    return OK;
}
