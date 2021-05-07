#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "LLADT.h"

status InitList(LinkList& L) {
    /// <summary>
    /// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
    /// </summary>
    /// <param name="L"></param>
    /// <returns></returns>
    if (L) return INFEASIBLE;
    L = new LNode;
    return OK;
}

status DestroyList(LinkList& L) {
    /// <summary>
    /// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
    /// </summary>
    /// <param name="L"></param>
    /// <returns></returns>
    if (L) {
        free(L);
        L = NULL;
        return OK;
    }
    return INFEASIBLE;
}

status ClearList(LinkList& L) {
    /// <summary>
    /// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
    /// </summary>
    /// <param name="L"></param>
    /// <returns></returns>
    if (!L) return INFEASIBLE;
    LinkList t = L->next;
    LinkList r;
    while (t != NULL) {
        r = t;
        t = t->next;
        free(r);
    }
    L->next = NULL;
    return OK;
}

status ListEmpty(LinkList L) {
    /// <summary>
    /// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
    /// </summary>
    /// <param name="L"></param>
    /// <returns></returns>
    if (!L) return INFEASIBLE;
    if (!L->next) return TRUE;
    return FALSE;
}

status GetElem(LinkList L, int i, ElemType& e) {
    /// <summary>
    /// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；
    /// 如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    /// </summary>
    /// <param name="L"></param>
    /// <param name="i"></param>
    /// <param name="e"></param>
    /// <returns></returns>
    if (!L) return INFEASIBLE;
    if (i < 1) return ERROR;
    LinkList    t = L->next;
    int         cnt = 0;
    while (t) {
        ++cnt;
        if (cnt == i) {
            e = t->data;
            return OK;
        }
        t = t->next;
    }
    return ERROR;
}

status LocateElem(LinkList L, ElemType e) {
    /// <summary>
    /// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；
    /// 当线性表L不存在时，返回INFEASIBLE。
    /// </summary>
    /// <param name="L"></param>
    /// <param name="e"></param>
    /// <returns></returns>

    if (!L) return INFEASIBLE;
    int cnt = 0;
    LinkList t = L->next;
    while (t) {
        cnt++;
        if (t->data == e) {
            return cnt;
        }
        t = t->next;
    }
    return ERROR;

}

status PriorElem(LinkList L, ElemType e, ElemType& pre) {
    /// <summary>
    /// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；
    /// 如果线性表L不存在，返回INFEASIBLE。
    /// </summary>
    /// <param name="L"></param>
    /// <param name="e"></param>
    /// <param name="pre"></param>
    /// <returns></returns>

    if (!L) return INFEASIBLE;
    ElemType p;
    LinkList t;
    LinkList nt;
    t = L->next;
    if (t) {
        nt = t->next;
    }
    else return ERROR;
    while (nt) {
        if (nt->data == e) {
            pre = t->data;
            return OK;
        }
        t = nt;
        nt = nt->next;
    }
    return ERROR;

}

status NextElem(LinkList L, ElemType e, ElemType& next) {
    /// <summary>
    /// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，
    /// 返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    /// </summary>
    /// <param name="L"></param>
    /// <param name="e"></param>
    /// <param name="next"></param>
    /// <returns></returns>

    if (!L) return INFEASIBLE;
    LinkList t = L->next;
    while (t) {
        if (t->data == e) {
            if (t->next) {
                next = t->next->data;
                return OK;
            }
            else {
                return ERROR;
            }
        }
        t = t->next;
    }
    return ERROR;

}

status ListInsert(LinkList& L, int i, ElemType e) {

    /// <summary>
    /// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；
    /// 当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    /// </summary>
    /// <param name="L"></param>
    /// <param name="i"></param>
    /// <param name="e"></param>
    /// <returns></returns>
    if (!L) return INFEASIBLE;
    // Before i == After i-1
    --i;
    LinkList t = L;
    // Initialize new node
    LinkList x = new LNode;
    x->data = e;
    x->next = NULL;

    while (t) {
        if (!i) {
            LinkList nt = t->next;
            t->next = x;
            x->next = nt;
            return OK;
        }
        t = t->next;
        --i;
    }

    return ERROR;

}

status ListDelete(LinkList& L, int i, ElemType& e) {
    /// <summary>
    /// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；
    /// 当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    /// </summary>
    /// <param name="L"></param>
    /// <param name="i"></param>
    /// <param name="e"></param>
    /// <returns></returns>

    if (!L) return INFEASIBLE;
    if (i < 1) return ERROR;
    LinkList t;
    LinkList nt;
    int cnt = 0;
    t = L;
    nt = t->next;
    while (nt) {
        ++cnt;
        if (cnt == i) {
            t->next = nt->next;
            e = nt->data;
            free(nt);
            return OK;
        }
        t = nt;
        nt = nt->next;
    }
    return ERROR;

}

status ListTraverse(LinkList L) {
    /// <summary>
    /// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；
    /// 如果线性表L不存在，返回INFEASIBLE。
    /// </summary>
    /// <param name="L"></param>
    /// <returns></returns>

    if (!L) return INFEASIBLE;
    LinkList t = L->next;
    while (t) {
        std::cout << t->data << " ";
        t = t->next;
    }
    return OK;

}

status SaveList(LinkList L, char FileName[]) {
    /// <summary>
    /// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
    /// </summary>
    /// <param name="L"></param>
    /// <param name="FileName"></param>
    /// <returns></returns>
    if (!L) return INFEASIBLE;
    LinkList t = L->next;
    FILE* fp = fopen(FileName, "w");
    while (t) {
        fprintf(fp, "%d ", t->data);
        t = t->next;
    }
    fclose(fp);
    return OK;
}

status LoadList(LinkList& L, char FileName[]) {
    /// <summary>
    /// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
    /// </summary>
    /// <param name="L"></param>
    /// <param name="FileName"></param>
    /// <returns></returns>
    if (L) return INFEASIBLE;
    L = new LNode;
    FILE* fp = fopen(FileName, "r");
    LinkList t = L; // tail
    int nt = -1;
    while (~fscanf(fp, "%d", &nt)) {
        LinkList re = new LNode;
        re->data = nt;
        re->next = NULL;
        t->next = re;
        t = re;
    }
    fclose(fp);
    return OK;
}
