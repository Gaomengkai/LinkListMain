#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "LLADT.h"

status InitList(LinkList& L) {
    /// <summary>
    /// ���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
    /// </summary>
    /// <param name="L"></param>
    /// <returns></returns>
    if (L) return INFEASIBLE;
    L = new LNode;
    return OK;
}

status DestroyList(LinkList& L) {
    /// <summary>
    /// ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
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
    /// ������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
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
    /// ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
    /// </summary>
    /// <param name="L"></param>
    /// <returns></returns>
    if (!L) return INFEASIBLE;
    if (!L->next) return TRUE;
    return FALSE;
}

status GetElem(LinkList L, int i, ElemType& e) {
    /// <summary>
    /// ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK��
    /// ���i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
    /// ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����ţ����e�����ڣ�����ERROR��
    /// �����Ա�L������ʱ������INFEASIBLE��
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
    /// ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��
    /// ������Ա�L�����ڣ�����INFEASIBLE��
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
    /// ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�
    /// ����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
    /// ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��
    /// ������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
    /// ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK��
    /// ��ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
    /// ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��
    /// ������Ա�L�����ڣ�����INFEASIBLE��
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
    /// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
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
    /// ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
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
