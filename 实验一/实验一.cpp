#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

/*---------page 10 on textbook ---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2
#define MAX_NUM 10

typedef int status;
typedef int ElemType; //数据元素类型定义

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct {  //顺序表（顺序结构）的定义
	ElemType* elem;
	int length;
	int listsize;
}SqList;

FILE* fp;

/*-----page 19 on textbook ---------*/
status InitList(SqList& L);
status DestroyList(SqList& L);
status ClearList(SqList& L);
status ListEmpty(SqList L);
int ListLength(SqList L);
status GetElem(SqList L, int i, ElemType* e);
status LocateElem(SqList L, ElemType e, status(*compare)(ElemType, ElemType));
status cmp(ElemType a, ElemType b);
status PriorElem(SqList L, ElemType cur_e, ElemType* pre_e);
status NextElem(SqList L, ElemType cur_e, ElemType* next_e);
status ListInsert(SqList& L, int i, ElemType e);
status ListDelete(SqList& L, int i, ElemType* e);
status ListTraverse(SqList L);
status SaveList(SqList L, char* filename);
status LoadList(SqList* L, char* filename);
status SortList(SqList L, int tag);
/*--------------------------------------------*/
int main(void) {
	char filename[40];
	int op = 1, tag;
	int i;
	int i_num = 1;
	SqList L[MAX_NUM];
	for (i = 0; i < MAX_NUM; i++)
	{
		L[i].elem = NULL;
		L[i].listsize = 0;
		L[i].length = 0;
	}
	ElemType e, cur_e, pre_e, next_e;
	while (op) {

		system("cls");	printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. InitList        7. LocateElem\n");
		printf("    	  2. DestroyList     8. PriorElem\n");
		printf("    	  3. ClearList       9. NextElem \n");
		printf("    	  4. ListEmpty       10. ListInsert\n");
		printf("    	  5. ListLength      11. ListDelete\n");
		printf("    	  6. GetElem         12. ListTrabverse\n");
		printf("	  13.SaveList	     14. LoadList\n");
		printf("	  15.SortList\n");
		printf("	  16. Choose the specific list(操作前请先执行此选项以选择所操作的表的编号，默认为1)\n");
		printf("	  0. Exit           \n");
		printf("-------------------------------------------------\n");
		printf("请选择你的操作[0--15]:\n");
		scanf("%d", &op);//选择op的值,用于switch
		switch (op) {
		case 1:
			//初始化线性表
			if (InitList(L[i_num]) == OK)
			{

				printf("请输入要保存的线性表名称\n");
				scanf("%s", filename);
				printf("线性表创建成功\n");
			}
			else printf("线性表创建失败！\n");
			getchar(); getchar();
			break;

		case 2:
			//销毁线性表
			if (L[i_num].elem == NULL)
			{
				printf("线性表不存在!\n");
				getchar(); getchar();
				break;
			}
			if (DestroyList(L[i_num]) == OK)
			{
				printf("销毁线性表成功!\n");
			}
			else printf("销毁线性表失败！\n");
			getchar(); getchar();
			break;

		case 3:
			//重置线性表
			if (L[i_num].elem == NULL)
			{
				printf("线性表不存在!\n");
				getchar(); getchar();
				break;
			}
			if (ClearList(L[i_num]) == OK)
			{
				printf("线性表重置成功！\n");
			}
			else printf("线性表重置失败！\n");
			getchar(); getchar();
			break;

		case 4:
			//判断是否为空
			if (L[i_num].elem == NULL)
			{
				printf("线性表不存在!\n");
				getchar(); getchar();
				break;
			}
			if (ListEmpty(L[i_num]) == TRUE)
			{
				printf("线性表为空表！\n");
			}
			else printf("线性表不是空表！\n");
			getchar(); getchar();
			break;

		case 5:
			//得到线性表长度
			if (L[i_num].elem == NULL)
			{
				printf("线性表不存在!\n");
				getchar(); getchar();
				break;
			}
			printf("线性表表长为%d\n", ListLength(L[i_num]));
			getchar(); getchar();
			break;

		case 6:
			//得到某个元素
			if (L[i_num].elem == NULL)
			{
				printf("线性表不存在!\n");
				getchar(); getchar();
				break;
			}
			printf("请输入要取结点的位置：\n");
			scanf("%d", &i);
			if (GetElem(L[i_num], i, &e) == OK)
				printf("第%d个结点的元素是：%d\n", i, e);
			else  printf("输入位置错误！\n");
			getchar(); getchar();
			break;

		case 7:
			//查找元素
			if (L[i_num].elem == NULL)
			{
				printf("线性表不存在!\n");
				getchar(); getchar();
				break;
			}
			printf("请输入数据元素值：\n");
			scanf("%d", &e);
			if (i = LocateElem(L[i_num], e, cmp))
				printf("%d元素位于第%d个位置！\n", e, i);
			else  printf("该元素不存在!\n");
			getchar(); getchar();
			break;

		case 8:
			//求出前驱结点
			if (L[i_num].elem == NULL)
			{
				printf("线性表不存在!\n");
				getchar(); getchar();
				break;
			}
			printf("请输入数据元素：\n");
			scanf("%d", &cur_e);
			PriorElem(L[i_num], cur_e, &pre_e);
			if (PriorElem(L[i_num], cur_e, &pre_e) == OK)
				printf("它的前驱元素为：%d\n", pre_e);
			else if (PriorElem(L[i_num], cur_e, &pre_e) == OVERFLOW)
				printf("表中没有该元素！\n");
			else  printf("它不存在前驱元素！\n");
			getchar(); getchar();
			break;

		case 9:
			//求出后置节点
			if (L[i_num].elem == NULL)
			{
				printf("线性表不存在!\n");
				getchar(); getchar();
				break;
			}
			printf("请输入数据元素：\n");
			scanf("%d", &cur_e);
			if (NextElem(L[i_num], cur_e, &next_e) == OK)
				printf("它的后继元素为：%d\n", next_e);
			else if (NextElem(L[i_num], cur_e, &pre_e) == FALSE)
				printf("它不存在后继元素！\n");
			else
			{
				printf("表中没有该元素！\n");
			}
			getchar(); getchar();
			break;

		case 10:
			//插入元素
			if (L[i_num].elem == NULL)
			{
				printf("线性表不存在!\n");
				getchar(); getchar();
				break;
			}
			printf("请输入您要插入的数据元素：\n");
			scanf("%d", &e);
			printf("请输入您要插入的数据元素的位置：\n");
			scanf("%d", &i);
			if (ListInsert(L[i_num], i, e) == OK)
				printf("插入数据元素成功！\n");
			else
				printf("插入数据元素失败！\n");
			getchar(); getchar();
			break;

		case 11:
			//删除元素
			if (L[i_num].elem == NULL)
			{
				printf("线性表不存在!\n");
				getchar(); getchar();
				break;
			}
			printf("请输入您要删除的数据元素的位置：\n");
			scanf("%d", &i);
			if (ListDelete(L[i_num], i, &e) == OK)
				printf("删除数据元素成功！\n");
			else
				printf("删除数据元素失败！\n");
			getchar(); getchar();
			break;

		case 12:
			//遍历线性表中的元素
			if (L[i_num].elem == NULL)
			{
				printf("线性表不存在!\n");
				getchar(); getchar();
				break;
			}
			if (!ListTraverse(L[i_num])) printf("线性表是空表！\n");
			getchar(); getchar();
			break;

		case 13:
			//保存文件
			if (L[i_num].elem == NULL)
			{
				printf("线性表不存在!\n");
				getchar(); getchar();
				break;
			}
			if (SaveList(L[i_num], filename) == OK)
				printf("文件保存成功\n文件名为%s\n", filename);
			getchar(); getchar();
			break;

		case 14:
			//加载文件，需要输入需要加载的名称
			printf("请输入要加载的文件名:\n ");
			scanf("%s", filename);
			if (LoadList(&L[i_num], filename) == OK)
			{
				printf("文件加载成功\n");
			}
			getchar(); getchar();
			break;

		case 15:
			//排序
			if (L[i_num].elem == NULL)
			{
				printf("线性表不存在!\n");
				getchar(); getchar();
				break;
			}
			printf("请选择排序方法，0代表升序，1代表降序\n");
			scanf("%d", &tag);
			if (SortList(L[i_num], tag) == ERROR)printf("表为空表!");
			else printf("排序成功!");
			getchar(); getchar();
			break;

		case 16:
			//选择在哪个表进行操作
			printf("请输入要在第几个表操作:\n ");
			printf("只支持在%d个顺序表上操作\n", MAX_NUM);
			scanf("%d", &i_num);
			if (i_num<1 || i_num>MAX_NUM)
			{
				printf("选择错误，只能在1~%d号顺序表上操作!", MAX_NUM);
				getchar(); getchar();
				break;
			}
			printf("正在对第%d个表进行操作\n", i_num);
			if ((i_num < 1) || (i_num > 10))
			{
				printf("请选择正确范围，已默认为选择第一个顺序表\n");
				i_num = 1;
			}
			getchar(); getchar();
			break;

		case 0:
			break;

		}
	}
	printf("OhOhOhOhOhOh!\n");
}


