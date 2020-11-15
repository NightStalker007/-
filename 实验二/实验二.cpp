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
const int MAX_NUM = 10;//所能操作的最多的表数

typedef int status;
typedef int ElemType;

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct LNode {
	ElemType data;//结点的数据域
	struct LNode* next;//结点的指针域
}LNode, * LinkList;

FILE* fp;
LinkList frontPointer;//判断回文链表时用
LinkList L[MAX_NUM];

status InitList(LinkList* L);
status DestroyList(LinkList* L);
status ClearList(LinkList* L);
status ListEmpty(LinkList L);
int ListLength(LinkList L);
status GetElem(LinkList L, int i, ElemType* e);
int LocateElem(LinkList L, ElemType e, status(*compare)(ElemType a, ElemType b));
status compare(ElemType a, ElemType b);
status PriorElem(LinkList L, ElemType cur_e, ElemType* pre_e);
status NextElem(LinkList L, ElemType cur_e, ElemType* next_e);
status ListInsert(LinkList* L, int i, ElemType e);
status ListDelete(LinkList* L, int i, ElemType* e);
status ListTraverse(LinkList L);
status SaveList(LinkList L, char* filename);
status LoadList(LinkList* L, char* filename);
status SortList(LinkList L, int tag);
status ReverseList(LinkList* L);
status RemoveSpecificData(LinkList L, int val);
status MergeList(LinkList* L1, LinkList* L2);
status IsPalindromeList(LinkList L);
status RecursivelyCheck(LinkList currentNode);
status ListAddition(LinkList* L1, LinkList* L2);

