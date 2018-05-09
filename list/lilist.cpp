#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
/**
 * 基本操作：
 * InitList(&L)
 * DestroyList(&L)
 * ClearList(&L)
 * ListEmpty(L)
 * ListLength(L)
 * GetElem(L, i, &e)
 * LocateElem(L, e, compare())
 * PriorElem(L, cur_e, &pre_e)
 * NextElem(L, cur_e, &next_e)
 * ListInsert(&L, i, e)
 * ListDelete(&L, i, &e)
 * ListTraverse(L, visit())
 * **/


// ----------定义状态----------
typedef int Status;
#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0

// ----------用户自定义的数据元素类型----------
typedef char ElemType;

// ----------线性表的单链存储结构----------
typedef struct Lnode {
    ElemType data;
    struct Lnode* next;
}Lnode, *LinkList; // 注：`*LinkList` means `struct Lnode *`, it's a pointer type.

Status GetElem_L(LinkList L, int i, ElemType &e) {
    // L为带头结点的单链表的头指针
    // 当第i个元素存在时，其值赋给e并返回OK，否则返回ERROR
    LinkList p = L -> next; // 初始化p指向第1个结点
    int j = 1;  // 计数器
    while (p && j < i) {
        p = p -> next;
        ++j;
    }
    if(!p || j > i) {
        return ERROR;
    }
    e = p -> data;
    return OK;
} // GetElem_L

Status ListInsert_L(LinkList &L, int i, ElemType e) {
    // 在带头结点的单链线性表L中第i个位置之前插入元素e
    LinkList p = L;
    int j = 0;
    while (p && j < i - 1) {
        p = p -> next;
        ++j;
    }
    if (!p || j > j - 1) return ERROR;
    Lnode* s = (Lnode *)malloc(sizeof(Lnode));
    // (*s).data = e;
    s -> data = e;
    s -> next = p -> next; // 插入L
    p -> next = s;
    return OK;
} // ListInsert_L

Status ListDelete_L(LinkList &L, int i, ElemType &e) {
    // 在带头结点的单链线性表L中，删除第i个元素，并用e返回其值
    Lnode* p = L;
    int j = 0;
    while (p && j < i - 1) {
        p = p -> next;
        ++j;
    }
    if(!p || j > i - 1) {
        return ERROR;
    }
    Lnode* q = p -> next; // q为删除节点所在位置
    e = q -> data;
    p -> next = q -> next;
    free(q); // 注意不要忘记释放删除节点所占空间
    return OK;
}

void CreateList_L(LinkList &L, int n) {
    // 逆位序输入n个元素的值，建立带头结点的单链线性表L
    L = (LinkList)malloc (sizeof (Lnode));
    L -> next = NULL; // 建立一个带头结点的单链表L
    for(int i = 0; i < n; i++) {
        Lnode* p = (Lnode*)malloc(sizeof (Lnode));
        scanf("%c\n",&(p -> data));
        p -> next = L -> next; // 插入到表头
        L -> next = p;
    }
}// CreatList_L

int main(void) {
    LinkList l;
    CreateList_L(l, 10);
    for(int i = 0; i < 10; i++) {
        ElemType e;
        GetElem_L(l, i + 1, e);
        printf("%d is %c\n", i + 1, e);
    }
    return 0;
}