/*函数名称：IntiaList
*函数功能：构造一个空的线性表
*初始条件：线性表L不存在或已存在；
*操作结果：构造一个空的线性表。
*/
status InitList(SqList& L) {
	L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem) exit(OVERFLOW);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}


/*
*函数名称：DestoryList
*函数功能：销毁线性表
*初始条件：线性表L已存在；
*操作结果：销毁线性表L。
*/
status DestroyList(SqList& L)
{
	if (L.elem)
		free(L.elem);
	L.elem = NULL;
	L.length = 0;
	L.listsize = 0;
	return OK;
}


/*
*函数名称：ClearList
*函数功能：清空顺序表
*初始条件：线性表L已存在；
*操作结果：将L重置为空表。
*/
status ClearList(SqList& L)
{
	L.length = 0;
	return OK;
}

/*
*函数名称：ListEmpty
*函数功能：判断线性表是否为空
*初始条件：线性表L已存在；
*操作结果：若L为空表返回TRUE,否则返回FALSE。
*/
status ListEmpty(SqList L)
{
	if (L.length == 0)
	{
		return TRUE;
	}
	return FALSE;

}



/*
*函数名称：ListLength
*函数功能：求线性表的表长
*初始条件：线性表已存在；
*操作结果：返回L中数据元素的个数。
*/
int ListLength(SqList L)
{
	return L.length;
}


