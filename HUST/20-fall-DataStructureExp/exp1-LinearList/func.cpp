#include "def.h"

status InitList(SqList& L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    if (L.elem != NULL)
        return INFEASIBLE;

    L.elem = (ElemType*)malloc(0);
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;

    return OK;
}

status DestroyList(SqList& L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，
// 返回OK，否则返回INFEASIBLE。
{
    if (L.elem == NULL)
        return INFEASIBLE;

    free(L.elem);
    L.elem = NULL;

    return OK;
}

status ClearList(SqList& L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    if (L.elem == NULL)
        return INFEASIBLE;

    L.length = 0;
    return OK;
}

status ListEmpty(SqList L)
// 如果线性表L存在，判断线性表L是否为空，
// 空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    if (L.elem == NULL)
        return INFEASIBLE;

    return L.length == 0;
}

int ListLength(SqList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    if (L.elem == NULL)
        return INFEASIBLE;

    return L.length;
}

status GetElem(SqList L, int i, ElemType& e)
// 如果线性表L存在，获取线性表L的第i个元素(下标从1开始)，保存在e中，返回OK
// ；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (L.elem == NULL)
        return INFEASIBLE;

    if (i > L.length || i < 1)
        return ERROR;

    e = L.elem[i - 1];
    return OK;
}

status LocateElem(SqList L, ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号并返回OK；
// 如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
    if (L.elem == NULL)
        return INFEASIBLE;

    for (int i = 0; i < L.length; i++) {
        if (L.elem[i] == e)
            return i + 1;
    }

    return ERROR;
}

status PriorElem(SqList L, ElemType e, ElemType& pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；
// 如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (L.elem == NULL)
        return INFEASIBLE;

    for (int i = 1; i < L.length; i++) {
        if (L.elem[i] == e) {
            pre = L.elem[i - 1];
            return OK;
        }
    }

    return ERROR;
}

status NextElem(SqList L, ElemType e, ElemType& next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (L.elem == NULL)
        return INFEASIBLE;

    for (int i = 0; i < L.length - 1; i++) {
        if (L.elem[i] == e) {
            next = L.elem[i + 1];
            return OK;
        }
    }

    return ERROR;
}

status ListInsert(SqList& L, int i, ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK
// 当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (L.elem == NULL)
        return INFEASIBLE;

    if (i > L.length + 1 || i < 1)
        return ERROR;

    ElemType* old = L.elem;

    L.elem = (ElemType*)malloc(sizeof(ElemType) * ++L.length);

    for (int j = 0; j < i - 1; j++) {
        L.elem[j] = old[j];
    }
    L.elem[i - 1] = e;
    for (int j = i; j < L.length; j++) {
        L.elem[j] = old[j - 1];
    }

    free(old);
    return OK;
}

status ListDelete(SqList& L, int i, ElemType& e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK
// 当删除位置不正确时，返回ERROR
// 如果线性表L不存在，返回INFEASIBLE。
{
    if (L.elem == NULL)
        return INFEASIBLE;

    if (i > L.length + 1 || i < 1)
        return ERROR;

    e = L.elem[i - 1];

    for (int j = i; j < L.length; j++) {
        L.elem[j - 1] = L.elem[j];
    }
    L.length--;

    return OK;
}

status ListTraverse(SqList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格
// 返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    if (L.elem == NULL)
        return INFEASIBLE;

    for (int i = 0; i < L.length; i++) {
        printf("%d ", L.elem[i]);
    }
    return OK;
}

status SaveList(SqList L, char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    if (L.elem == NULL)
        return INFEASIBLE;

    FILE* fp = fopen(FileName, "w");

    if (fp == NULL)
        return INFEASIBLE;

    for (int i = 0; i < L.length; i++) {
        fprintf(fp, "%d ", L.elem[i]);
    }

    fclose(fp);

    return OK;
}

status LoadList(SqList& L, char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    if (L.elem != NULL)
        return INFEASIBLE;

    int count = 0;
    int temp;

    FILE* fp = fopen(FileName, "r");

    if (fp == NULL)
        return INFEASIBLE;

    while (true) {
        if (fscanf(fp, "%d ", &temp) != 1) {
            break;
        }
        count++;
    }

    rewind(fp);

    L.elem = (ElemType*)malloc(count * sizeof(ElemType));

    for (int i = 0; i < count; i++) {
        fscanf(fp, "%d ", L.elem + i);
    }

    L.length = count;

    fclose(fp);

    return OK;
}

status AddList(LISTS& Lists, char ListName[])
// 只需要在Lists中增加一个名称为ListName的空线性表
// 线性表数据又后台测试程序插入。
{
    Lists.elem[Lists.length].L.elem = (ElemType*)malloc(0);
    Lists.elem[Lists.length].L.length = 0;
    Lists.elem[Lists.length].L.listsize = LIST_INIT_SIZE;

    int i = 0;
    do {
        Lists.elem[Lists.length].name[i] = ListName[i];
    } while (ListName[i++]);

    Lists.length++;

    return OK;
}

int strcmp(char* a, char* b) {
    int i = 0;
    while (1) {
        if (a[i] != b[i])
            return 0;
        else if (a[i] == 0 && b[i] == 0)
            return 1;
        else if (a[i] == 0 || b[i] == 0)
            return 0;
        else
            i++;
    }
}

status RemoveList(LISTS& Lists, char ListName[])
// Lists中删除一个名称为ListName的线性表
{
    int i = 0;
    for (; i < Lists.length; i++) {
        if (strcmp(Lists.elem[i].name, ListName))
            break;
    }
    if (i >= Lists.length)
        return ERROR;

    for (; i + 1 < Lists.length + 1; i++) {
        Lists.elem[i] = Lists.elem[i + 1];
    }

    return OK;
}

int LocateList(LISTS Lists, char ListName[])
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
    for (int i = 0; i < Lists.length; i++) {
        if (strcmp(Lists.elem[i].name, ListName))
            return i + 1;
    }

    return 0;
}