int main() {
	char filename[40]; int op = 1;
	int i, i_num = 1, tag = 0, val = 0, i_num1, i_num2;//默认在第一张表上进行操作 
	status flag;
	for (i = 0; i < MAX_NUM; i++)
	{
		L[i] = NULL;
	}
	ElemType e, cur_e, pre_e, next_e;
	while (op) {
		system("cls");
		printf("\n\n");
		printf("     Menu for Linear Table On Sequence Structure \n");
		printf("  可在%d个顺序表进行多表操作，初始化请先操作功能15,默认在第一个表上操作\n", MAX_NUM);
		printf("-------------------------------------------------\n");
		printf("    	  1. InitList        7. LocateElem\n");
		printf("    	  2. DestroyList     8. PriorElem\n");
		printf("    	  3. ClearList       9. NextElem \n");
		printf("    	  4. ListEmpty       10. ListInsert\n");
		printf("    	  5. ListLength      11. ListDelete\n");
		printf("    	  6. GetElem         12. ListTraverse\n");
		printf("    	  13.SaveList        14. LoadList\n");
		printf("    	  15.SortList        16. ReverseList\n");
		printf("    	  17.RemoveSpecificData\n");
		printf("    	  18.MergeList       19.IsPalindromeList\n");
		printf("    	  20.ListAddition\n");
		printf("    	  21.Choose the specific List\n");
		printf("    	  先选择21以选择所要执行操作的表的序号！\n");
		printf("-------------------------------------------------\n");
		printf("请选择你的操作[0--21]:\n");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			//初始化线性表
			flag = InitList(&L[i_num]);
			if (flag == OK)
			{

				printf("请输入要保存的线性表名称\n");
				scanf("%s", filename);
				printf("线性表创建成功\n");
			}
			else if (flag == OVERFLOW) printf("空间不足，线性表创建失败！\n");
			else printf("表不为空，无需初始化!\n");
			getchar(); getchar();
			break;

		case 2:
			//第二种情况是用来销毁线性表
			if (L[i_num] == NULL)
			{
				printf("线性表不存在!\n");
				getchar(); getchar();
				break;
			}
			if (DestroyList(&L[i_num]) == OK)
			{
				printf("销毁线性表成功!\n");
			}
			else printf("销毁线性表失败！\n");
			getchar(); getchar();
			break;

		case 3:
			//用于重置线性表
			if (L[i_num] == NULL)
			{
				printf("线性表不存在!\n");
				getchar(); getchar();
				break;
			}
			if (ClearList(&L[i_num]) == OK)
			{
				printf("线性表重置成功！\n");
			}
			else printf("线性表重置失败！\n");
			getchar(); getchar();
			break;

		case 4:
			//判断是否为空
			if (L[i_num] == NULL)
			{
				printf("线性表不存在!\n");
				getchar(); getchar();
				break;
			}
			if (ListEmpty(L[i_num]) == TRUE)
			{
				printf("文件为空！\n");
			}
			else printf("线性表不是空表！\n");
			getchar(); getchar();
			break;

		case 5:
			//得到线性表长度
			if (L[i_num] == NULL)
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
			if (L[i_num] == NULL)
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
			//printf("\n----LocateElem功能待实现！\n");
			if (L[i_num] == NULL)
			{
				printf("线性表不存在!\n");
				getchar(); getchar();
				break;
			}
			printf("请输入数据元素值：\n");
			scanf("%d", &e);
			if (i = LocateElem(L[i_num], e, compare))
				printf("%d元素位于第%d个位置！\n", e, i);
			else  printf("该元素不存在!\n");
			getchar(); getchar();
			break;

		case 8:
			//求出前驱结点
			if (L[i_num] == NULL)
			{
				printf("线性表不存在!\n");
				getchar(); getchar();
				break;
			}
			printf("请输入数据元素：\n");
			scanf("%d", &cur_e);
			PriorElem(L[i_num], cur_e, &pre_e);
			if (PriorElem(L[i_num], cur_e, &pre_e) == OK)
				printf("其前驱元素为：%d\n", pre_e);
			else if (PriorElem(L[i_num], cur_e, &pre_e) == OVERFLOW)
				printf("顺序表中没有该元素！\n");
			else  printf("其不存在前驱元素！\n");
			getchar(); getchar();
			break;


		case 9:
			//求出后置节点
			if (L[i_num] == NULL)
			{
				printf("线性表不存在!\n");
				getchar(); getchar();
				break;
			}
			printf("请输入数据元素：\n");
			scanf("%d", &cur_e);
			if (NextElem(L[i_num], cur_e, &next_e) == OK)
				printf("其后继元素为：%d\n", next_e);
			else if (NextElem(L[i_num], cur_e, &pre_e) == OVERFLOW)
				printf("顺序表中没有该元素！\n");
			else
			{
				printf("其不存在后继元素！\n");
			}
			getchar(); getchar();
			break;

		case 10:
			//插入元素
			if (L[i_num] == NULL)
			{
				printf("线性表不存在!\n");
				getchar(); getchar();
				break;
			}
			printf("请输入您要插入的数据元素：\n");
			scanf("%d", &e);
			printf("请输入您要插入的数据元素的位置：\n");
			scanf("%d", &i);
			if (ListInsert(&L[i_num], i, e) == OK)
				printf("插入数据元素成功！\n");
			else
				printf("插入数据元素失败！\n");
			getchar(); getchar();
			break;

		case 11:
			//删除元素
			if (L[i_num] == NULL)
			{
				printf("线性表不存在!\n");
				getchar(); getchar();
				break;
			}
			printf("请输入您要删除的数据元素的位置：\n");
			scanf("%d", &i);
			if (ListDelete(&L[i_num], i, &e) == OK)
				printf("删除数据元素成功！\n");
			else
				printf("删除数据元素失败！\n");
			getchar(); getchar();
			break;

		case 12:
			//遍历线性表中的元素
			if (L[i_num] == NULL)
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
			if (L[i_num] == NULL)
			{
				printf("线性表不存在!\n");
				getchar(); getchar();
				break;
			}
			if (SaveList(L[i_num], filename) == OK)
				printf("文件保存成功!文件名为%s\n", filename);
			getchar(); getchar();
			break;

		case 14:
			//加载文件，需要输入需要加载的名称
			InitList(&L[i_num]);
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
			if (L[i_num] == NULL)
			{
				printf("线性表不存在!\n");
				getchar(); getchar();
				break;
			}
			printf("请输入排序准则，0代表升序，1代表降序\n");
			scanf("%d", &tag);
			if (SortList(L[i_num], tag) == OK)
			{
				printf("排序成功!排序后顺序表为：\n");
				ListTraverse(L[i_num]);
			}
			else printf("表为空表!\n");
			getchar(); getchar();
			break;

		case 16:
			//反转链式线性表
			if (L[i_num] == NULL)
			{
				printf("线性表不存在!\n");
				getchar(); getchar();
				break;
			}
			if (ReverseList(&L[i_num]) == OK)
			{
				printf("反转链式表成功!反转后顺序表为：\n");
				ListTraverse(L[i_num]);
			}
			else printf("表为空表!\n");
			getchar(); getchar();
			break;

		case 17:
			//删除表中所有与给定数据相同的结点
			if (L[i_num] == NULL)
			{
				printf("线性表不存在!\n");
				getchar(); getchar();
				break;
			}
			printf("请输入所要删除的数据\n");
			scanf("%d", &val);
			flag = RemoveSpecificData(L[i_num], val);
			if (flag == OK)printf("删除成功!\n");
			else if (flag == INFEASTABLE)printf("表为空表!\n");
			else printf("表中无此元素!\n");
			getchar(); getchar();
			break;

		case 18:
			//合并两个有序链表
			printf("请选择所要合并的两个有序链表的序号：");
			scanf("%d %d", &i_num1, &i_num2);
			if (L[i_num1] == NULL || L[i_num2] == NULL)
			{
				printf("线性表不存在!\n");
				getchar(); getchar();
				break;
			}
			flag = MergeList(&L[i_num1], &L[i_num2]);
			if (flag == OK)
			{
				printf("合并成功，合并后的线性表存储在第%d号表中\n", i_num1);
			}
			else if (flag == ERROR)printf("两个表均为空表\n");
			else if (flag == INFEASTABLE)printf("输入不为升序表！\n");
			getchar(); getchar();
			break;

		case 19:
			//判断回文链表
			if (L[i_num] == NULL)
			{
				printf("线性表不存在!\n");
				getchar(); getchar();
				break;
			}
			if (L[i_num]->next == NULL)
			{
				printf("线性表为空!\n");
				getchar(); getchar();
				break;
			}
			if (IsPalindromeList(L[i_num]->next) == TRUE)
				printf("它是回文链表\n");
			else printf("它不是回文链表\n");
			getchar(); getchar();
			break;

		case 20:
			printf("请选择所要相加的两个有序链表的序号：");
			scanf("%d %d", &i_num1, &i_num2);
			if (L[i_num1] == NULL || L[i_num2] == NULL)
			{
				printf("线性表不存在!\n");
				getchar(); getchar();
				break;
			}
			if (ListAddition(&L[i_num1], &L[i_num2]) == ERROR)printf("存在空表，无法相加");
			else
			{
				printf("合并成功，合并后的线性表存储在第%d号表中\n", i_num1);
			}
			getchar(); getchar();
			break;

		case 21:
			//选择所操作的表的序号
			printf("请输入要在第几个表操作，可选择1~%d的序号\n ", MAX_NUM);
			scanf("%d", &i_num);
			printf("正在对第%d个表进行操作\n", i_num);
			if ((i_num < 1) || (i_num > 10))
			{
				printf("请选择正确范围！\n");
				i_num = 1;
			}
			getchar(); getchar();
			break;

		case 0:
			break;
		}
	}
	printf("OhOhOhOh!!!");
	return 0;
}
/*--------page 23 on textbook --------------------*/