/*
*函数名称：GetElem
*函数功能：得到某一个元素的值
*初始条件：线性表已存在且满足1≤i≤ListLength(L)；
*操作结果：用e记录L中第i个元素的值
*/
status GetElem(SqList L, int i, ElemType* e)
{
	if (i<1 || i>L.length)
	{
		return ERROR;
	}
	*e = L.elem[i - 1];
	return OK;
}


/*
*函数名称：LocateElem
*函数功能：查找元素
*初始条件：线性表已存在；
*操作结果：返回L中第1个与e满足函数cmp关系的元素的位置，若不存在满足cmp关系的元素，返回0；
*/
status LocateElem(SqList L, ElemType e, status(*cmp)(ElemType, ElemType))
{
	int i;
	for (i = 0; i < L.length; i++)
	{
		if (cmp(L.elem[i], e))
			return ++i;
	}
	return 0;
}



/*
*函数名称：compare
*函数功能：比较大小，服务于LocateList函数
*注释：输入两个ElemType类型的值
*/
status cmp(ElemType a, ElemType b)
{
	if (a == b)
		return TRUE;
	else  return FALSE;
}



/*
*函数名称：PriorElem
*函数功能：求元素的前驱
*注释：初始条件是线性表L已存在；操作结果是若cur_e是L的数据元素，且不是第一个，
	   则用pre_e返回它的前驱，否则操作失败，pre_e无定义。
*/
status PriorElem(SqList L, ElemType cur_e, ElemType* pre_e)
{
	int i;
	for (i = 0; i < L.length; i++)
	{
		if (L.elem[i] == cur_e && i == 0)
		{
			return ERROR;
		}
		else if (L.elem[i] == cur_e)
		{
			*pre_e = L.elem[i - 1];
			return OK;
		}
	}
	return OVERFLOW;
}


/*
*函数名称：NextElem
*函数功能：求后继节点
*初始条件:线性表L已存在；
*操作结果:若cur_e是L的数据元素(不是最后一个元素),则用next_e返回后继的元素，否则返回FALSE；
*/
status NextElem(SqList L, ElemType cur_e, ElemType* next_e)
{
	int i;
	for (i = 0; i < L.length - 1; i++)
	{
		if (L.elem[i] == cur_e)
		{
			*next_e = L.elem[i + 1];
			return OK;
		}

	}
	if (i == L.length - 1 && (L.elem[i] != cur_e)) return OVERFLOW;
	else return FALSE;
}



