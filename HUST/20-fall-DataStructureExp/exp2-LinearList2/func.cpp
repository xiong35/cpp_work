
#include "func.h"

status InitList(LinkList& L) {
    // 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
    if (L)
        return INFEASIBLE;

    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;

    return OK;
}

status DestroyList(LinkList& L) {
    // 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
    if (!L)
        return INFEASIBLE;

    LinkList temp;
    while (L) {
        temp = L;
        L = L->next;
        free(temp);
    }

    return OK;
}

status ClearList(LinkList& L) {
    // 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
    if (!L)
        return INFEASIBLE;

    LinkList temp, LFirst = L->next;

    while (LFirst) {
        temp = LFirst;
        LFirst = LFirst->next;
        free(temp);
    }

    L->next = NULL;

    return OK;
}

status ListEmpty(LinkList L) {
    // 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
    if (!L)
        return INFEASIBLE;

    return L->next == NULL;
}

int ListLength(LinkList L) {
    // 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
    if (!L)
        return INFEASIBLE;

    int len = 0;

    LinkList temp = L->next;

    while (temp) {
        temp = temp->next;
        len++;
    }

    return len;
}

status GetElem(LinkList L, int i, ElemType& e) {
    // 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回O
    // 如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。

    if (!L)
        return INFEASIBLE;

    if (i <= 0)
        return ERROR;

    while (L && i--) {
        L = L->next;
    }

    if (i < 0) {
        e = L->data;
        return OK;
    }

    return ERROR;
}

status LocateElem(LinkList L, ElemType e) {
    // 如果线性表L存在，查找元素e在线性表L中的位置序号
    // 如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
    if (!L)
        return INFEASIBLE;

    int ind = 1;
    L = L->next;

    while (L) {
        if (L->data == e)
            return ind;
        L = L->next;
        ind++;
    }

    return ERROR;
}

status PriorElem(LinkList L, ElemType e, ElemType& pre) {
    // 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK
    // 果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。

    // 如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
    if (!L)
        return INFEASIBLE;

    L = L->next;

    while (L && L->next) {
        if (L->next->data == e) {
            pre = L->data;
            return OK;
        }
        L = L->next;
    }

    return ERROR;
}

status NextElem(LinkList L, ElemType e, ElemType& next) {
    // 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回O
    // 如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。

    if (!L)
        return INFEASIBLE;

    L = L->next;

    while (L && L->next) {
        if (L->data == e) {
            next = L->next->data;
            return OK;
        }
        L = L->next;
    }

    return ERROR;
}

status ListInsert(LinkList& L, int i, ElemType e) {
    // 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK
    // 当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    if (!L)
        return INFEASIBLE;

    LinkList L_ = L;

    while (L_ && i-- > 0) {
        if (i == 0) {
            LinkList temp = L_->next;
            L_->next = (LinkList)malloc(sizeof(LNode));
            L_->next->data = e;
            L_->next->next = temp;
            return OK;
        }
        L_ = L_->next;
    }

    return ERROR;
}

status ListDelete(LinkList& L, int i, ElemType& e) {
    // 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK
    //当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    if (!L)
        return INFEASIBLE;

    LinkList L_ = L;

    while (L_ && L_->next && i-- > 0) {
        if (i == 0) {
            e = L_->next->data;
            LinkList temp = L_->next->next;
            free(L_->next);
            L_->next = temp;
            return OK;
        }
        L_ = L_->next;
    }

    return ERROR;
}

status ListTraverse(LinkList L) {
    // 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK
    // 如果线性表L不存在，返回INFEASIBLE。
    if (!L)
        return INFEASIBLE;

    L = L->next;

    while (L) {
        printf("%d ", L->data);
        L = L->next;
    }

    return OK;
}

status SaveList(LinkList L, char FileName[]) {
    // 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK
    // 否则返回INFEASIBLE。
    if (!L)
        return INFEASIBLE;

    FILE* fp = fopen(FileName, "w");
    if (!fp)
        return ERROR;

    L = L->next;
    while (L) {
        fprintf(fp, "%d ", L->data);
        L = L->next;
    }

    fclose(fp);

    return OK;
}

status LoadList(LinkList& L, char FileName[]) {
    // 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK
    // 否则返回INFEASIBLE。
    if (L)
        return INFEASIBLE;

    FILE* fp = fopen(FileName, "r");
    if (!fp)
        return ERROR;

    L = (LinkList)malloc(sizeof(LNode));
    LinkList L_ = L;
    L_->next = NULL;

    ElemType temp;
    while (fscanf(fp, "%d ", &temp) == 1) {
        L_->next = (LinkList)malloc(sizeof(LNode));
        L_->next->data = temp;
        L_->next->next = NULL;

        L_ = L_->next;
    }

    return OK;
}

status AddList(Lists& lists, char ListName[]) {
    // 只需要在Lists中增加一个名称为ListName的空线性表
    // 线性表数据又后台测试程序插入。
    if (lists.length == MAX_LISTS)
        return ERROR;

    int i = 0;
    do {
        lists.names[lists.length][i] = ListName[i];
    } while (ListName[i++]);

    lists.length++;

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

status RemoveList(Lists& lists, char ListName[]) {
    // lists中删除一个名称为ListName的线性表
    int i = 0;
    for (; i < lists.length; i++) {
        if (strcmp(lists.names[i], ListName))
            break;
    }
    if (i >= lists.length)
        return ERROR;

    for (; i + 1 < lists.length + 1; i++) {
        lists.lists[i] = lists.lists[i + 1];
    }

    return OK;
}

int LocateList(Lists Lists, char ListName[]) {
    // 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
    for (int i = 0; i < Lists.length; i++) {
        if (strcmp(Lists.names[i], ListName))
            return i + 1;
    }

    return 0;
}