/*
函数名称：IntiaList
函数功能：构造一个空的线性表
初始条件：线性表不存在
操作结果：创建一个空的线性表，空间不足时返回OVERFLOW，成功时返回OK
*/
status InitList(LinkList* L)
{
	if (*L)return ERROR;
	*L = (LinkList)malloc(sizeof(LNode));//动态分配
	if (*L == NULL)
	{
		return OVERFLOW;//空间不足返回OVERFLOW
	}
	(*L)->data = 0;
	(*L)->next = NULL;//链表带表头结点，其数据域为0
	return OK;
}

/*
函数名称：DestoryList
函数功能：销毁线性表
初始条件：线性表L已存在
操作结果：销毁线性表，进行其他操作时显示线性表不存在，成功返回OK
*/
status DestroyList(LinkList* L)
{
	LinkList p, q;
	p = *L;
	while (p)
	{
		q = p->next;//q指向p的下一个节点
		free(p);//释放p指向的空间
		p = q;//移位
	}
	*L = NULL;//L指向空
	return OK;
}

/*
函数名称：ClearList
函数功能：重置顺序表
初始条件：线性表L已存在
操作结果：将线性表的所有数据元素清空，成功返回OK
*/
status ClearList(LinkList* L)
{
	LinkList p, q;
	p = (*L)->next;
	while (p)
	{
		q = p->next;//q指向p的下一个节点
		free(p);//释放p指向的空间
		p = q;//移位
	}
	(*L)->next = NULL;//表头节点的指针域指向NULL
	return OK;
}