/*
*函数名称：ListInsert
*函数功能：插入元素
*初始条件：线性表L已存在且非空且满足1≤i≤ListLength(L)+1；
*操作结果：在L的第i个位置之前插入新的元素e
*/
status ListInsert(SqList& L, int i, ElemType e)
{
	int* p, * q, * newbase;
	if (i<1 || i>L.length + 1)
	{
		printf("插入位置不正确!\n");
		return ERROR;
	}
	if (L.length >= L.listsize) {
		newbase = (ElemType*)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
		if (!newbase) exit(OVERFLOW);
		L.elem = newbase;
		L.listsize += LISTINCREMENT;
	}
	q = &(L.elem[i - 1]);
	for (p = &(L.elem[L.length - 1]); p >= q; --p) *(p + 1) = *p;
	*q = e;
	++L.length;
	return OK;

}


/*
*函数名称：ListDelete
*函数功能：删除元素
*初始条件：线性表L已存在且非空，1≤i≤ListLength(L)；
*操作结果：删除L的第i个数据元素，用e返回其值。
*/
status ListDelete(SqList& L, int i, ElemType* e)
{
	if (i<1 || i>L.length)
		return ERROR;//删除的位数不正确
	int j;
	*e = L.elem[i - 1];
	for (j = i - 1; j < L.length; j++)
		L.elem[j] = L.elem[j + 1];
	L.length--;
	return OK;
}


/*
*函数名称：ListTraverse
*函数功能：遍历顺序表
*操作结果：输出顺序表的值
*/
status ListTraverse(SqList L) {
	int i;
	printf("\n--------------all elements --------------------\n");
	for (i = 0; i < L.length; i++) printf("%d ", L.elem[i]);
	printf("\n------------------ end ------------------------\n");
	return L.length;
}


/*
*函数名称：SaveList
*函数功能：保存线性表
*初始条件：线性表非空
*操作结果：将数据元素存入文件
*/
status SaveList(SqList L, char* filename)
{
	int i = 0;
	if ((fp = fopen(filename, "w")) == NULL)
	{
		printf("文件保存失败\n");
		return ERROR;
	}
	fprintf(fp, "%d ", L.length);//保存的时候，也将L的长度保存到了文件
	fprintf(fp, "%d ", L.listsize);//将每个元素的大小也保存到了文件里
	while (i < L.length)
		fprintf(fp, "%d ", L.elem[i++]);//利用循环，将元素依次存进去
	printf("表中元素为:\n");
	for (int i = 0; i < L.length; i++)printf("%d ", L.elem[i]);
	printf("存储的表长为%d，所能存储的数据元素的数量为%d.", L.length, L.listsize);

	fclose(fp);//关闭文件
	return OK;
}







/*
*函数名称：LoadList
*函数功能：加载文件
*初始条件：装载有数据元素的文件
*操作结果：读取文件中的表长，容量，数据元素等属性
*/
status LoadList(SqList* L, char* filename)
{
	int i = 0;
	if ((fp = fopen(filename, "r")) == NULL)
	{
		printf("文件加载失败\n");
		return ERROR;
	}
	fscanf(fp, "%d ", &L->length);
	fscanf(fp, "%d ", &L->listsize);
	L->elem = (ElemType*)malloc(L->listsize * sizeof(ElemType));
	if (!L->elem) exit(OVERFLOW);
	while (i < L->length)
		fscanf(fp, "%d ", &L->elem[i++]);//利用循环，依次读出文件中的内容
	printf("加载得到表长为%d,容量为%d的线性表.\n表中元素为", L->length, L->listsize);
	for (int i = 0; i < L->length; i++)printf("%d ", L->elem[i]);
	fclose(fp);
	return OK;
}


/*
*函数名称：SortList
*函数功能：将表中的元素进行排序
*操作结果：若为空表返回ERROR,否则排序成功后，返回OK
*/
status SortList(SqList L, int tag)
{
	if (L.length == 0)return ERROR;
	if (L.length == 1)return OK;
	if (tag == 0)
	{
		for (int i = 0; i < L.length - 1; i++)
		{
			for (int j = 0; j < L.length - 1 - i; j++)
			{
				if (L.elem[j] > L.elem[j + 1])
				{
					int tmp = L.elem[j];
					L.elem[j] = L.elem[j + 1];
					L.elem[j + 1] = tmp;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < L.length - 1; i++)
		{
			for (int j = 0; j < L.length - 1 - i; j++)
			{
				if (L.elem[j] < L.elem[j + 1])
				{
					int tmp = L.elem[j];
					L.elem[j] = L.elem[j + 1];
					L.elem[j + 1] = tmp;
				}
			}
		}
	}
	return OK;
}
