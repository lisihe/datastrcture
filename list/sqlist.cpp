#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define LIST_INIT_SIZE 100
#define LIST_INCREMENT 10

// 定义数据元素
typedef char ElemType;
// 定义状态
typedef int Status;
#define ERROR 0
#define OK 1
#define OVERFLOW 0
#define TRUE 1
#define FALSE 0

//----------线性表的动态分配顺序存储结构----------
typedef struct {
    ElemType * elem; // 存储空间基址
    int length; // 当前长度
    int listsize; // 当前分配的存储容量（以sizeof(ElemType)为单位）
}SqList;

//---------函数原型----------
Status InitList_Sq(SqList &L);
Status ListInsert_Sq(SqList &L, int i, ElemType e);
Status ListDelete_Sq(SqList &L, int i, ElemType &e);
Status LocateElem_Sq(SqList L, ElemType e, Status (* compare)(ElemType, ElemType));
Status compare(ElemType e1, ElemType e2);

Status InitList_Sq(SqList &L) {
    // 构造一个空的线性表
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if(! L.elem) exit(OVERFLOW);
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}// InitList_Sq

Status ListInsert_Sq(SqList &L, int i, ElemType e) {
    // 在顺序线性表第i个位置之前插入新的元素e
    // i的合法值为 1 <= i <= ListLength_Sq(L) + 1
    if (i < 1 || i > L.length + 1) return ERROR; // i值不合法
    if (L.length > L.listsize) { // 当存储空间已满，增加分配
        ElemType *newbase = (ElemType *) realloc(L.elem,
            (L.listsize + LIST_INCREMENT) * sizeof(ElemType));
        if(!newbase) exit(OVERFLOW); // 存储空间分配失败
        L.elem = newbase;
        L.listsize += LIST_INCREMENT;
    }
    ElemType *q = &(L.elem[i - 1]); // q为插入位置
    for(ElemType *p = &(L.elem[L.length - 1]); p >= q; --p) {
        *(p + 1) = *p;
    }
    *q = e;
    ++L.length;
    return OK;
}// ListInsert_Sq

Status ListDelete_Sq(SqList &L, int i, ElemType &e) {
    // 在顺序线性表L中删除第i个元素，并用e返回其值
    // i的合法值为 1 <= i <= ListLength_Sq(L)
    if (i < 1 || i > L.length) return ERROR; // i值不合法
    ElemType *p = &(L.elem[i - 1]); // p为被删除元素的位置
    e = *p; // 被删除元素的值赋给e
    ElemType *q = &(L.elem[L.length -1]); // q为表尾元素的地址
    for (++p; p <= q; ++p) {
        *(p - 1) = *p;
    }
    --L.length; // 表长减1
    return OK;
}// ListDelete_Sq

int LocateElem_Sq(SqList L, ElemType e, Status(* compare)(ElemType, ElemType)) {
    // 在线性顺序表L中查找第1个值与e满足compare()的元素的位序
    // 若找到，则返回其在L中的位序，否则返回0
    int i = 1; // i的初始值为第1个元素的位序
    ElemType* p = L.elem; // p的初值为第1个元素的存储位置
    while (i <= L.length && !(* compare)(*p++, e)) ++i;
    if (i < L.length) {
        return i;
    } else {
        return 0;
    }
}// LocatElem_Sq

Status compare(ElemType e1, ElemType e2) {
    // 比较e1,e2是否相同，相同返回TRUE否则返回FALSE
    return e1 == e2 ? TRUE : FALSE;
}

void MergeList_Sq(SqList La, SqList Lb, SqList &Lc) {
    // 已知线性表La和Lb的元素按值非递减排列
    // 归并La和Lb得到新的顺序线性表Lc，Lc的元素也按值非递减排列
    ElemType* pa = La.elem;
    ElemType* pb = Lb.elem;
    Lc.listsize = Lc.length = La.length + Lb.length;
    ElemType* pc = Lc.elem = (ElemType *)malloc(Lc.listsize * sizeof(ElemType));
    if(!Lc.elem) exit(OVERFLOW); // 存储空间分配失败
    ElemType* pa_last = La.elem + La.length - 1;
    ElemType* pb_last = Lb.elem + Lb.length - 1;
    while(pa <= pa_last && pb <= pb_last) { // 归并
        if(*pa <= *pb) *pc++ = *pa++;
        else *pc++ = *pb++;
    }
    while(pa <= pa_last) *pc++ = *pa;   // 插入La中剩余的元素
    while(pb <= pb_last) *pc++ = *pb;   // 插入Lb中剩余的元素
}// MergeList_Sq

void test1();
int main(void) {
    test1();
    return 0;
}
void testMergeList() {
    // 未测试
}

void test1() {
    SqList sqList;
    Status initStatus = InitList_Sq(sqList); // 初始化有序线性表
    printf("initStatus:%d\n", initStatus);

    ElemType e1 = 'a';
    Status insertStatus = ListInsert_Sq(sqList, 1, e1); // 在线性表中插入一个元素
    printf("insertStatus:%d\n", insertStatus);

    ElemType e2;
    Status deleteStatus = ListDelete_Sq(sqList, 1, e2); // 在线性表中删除一个元素
    printf("deleteStatus:%d deleteValue:%c\n", deleteStatus, e2);

    printf("%d\n", compare('a', 'a'));

    for (int i = 0; i < 10; i++) {  // 向线性表中随机插入10个元素
        char r = (char)((rand() % 5) + 65);
        ListInsert_Sq(sqList, i + 1, r);
        printf("char %c inserted.\n", r);
    }
    int locatIndex = LocateElem_Sq(sqList, 'B', compare); // 查找值为2的元素序位
    printf("char B at :%d\n", locatIndex);
}