/*
函数名称：ListEmpty
函数功能：判断线性表是否为空
初始条件：线性表L已存在
操作结果：若线性表为空则返回NULL
*/
status ListEmpty(LinkList L)
{
	return L->next ? FALSE : TRUE;
}

/*
函数名称：ListLength
函数功能：求线性表的表长
初始条件：线性表已存在
操作结果：返回线性表中数据元素的长度
*/
int ListLength(LinkList L)
{
	int len = 0;
	LinkList p = L->next;//指向第一个结点
	while (p)
	{
		len++;
		p = p->next;//p指向下一个结点
	}
	return len;
}


/*
函数名称：GetElem
函数功能：得到某一个元素的值
初始条件：线性表已存在，1<=i<=ListLength(L)
操作结果：若访问位置不正确返回ERROR,否则用e记录数据域，返回OK
*/
status GetElem(LinkList L, int i, ElemType* e)
{
	int place = 1;//place记录当前位置
	LinkList p = L->next;
	while (p && place < i)
	{
		p = p->next;//找到i节点
		place++;
	}
	if (!p || place > i)
	{
		return ERROR;//判断访问位置是否正确
	}
	*e = p->data;//用e记录结点的数据
	return OK;
}

/*
函数名称：LocateElem
函数功能：查找元素
初始条件：线性表已存在
操作结果：返回L中第1个与e满足函数关系compare()的数据元素的位置，若这样的数据元素不存在，则返回0
*/
int LocateElem(LinkList L, ElemType e, status(*compare)(ElemType a, ElemType b))
{
	int i = 0;
	LinkList p = L->next;//p指向第一个节点
	while (p)
	{
		i++;
		if ((*compare)(p->data, e))//对每一个遍历到的元素进行比较
			return i;//找到元素所在位置就返回
		p = p->next;
	}
	return 0;
}

/*
函数名称：compare
函数功能：比较大小，服务于LocateList函数
初始条件：作为比较标准的元素和待比较元素
操作结果：若满足比较条件返回TRUE否则返回FALSE
*/
status compare(ElemType a, ElemType b)
{
	return a == b;//相等返回TRUE
}

/*
函数名称：PriorElem
函数功能：返回传入元素的前驱
初始条件：线性表L存在
操作结果：若第一个元素就等于cur_e，则它不存在前驱，返回ERROR;若线性表中无此元素，则返回OVERFLOW；否则用pre_e记录前驱元素，返回OK
*/
status PriorElem(LinkList L, ElemType cur_e, ElemType* pre_e)
{
	LinkList p = L->next;
	if (p->data == cur_e) return ERROR;
	while (p->next != NULL && p->next->data != cur_e)
	{
		p = p->next;
	}
	if (p->next == NULL)//遍历完p指针指向空，则意味着表中没有该元素
		return OVERFLOW;
	*pre_e = p->data;//用pre_e记录p指向的结点的元素，即输入元素的前驱
	return OK;
}

/*
函数名称：NextElem
函数功能：求后继节点
初始条件：线性表L存在
操作结果：若最后一个元素等于cur_e，则它不存在后继元素，返回ERROR;若线性表中无此元素，返回OVERFLOW;否则用next_e记录后继元素，返回OK
*/
status NextElem(LinkList L, ElemType cur_e, ElemType* next_e)
{
	LinkList p = L->next;
	while (p->next != NULL && p->data != cur_e)
	{
		p = p->next;//循环的方式找到所要找的元素的前一个节点
	}
	if (p->next == NULL && p->data != cur_e)//此时p指针指向NULL，p指向节点的值不是输入的元素，那么没有输入的元素
		return OVERFLOW;
	if (p->next == NULL && p->data == cur_e)//此时p指针指向NULL，p指向节点的值是输入的元素，那么没有后继节点
		return ERROR;
	*next_e = p->next->data;//next_e记录p所指向结点的下一个结点的值
	return OK;
}

/*
函数名称：ListInsert
函数功能：插入元素
初始条件：线性表L已存在且非空，1≤i≤ListLength(L)+1
操作结果：在表中第i个位置插入元素e；位置不正确返回ERROR,否则插入元素，返回OK
*/
status ListInsert(LinkList* L, int i, ElemType e)
{
	int j = 1;
	LinkList p, q;
	p = *L;
	while (p && j < i)
	{
		p = p->next;
		j++;
	}
	if (!p || j > i)
		return ERROR;//还没到插入位置p就到达NULL或者插入位置不正确
	q = (LinkList)malloc(sizeof(LNode));//给插入元素分配空间
	if (q == NULL)
	{
		exit(OVERFLOW);//空间不足
	}
	q->data = e;
	q->next = p->next;
	p->next = q;
	return OK;
}

/*
函数名称：ListDelete
函数功能：删除元素
初始条件：线性表L已存在且非空，1≤i≤ListLength(L)；
操作结果：若位置不正确则返回ERROR,否则删除元素返回OK
*/
status ListDelete(LinkList* L, int i, ElemType* e)
{
	int j = 1;
	LinkList p, q;
	p = *L;
	while (p->next && j < i)
	{
		p = p->next;//找到删除位置，同时p的下一个节点不为空
		j++;
	}
	if (!(p->next) || j > i)
		return ERROR;//或是空表，或是删除位置不对

	q = p->next;
	p->next = q->next;
	*e = q->data;
	free(q);
	//删除结点，e记录结点中的值
	return OK;
}

/*
函数名称：ListTraverse
函数功能：遍历顺序表
初始条件：线性表L存在
操作结果：顺序输出L中所有元素，空表返回ERORR，否则返回OK
*/
status ListTraverse(LinkList L)
{
	LinkList p = L->next;
	if (!p)//此时为空表
		return ERROR;
	while (p)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	return OK;
}

/*
函数名称：SaveList
函数功能：保存线性表
初始条件：线性表L存在
操作结果：使用文件读写将L的长度，容量及各数据元素存入filename数组
*/
status SaveList(LinkList L, char* filename)
{
	LinkList p = L->next;//指针指向第一个节点
	int listsize = LIST_INIT_SIZE;
	if ((fp = fopen(filename, "w")) == NULL)
	{
		printf("文件保存失败！");
		return ERROR;
	}
	fprintf(fp, "%d ", ListLength(L));//将元素个数写入
	fprintf(fp, "%d ", listsize);//将容量写入
	while (p)
	{
		fprintf(fp, "%d ", p->data);//写入数据元素
		p = p->next;
	}
	fclose(fp);
	return OK;
}

/*
函数名称：LoadList
函数功能：加载文件
初始条件：filename不为空，能够写入L
操作结果：使用文件读写将filename中存储的length,listsize，和各元素写入表L
*/
status LoadList(LinkList* L, char* filename)
{
	int i = 1, length = 0, listsize;
	ElemType e;
	if ((fp = fopen(filename, "r")) == NULL)
	{
		printf("文件加载失败!");
		return ERROR;
	}
	fscanf(fp, "%d ", &length);
	fscanf(fp, "%d ", &listsize);
	fscanf(fp, "%d ", &e);
	while (i <= length)
	{
		ListInsert(L, i, e);
		fscanf(fp, "%d ", &e);
		i++;
	}
	fclose(fp);
	return OK;
}

/*
函数名称：SortList
函数功能：对线性表中的数据进行升序或降序排序
初始条件：线性表非空
操作结果：根据所选择的序号选择升序排列还是排列，返回OK
*/
status SortList(LinkList L, int tag)
{
	LinkList p = L->next; LinkList q = L->next;
	int sum = 0;
	while (p)
	{
		p = p->next;
		sum++;
	}//计算表长
	if (!sum)return ERROR;
	if (tag == 0)//tag==0执行升序
	{
		for (int i = 0; i < sum - 1; i++)
		{
			for (int j = 0; j < sum - 1 - i; j++)
			{
				if (q->next->data < q->data)
				{
					int tem = q->next->data;
					q->next->data = q->data;
					q->data = tem;
				}
				q = q->next;
			}
			q = L->next;
		}
	}
	else//tag==1执行降序
	{
		for (int i = 0; i < sum - 1; i++)
		{
			for (int j = 0; j < sum - 1 - i; j++)
			{
				if (q->next->data > q->data)
				{
					int tem = q->next->data;
					q->next->data = q->data;
					q->data = tem;
				}
				q = q->next;
			}
			q = L->next;
		}
	}
	return OK;
}

/*
函数名称：ReverseList
函数功能：将线性表数据元素反转
初始条件：线性表L非空
操作结果：表中顺序反转，如1->2->3变为3->2->1
*/
status ReverseList(LinkList* L)
{
	LinkList pre = (*L)->next;
	if (!pre)return ERROR;//表为空
	LinkList cur = NULL;//将要被指向的结点置为NULL
	while (pre)
	{
		LinkList t = pre->next;
		pre->next = cur;
		cur = pre;
		pre = t;//反转，同时将pre前移，为NULL时退出
	}
	(*L)->next = cur;//修改表头结点的指向为新的首结点
	return OK;
}

/*
函数名称：RemoveSpecificData
函数功能：将线性表中所有等于val的数据删除
初始条件：线性表非空
操作结果：若表中没有等于val的元素，返回ERROR，否则删除完毕后返回OK
*/
status RemoveSpecificData(LinkList L, int val)
{
	LinkList p = L;
	int tag = 0;
	if (p->next == NULL)return INFEASTABLE;//表为空
	while (p->next)
	{
		if (p->next->data == val)
		{
			LinkList tem = p->next;
			p->next = p->next->next;//删除等于val的结点
			tag = 1;//表示表中有与val相等的元素
			free(tem);
		}
		else p = p->next;
	}
	if (!tag)return ERROR;//表中没有等于val的元素
	return OK;
}

/*
函数名称：MergeList
函数功能：将两个有序线性表合并成一个新的线性表
初始条件：两个有序线性表L1，L2
操作结果：得到一个含L1，L2的所有元素的线性表
*/
status MergeList(LinkList* L1, LinkList* L2)
{
	if ((*L1)->next == NULL && (*L2)->next == NULL)return ERROR;
	LinkList c1 = (*L1)->next, c2 = (*L2)->next;
	while (c1 && c1->next) {
		if (c1->data > c1->next->data)return INFEASTABLE;
		c1 = c1->next;
	}
	while (c2 && c2->next) {
		if (c2->data > c2->next->data)return INFEASTABLE;
		c2 = c2->next;
	}
	if ((*L1)->next == NULL) {
		*L1 = *L2;
		return OK;
	}
	if ((*L2)->next == NULL) {
		return OK;
	}
	LinkList head = (LinkList)malloc(sizeof(LNode));
	LinkList p = (*L1)->next; LinkList q = (*L2)->next;
	LinkList move = head;
	while (p && q)
	{
		move->next = (LinkList)malloc(sizeof(LNode));
		move = move->next;
		if (p->data <= q->data)
		{
			move->data = p->data;
			p = p->next;
		}
		else
		{
			move->data = q->data;
			q = q->next;
		}
	}
	if (p)move->next = p;
	else if (q)move->next = q;
	(*L1) = head;

	return OK;
}

/*
函数名称：IsPalindromeList
函数功能：判断一个链表是否是回文链表
初始条件：线性表非空
操作结果：若链表是回文链表则返回TRUE，否则返回FALSE;
*/
status IsPalindromeList(LinkList L)
{
	frontPointer = L;
	return RecursivelyCheck(L);//传入带有数据元素的首结点
}

/*
函数名称：RecursivelyCheck
函数功能：用于递归判断链表是否为回文链表，给IsPalindromeList函数返回TRUE或FALSE;
初始条件：链表头结点currentNode存在
操作结果：递归过程中出现前后元素不相等返回FALSE，递归遍历过程结束发现是回文链表则返回TRUE;
*/
status RecursivelyCheck(LinkList currentNode) {
	if (currentNode != nullptr) {
		if (!RecursivelyCheck(currentNode->next)) {
			return FALSE;//首先通过递归调用将currentNode移动到了链表末尾的NULL,这时返回TRUE，
			//跳出这个if语句，currentNode回到上一个结点，去判定下一个判定结点数据元素是否相等的if语句
		}
		if (currentNode->data != frontPointer->data) {
			return FALSE;//frontPointer起初在表头，而currentNode到达表尾，这时判定对应结点数据元素是否相等，每一层递归回溯currentNode会回到上个结点;
			//而下文中语句会控制frontPointer移动到下一个结点，继续比较
		}
		frontPointer = frontPointer->next;//不返回FALSE，则说明当前数据元素对应相等，继续比较下一个元素
	}
	return TRUE;//递归完成不返回FALSE则返回TRUE;
}


/*
函数名称：ListAddition
函数功能：假设L1,L2记录两个整数，高位在前，低位在后，将两个链表表示的整数进行相加，得到的整数用第一个
链表存储，依然高位在前并且没有前导0；
初始条件：两个非空链表L1,L2
操作结果：L1修改为相加后的整数，每一个结点存储一个位，高位在前
*/
status ListAddition(LinkList* L1, LinkList* L2)
{
	if ((*L1)->next == NULL || (*L2)->next == NULL)return ERROR;//有一张表为空则返回ERROR;
	LinkList head = (LinkList)malloc(sizeof(LNode)); head->data = 0; head->next = NULL;
	LinkList q1 = (*L1)->next, q2 = (*L2)->next;//q1,q2分别指向两个首结点
	int a[100], b[100], ans[100]; int sum1 = 0, sum2 = 0;//sum1和sum2记录两个数的数位
	for (int i = 0; i < 100; i++)a[i] = b[i] = ans[i] = 0;
	int flag1 = 0, flag2 = 0;//用于跳过前导0；
	while (q1)
	{
		if (q1->data == 0)
		{
			if (!flag1)//flag为1时表示已经遇到非零数，则以后的0都必须加入数组
			{
				q1 = q1->next;
				continue;//前导0跳过
			}
		}
		flag1 = 1;
		a[sum1++] = q1->data;
		q1 = q1->next;
	}
	while (q2)
	{
		if (q2->data == 0)
		{
			if (!flag2)//原理同上
			{
				q2 = q2->next;
				continue;
			}
		}
		flag2 = 1;
		b[sum2++] = q2->data;
		q2 = q2->next;
	}
	for (int l = 0, r = sum1 - 1; l < r; l++, r--)
	{
		int tem = a[l]; a[l] = a[r]; a[r] = tem;
	}
	for (int l = 0, r = sum2 - 1; l < r; l++, r--)
	{
		int tem = b[l]; b[l] = b[r]; b[r] = tem;
	}//将位数反转，从最小位数开始相加
	int pro = 0, mx = (sum1 > sum2) ? sum1 : sum2;//pro表示进位，mx是最大位数
	for (int i = 0; i < mx; i++)
	{
		ans[i] = a[i] + b[i] + pro;//答案的当前位数为两个数组中对应位的数加上可能有的进位1
		pro = 0;
		if (ans[i] > 9) {
			ans[i] %= 10;
			pro = 1;//一个位上的数字大于9则进位处理
		}
	}
	if (pro == 1)ans[mx] = 1, mx++;//对最高位进行特判
	LinkList p = head;
	for (int place = mx - 1; place >= 0; place--)
	{
		p->next = (LinkList)malloc(sizeof(LNode));
		p->next->data = ans[place];//从最高位逐步读入位数
		p = p->next;
	}
	p->next = NULL;
	(*L1) = head;
	return OK;
}
