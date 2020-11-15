#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#include <queue>
#include <algorithm>
using namespace std;

//数据元素类型定义
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int KeyType;
typedef struct {
	KeyType  key;
	char others[20];
} TElemType; //二叉树结点类型定义


typedef struct BiTNode {  //二叉链表结点的定义
	TElemType  data;
	struct BiTNode* lchild, * rchild;
} BiTNode, * BiTree;

typedef struct {
	BiTree T;//创建二叉树用的指针T
	char name[20];//用于保存树的名称
}LElemType;

typedef struct {
	LElemType tree[20];//多个树进行操作
	int listsize;
}SqList;


//全局变量
int tail = 0;//文件操作时作为位置后移的标志
int p = 0;//记录树中所有关键字时用
int k[200];//存储树中所有的关键字
int place = 0;//初始建树时用
int MaxDistance;//用于求二叉树直径
int MaxNum = -1;//用于得到树中最大路径和

//辅助函数
bool check1(TElemType definition[]);
status BuildTree(BiTree& T, TElemType definition[]);
void checkkey(int k[], BiTree& T);
status check2(BiTree& T, KeyType e, TElemType value);
void Ass(BiTree& T, KeyType e, TElemType value);
bool check3(BiTree& T, int e);
status Insert(BiTree& T, KeyType e, int LR, TElemType c);
BiTree find(BiTree& T);
status Delete(BiTree& T, KeyType e);
void visit(BiTree T);
int write(BiTree T, FILE* fp);
int create(BiTree& T, int a[100], char b[100][20]);
BiTNode* SearchAncestor(BiTree T, BiTNode* p, BiTNode* q);
int UpdateDepth(BiTree T);
int maxGain(BiTree node);



//主要函数
status CreateBiTree(BiTree& T, TElemType definition[]);
status ClearBiTree(BiTree& T);
int BiTreeDepth(BiTree T);
BiTNode* LocateNode(BiTree T, KeyType e);
status Assign(BiTree& T, KeyType e, TElemType value);
BiTNode* GetSibling(BiTree T, KeyType e);
status InsertNode(BiTree& T, KeyType e, int LR, TElemType c);
status DeleteNode(BiTree& T, KeyType e);
status PreOrderTraverse(BiTree T, void (*visit)(BiTree));
status InOrderTraverse(BiTree T, void (*visit)(BiTree));
status PostOrderTraverse(BiTree T, void (*visit)(BiTree));
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree));
status SaveBiTree(BiTree T, char FileName[]);
status LoadBiTree(BiTree& T, char FileName[]);
status IsBalanced(BiTree T);
BiTNode* CommonAncestor(BiTree T, int key1, int key2);
status IsCousins(BiTree T, int key1, int key2);
int DiameterOfTree(BiTree T);
status InvertTree(BiTree T);
status HasPathSum(BiTree T, int sum);
int maxPathSum(BiTree T);

int main() {
	TElemType definition[100];
	char filename[30];
	status tag;
	SqList L;//相当于用数组构建多树操作的框架
	BiTNode* TN;
	int op = 1;//op用来case
	int i, num = 1, LR;//num默认为1，即默认在第一棵树进行操作，LR用来表示方向
	int ans; int dep = 0;
	int e;//用于输入待查找的结点的关键字
	int key1, key2;//查找最近公共祖先时用
	int sum;//判断是否存在路径和时所用的路径总和
	TElemType v;
	BiTNode* node;
	for (i = 0; i < 20; i++)
	{
		L.tree[i].T = NULL;//相当于创建20个定义中类型的树的指针，同时指空，即20个树；
	}

	while (op) {
		system("cls");//系统函数，用于清屏
		printf("\n\n");
		printf("\t\t      Menu for Binary Tree On Binary Linked List \n");
		printf("\t*****************************************************************************\n");
		printf("\t\t\t1.  CreateBiTree        2.  ClearBiTree\n");
		printf("\t\t\t3.  BiTreeDepth		4.  LocateNode\n");
		printf("\t\t\t5.  Assign		6.  GetSibling\n");
		printf("\t\t\t7.  InsertNode          8.  DeleteNode\n");
		printf("\t\t\t9.  PreOrderTraverse    10.  InOrderTraverse\n");
		printf("\t\t\t11.  PostOrderTraverse  12.  LevelOrderTraverse\n");
		printf("\t\t\t13.  SaveBiTree         14.  LoadBiTree\n");
		printf("\t\t\t15.  IsBalanced		16.  CommonAncestor\n");
		printf("\t\t\t17.  IsCousins		18.  DiameterOfTree\n");
		printf("\t\t\t19.  InvertTree	        20.  HasPathSum\n");
		printf("\t\t\t21.  maxPathSum		22.  Choose The Tree\n");
		printf("\t\t\t请选择你的操作[0~20]\n");
		scanf("%d", &op);
		switch (op)
		{

		case 1:
			i = 0; place = 0;
			do {
				scanf("%d%s", &definition[i].key, definition[i].others);
			} while (definition[i++].key != -1);
			ans = CreateBiTree(L.tree[num - 1].T, definition);
			if (ans == OK)
			{
				printf("创建成功!\n");
			}
			else printf("关键字不唯一!\n");
			getchar(); getchar();
			break;

		case 2:
			if (L.tree[num - 1].T == NULL)
			{
				printf("二叉树不存在！\n");
				getchar(); getchar();
				break;
			}
			ClearBiTree(L.tree[num - 1].T);
			printf("二叉树清空成功！\n");
			getchar(); getchar();
			break;

		case 3:
			if (L.tree[num - 1].T == NULL)
			{
				printf("二叉树不存在！\n");
				getchar(); getchar();
				break;
			}
			dep = BiTreeDepth(L.tree[num - 1].T);
			printf("树的深度为%d\n", dep);
			getchar(); getchar();
			break;


		case 4:
			if (L.tree[num - 1].T == NULL)
			{
				printf("二叉树不存在！\n");
				getchar(); getchar();
				break;
			}
			printf("请输入要查找的结点的关键字\n");
			scanf("%d", &e);
			node = LocateNode(L.tree[num - 1].T, e);
			if (node)printf("%d,%s\n", node->data.key, node->data.others);
			else printf("树中无此元素\n");
			getchar(); getchar();
			break;

		case 5:
			if (L.tree[num - 1].T == NULL)
			{
				printf("二叉树不存在！\n");
				getchar(); getchar();
				break;
			}
			p = 0;
			printf("请输入待赋值的结点的关键字，用于替换的数据域的关键字与内容:\n");
			scanf("%d%d%s", &e, &v.key, v.others);
			ans = Assign(L.tree[num - 1].T, e, v);
			if (ans == OK)
			{
				printf("赋值成功!\n");
			}
			else if (ans == INFEASIBLE)printf("无此结点!\n");
			else printf("赋值后出现关键字重复!\n");
			getchar(); getchar();
			break;

		case 6:
			if (L.tree[num - 1].T == NULL)
			{
				printf("二叉树不存在！\n");
				getchar(); getchar();
				break;
			}
			printf("请输入需要查找兄弟结点的结点的关键字:\n");
			scanf("%d", &e);
			node = GetSibling(L.tree[num - 1].T, e);
			if (node) printf("兄弟结点为%d,%s\n", node->data.key, node->data.others);
			else printf("无兄弟结点\n");
			getchar(); getchar();
			break;

		case 7:
			if (L.tree[num - 1].T == NULL)
			{
				printf("二叉树不存在！\n");
				getchar(); getchar();
				break;
			}
			printf("请依次输入关键字e（这个结点作为待插入结点的双亲），LR（0代表作为左孩子插入，1代表作为右孩子插入），待插入结点的关键字与内容\n");
			scanf("%d%d%d%s", &e, &LR, &v.key, v.others);
			ans = InsertNode(L.tree[num - 1].T, e, LR, v);
			if (ans == OK)printf("插入操作成功!\n");
			else printf("插入操作失败!\n");
			getchar(); getchar();
			break;

		case 8:
			if (L.tree[num - 1].T == NULL)
			{
				printf("二叉树不存在！\n");
				getchar(); getchar();
				break;
			}
			printf("请输入要删除的结点的关键字:\n");
			scanf("%d", &e);
			ans = DeleteNode(L.tree[num - 1].T, e);
			if (ans == OK)printf("结点删除成功!\n");
			else printf("结点删除失败!\n");
			getchar(); getchar();
			break;

		case 9:
			if (L.tree[num - 1].T == NULL)
			{
				printf("二叉树不存在！\n");
				getchar(); getchar();
				break;
			}
			printf("它的前序遍历结果为:\n");
			PreOrderTraverse(L.tree[num - 1].T, visit);
			getchar(); getchar();
			break;

		case 10:
			if (L.tree[num - 1].T == NULL)
			{
				printf("二叉树不存在！\n");
				getchar(); getchar();
				break;
			}
			printf("它的中序遍历结果为:\n");
			InOrderTraverse(L.tree[num - 1].T, visit);
			getchar(); getchar();
			break;

		case 11:
			if (L.tree[num - 1].T == NULL)
			{
				printf("二叉树不存在！\n");
				getchar(); getchar();
				break;
			}
			printf("它的后序遍历结果为:\n");
			PostOrderTraverse(L.tree[num - 1].T, visit);
			getchar(); getchar();
			break;

		case 12:
			if (L.tree[num - 1].T == NULL)
			{
				printf("二叉树不存在！\n");
				getchar(); getchar();
				break;
			}
			printf("它的层序遍历结果为:\n");
			LevelOrderTraverse(L.tree[num - 1].T, visit);
			getchar(); getchar();
			break;

		case 13:
			if (L.tree[num - 1].T == NULL)
			{
				printf("二叉树不存在！\n");
				getchar(); getchar();
				break;
			}
			tail = 0;
			SaveBiTree(L.tree[num - 1].T, L.tree[num - 1].name);
			printf("文件保存成功!文件名为%s", L.tree[num - 1].name);
			getchar(); getchar();
			break;

		case 14:
			tail = 0;
			if (LoadBiTree(L.tree[num - 1].T, L.tree[num - 1].name) == ERROR) {
				printf("文件加载失败!");
				getchar(); getchar();
				break;
			}
			printf("文件%s加载成功!", L.tree[num - 1].name);
			getchar(); getchar();
			break;


		case 15:
			if (L.tree[num - 1].T == NULL)
			{
				printf("二叉树不存在！\n");
				getchar(); getchar();
				break;
			}
			if (IsBalanced(L.tree[num - 1].T))printf("它是一棵二叉平衡树!");
			else printf("它不是一棵二叉平衡树!");
			getchar(); getchar();
			break;

		case 16:
			if (L.tree[num - 1].T == NULL)
			{
				printf("二叉树不存在！\n");
				getchar(); getchar();
				break;
			}
			printf("请输入所要查找最近公共祖先的两个结点的关键字：\n");
			scanf("%d %d", &key1, &key2);
			TN = CommonAncestor(L.tree[num - 1].T, key1, key2);
			if (!TN)printf("所输入的关键字有不存在的结点\n");
			else {
				printf("找到公共祖先，它的关键字为%d，内容为%s\n", TN->data.key, TN->data.others);
			}
			getchar(); getchar();
			break;

		case 17:
			if (L.tree[num - 1].T == NULL)
			{
				printf("二叉树不存在！\n");
				getchar(); getchar();
				break;
			}
			printf("请输入要判断是否为堂兄弟结点的两个关键字:\n");
			scanf("%d %d", &key1, &key2);
			tag = IsCousins(L.tree[num - 1].T, key1, key2);
			if (tag == INFEASIBLE)printf("有关键字不在树中\n");
			else if (tag == TRUE)printf("这两个结点是堂兄弟\n");
			else printf("这两个结点不是堂兄弟\n");
			getchar(); getchar();
			break;

		case 18:
			if (L.tree[num - 1].T == NULL)
			{
				printf("二叉树不存在！\n");
				getchar(); getchar();
				break;
			}
			MaxDistance = DiameterOfTree(L.tree[num - 1].T);
			printf("二叉树的直径为:%d\n", MaxDistance);
			getchar(); getchar();
			break;

		case 19:
			if (L.tree[num - 1].T == NULL)
			{
				printf("二叉树不存在！\n");
				getchar(); getchar();
				break;
			}
			InvertTree(L.tree[num - 1].T);
			printf("翻转成功！\n");
			getchar(); getchar();
			break;

		case 20:
			if (L.tree[num - 1].T == NULL)
			{
				printf("二叉树不存在！\n");
				getchar(); getchar();
				break;
			}
			printf("请输入从根到叶子结点的路径结点总和的目标和:\n");
			scanf("%d", &sum);
			if (HasPathSum(L.tree[num - 1].T, sum))
				printf("存在从根节点到叶子结点的路径使路径上所有结点值相加为目标和%d\n", sum);
			else printf("不存在从根节点到叶子结点的路径使路径上所有结点值相加为目标和%d\n", sum);
			getchar(); getchar();
			break;

		case 21:
			if (L.tree[num - 1].T == NULL)
			{
				printf("二叉树不存在！\n");
				getchar(); getchar();
				break;
			}
			MaxNum = -1;
			printf("这棵树的最大路径和为:");
			maxPathSum(L.tree[num - 1].T);
			printf("%d", MaxNum);
			getchar(); getchar();
			break;

		case 22:
			printf("在第几个树操作只支持20个树进行操作: \n");
			scanf("%d", &num);
			printf("请输入这棵树的文件名:\n");
			scanf("%s", L.tree[num - 1].name);
			if (num < 1 || num>20)
			{
				printf("\t\t\t请选择正确范围！\n");
				num = 1;
			}
			getchar(); getchar();
			break;

		case 0:
			break;
		}
	}
	printf("\n");
	printf("OhOhOhOhOh！\n\n");
	return 0;
}


/*
函数名称：check1
函数功能：检测输入definition的过程中出现结点关键字相同的情况，若是则返回false，不存在则返回true；
*/
bool check1(TElemType definition[])
{
	int t[500] = { 0 };
	for (int i = 0; definition[i].key != -1; i++)
	{
		if (definition[i].key == 0)continue;//0表示为空，无需计数
		if (t[definition[i].key] == 1)return false;//当发现有结点已被计数时说明重复了
		t[definition[i].key]++;//关键字的数量加1
	}
	return true;
}
/*
函数名称：BuildTree
函数功能：递归建立树的每一个结点
*/
status BuildTree(BiTree& T, TElemType definition[])
{
	if (definition[place].key == -1)return 0;//-1表示输入终止
	if (definition[place].key == 0) {
		T = NULL;
		return OK;//key为0表示空结点
	}
	else
	{
		T = (BiTree)malloc(sizeof(BiTNode));//申请空间
		T->data.key = definition[place].key;//赋值关键字
		for (int j = 0; j < 20; j++)T->data.others[j] = definition[place].others[j];//赋值内容
	}
	place++;
	BuildTree(T->lchild, definition);//以前序遍历输入，所以先递归建立左子树
	place++;
	BuildTree(T->rchild, definition);//后递归建立右子树
	return OK;
}
/*
函数名称：CreateBiTree
函数功能：依据definition里的前序遍历输入来构建一个二叉树
初始条件：含有二叉树结点关键字与内容的结构体数组definition
操作结果：若存在重复关键字返回ERROR；否则建立一棵二叉树L.tree[num-1].T,返回OK；
*/
status CreateBiTree(BiTree& T, TElemType definition[])
{
	if (check1(definition) == false)return ERROR;//先检查存不存在重复
	BuildTree(T, definition);//递归建树
	return OK;
}


/*
函数名称：ClearBiTree
函数功能：清空树的内容
初始条件：一个已构建的二叉树,可以是空树
操作结果：释放树中每个结点的空间，根结点T指向NULL，返回OK
*/
status ClearBiTree(BiTree& T)
{

	if (T == NULL)return OK;//为空结点则直接返回OK
	if (T->lchild)ClearBiTree(T->lchild);//若左结点不为空，则递归清空左子树
	if (T->rchild)ClearBiTree(T->rchild);//清空右子树
	free(T);//释放结点的空间
	T = NULL;//指向NULL
	return OK;

}


/*
函数名称：BiTreeDepth
函数功能：求二叉树的深度
初始条件：一棵已构建的二叉树
操作结果：返回树的深度
*/
int BiTreeDepth(BiTree T)
{

	int depth = 0;//初始化时深度为0
	if (T)
	{
		int lchilddepth = BiTreeDepth(T->lchild);//递归得到左子树的深度
		int rchilddepth = BiTreeDepth(T->rchild);//底肥得到右子树的深度
		depth = (lchilddepth >= rchilddepth ? (lchilddepth + 1) : (rchilddepth + 1));//得到左右子树的深度后，到当前结点的深度为左右结点深度的较大者加1
	}
	return depth;
}


/*
函数名称：LocateNode
函数功能：定位关键字为所给关键字的结点
初始条件：一棵已构建的树，所要查找的关键字key
操作结果：返回关键字等于key的结点
*/
BiTNode* LocateNode(BiTree T, KeyType e)
{
	if (T == NULL)return NULL;
	if (T->data.key == e)return T;
	if (LocateNode(T->lchild, e))return LocateNode(T->lchild, e);
	if (LocateNode(T->rchild, e))return LocateNode(T->rchild, e);
	return NULL;
}


/*
函数名称：checkkey
函数功能：将树的前序遍历结点的关键字记录入数组k
*/
void checkkey(int k[], BiTree& T)
{
	if (!T)return;
	k[p++] = T->data.key;
	checkkey(k, T->lchild);
	checkkey(k, T->rchild);
	return;
}
/*
函数名称：check2
函数功能：检查是否有结点等于key并且赋值后是否有关键字重复的情况
*/
status check2(BiTree& T, KeyType e, TElemType value)
{
	checkkey(k, T);//得到关键字数组k
	int tag = 0;
	for (int i = 0; i < p; i++)
		if (k[i] == e)
		{
			tag = 1;//若能替换，则tag=1，退出循环
			break;
		}
	if (!tag)return INFEASIBLE;//tag为0时说明找不到关键字为e的结点，返回INFEASIBLE
	int sum[200] = { 0 };//计数数组初始化为0
	for (int i = 0; i < p; i++)
	{
		if (k[i] == e)
		{
			sum[value.key]++;
			if (sum[value.key] > 1)return FALSE;//有关键字大于1则返回FALSE
		}
		else
		{
			sum[k[i]]++;
			if (sum[k[i]] > 1)return FALSE;
		}
	}
	return TRUE;
}
/*
函数名称：Ass
函数功能：递归地寻找关键字等于e的结点找到后进行重新赋值
*/
void Ass(BiTree& T, KeyType e, TElemType value)
{
	if (!T)return;
	if (T->data.key == e)//找到结点，进行赋值
	{
		T->data = value;
		return;
	}
	Ass(T->lchild, e, value);//未能返回则递归在左子树中进行赋值
	Ass(T->rchild, e, value);//右子树中进行赋值
	return;
}
/*
函数名称：Assign
函数功能：进行结点的赋值
初始条件：已构建的二叉树，待赋值的结点的关键字，新的data域TElemType类型的变量
操作结果：若重新赋值后关键字出现重复则返回ERROR否则成功赋值后返回OK
*/
status Assign(BiTree& T, KeyType e, TElemType value)
{
	status g = check2(T, e, value);
	if (g == INFEASIBLE)return INFEASIBLE;
	else if (g == ERROR)return ERROR;
	Ass(T, e, value);
	return OK;
}


/*
函数名称：GetSibling
函数功能：得到兄弟结点
前提条件：已构建的树
操作结果：返回传入结点的可能存在的兄弟结点
*/
BiTNode* GetSibling(BiTree T, KeyType e)
{
	if (T->data.key == e)return NULL;//若根节点的关键字就等于e了则它没有兄弟结点
	if (!T)return NULL;//若为空结点直接返回NULL
	if (T->lchild)
	{
		if (T->lchild->data.key == e)return T->rchild;//若左孩子存在且其中的key等于e，则返回右孩子
		if (GetSibling(T->lchild, e))return GetSibling(T->lchild, e);//递归在左子树中寻找
	}
	if (T->rchild)
	{
		if (T->rchild->data.key == e)return T->lchild;//若右孩子存在且其中的key等于e，则返回左孩子
		if (GetSibling(T->rchild, e))return GetSibling(T->rchild, e);//递归在右子树中寻找
	}
	return NULL;
}


/*
函数名称：check3
函数功能：检查是否存在关键字重复
*/
bool check3(BiTree& T, int e)
{
	if (!T)return true;
	if (T->data.key == e)return false;//存在相等则返回false
	return check3(T->lchild, e) && check3(T->rchild, e);//递归判断，若左右子树均不存在，则返回true
}
/*
函数名称：Insert
函数功能：插入节点
*/
status Insert(BiTree& T, KeyType e, int LR, TElemType c)
{
	if (!T)return ERROR;
	if (T->data.key == e)//等于e说明找到了结点
	{
		if (LR == 0)//结点应作为左孩子
		{
			if (T->lchild == NULL) {
				T->lchild = (BiTree)malloc(sizeof(BiTNode));
				T->lchild->data = c;
				T->lchild->lchild = NULL; T->lchild->rchild = NULL;//左子树为空直接申请空间进行赋值
			}
			else
			{
				BiTree node = T->lchild;
				BiTree newnode = (BiTree)malloc(sizeof(BiTNode));
				newnode->data = c;
				T->lchild = newnode;//修改左孩子为新的结点
				newnode->lchild = NULL; newnode->rchild = node;//原来的左节点作为新结点的右孩子
			}
		}
		else//结点应为右孩子
		{
			if (T->rchild == NULL) {
				T->rchild = (BiTree)malloc(sizeof(BiTNode));
				T->rchild->data = c;
				T->rchild->lchild = NULL; T->rchild->rchild = NULL;//右孩子为空直接申请空间进行赋值
			}
			else
			{
				BiTree node = T->rchild;
				BiTree newnode = (BiTree)malloc(sizeof(BiTNode));
				newnode->data = c;
				T->rchild = newnode;//修改右孩子为新的结点newnode
				newnode->lchild = NULL; newnode->rchild = node;//原来的右子树修改为newnode的右子树
			}
		}
		return OK;
	}
	if (Insert(T->lchild, e, LR, c))return OK;//key不为e则递归在左子树中进行插入
	if (Insert(T->rchild, e, LR, c))return OK;//递归在右子树中进行插入
	return ERROR;//找不到结点，返回ERROR
}
/*
函数名称：InsertNode
函数功能：插入结点到对应的位置
初始条件：已构建的子树，待插入的结点的data域，所要查找的结点的关键字，以及代表插入方式的整型常量LR
*/
status InsertNode(BiTree& T, KeyType e, int LR, TElemType c)
{
	if (check3(T, c.key) == false)return ERROR;//check没有问题才能进行插入
	if (LR == -1) {
		BiTree newT = (BiTree)malloc(sizeof(BiTNode));
		newT->data = c;
		newT->rchild = T;
		newT->lchild = NULL;//LR为-1时插入根节点，申请空间进行赋值
		T = newT;//修改根节点的指向
		return OK;
	}
	return Insert(T, e, LR, c);//不插入根节点则递归执行Insert函数
}


/*
函数名称：find
函数功能：找到一个树中最右的结点
*/
BiTree find(BiTree& T)
{
	if (T->rchild == NULL)return T;//若右子树为空则返回结点
	return find(T->rchild);//右子树不为空则在右子树中递归寻找
}
/*
函数名称：Delete
函数功能：递归地去寻找待删除的结点并删除
*/
status Delete(BiTree& T, KeyType e)
{
	if (T->lchild)//T的左子树存在
	{
		if (T->lchild->data.key == e)//左孩子的key正好等于e
		{
			if (T->lchild->lchild == NULL && T->lchild->rchild == NULL) {
				free(T->lchild);
				T->lchild = NULL;
			}//分情况执行，若左孩子为叶子结点，则直接删除
			else if (T->lchild->lchild && T->lchild->rchild)
			{
				BiTree node = find(T->lchild->lchild);//左孩子的左右结点均存在，则找到它的左孩子的左边的最右边的结点
				BiTree tem = T->lchild;//标记左孩子
				node->rchild = tem->rchild;
				T->lchild = tem->lchild;//修改指针域
				free(tem);
			}
			else if (T->lchild->lchild)
			{
				BiTree tem = T->lchild; T->lchild = tem->lchild;
				free(tem);//左孩子只有左孩子，则修改T的左孩子为左孩子的左孩子，再删除标记的tem
			}
			else if (T->lchild->rchild)
			{
				BiTree tem = T->lchild; T->lchild = tem->rchild;//原理同上
				free(tem);
			}
			return OK;
		}
		Delete(T->lchild, e);//未找到结点则在左子树中递归寻找并删除
	}
	if (T->rchild)//T的右子树存在
	{
		if (T->rchild->data.key == e)//右孩子的key正好等于e
		{
			if (T->rchild->lchild == NULL && T->rchild->rchild == NULL) {
				free(T->rchild);
				T->rchild = NULL;
			}//右孩子为叶子结点，直接删除
			else if (T->rchild->lchild && T->rchild->rchild)
			{
				BiTree node = find(T->rchild->lchild);//右孩子的左右结点均存在，则找到它的右孩子的左边的最右边的结点
				BiTree tem = T->rchild;//标记右孩子
				node->rchild = tem->rchild;
				T->rchild = tem->lchild;//修改指针域
				free(tem);
			}
			else if (T->rchild->lchild)
			{
				BiTree tem = T->rchild; T->rchild = tem->lchild;
				free(tem);//右孩子只有左孩子，则标记右孩子，修改T的右孩子域
			}
			else if (T->rchild->rchild)
			{
				BiTree tem = T->rchild; T->rchild = tem->rchild;
				free(tem);//修改T的右孩子域
			}
			return OK;
		}
		Delete(T->rchild, e);//未找到结点则在右子树中递归寻找
	}
}
/*
函数名称：DeleteNode
函数功能：删除结点
初始条件：已构建的树，所要删除的节点的关键字
操作结果：若成功删除结点，则返回OK，否则返回ERROR
*/
status DeleteNode(BiTree& T, KeyType e)
{

	if (!T)return ERROR;
	if (T->data.key == e)
	{
		BiTree node = T->lchild;
		BiTree right = find(node);//找到左子树中最右边的结点
		right->rchild = T->rchild;//T的右子树赋给right的右孩子指针
		T = node;//修改根的指向
		return OK;
	}
	if (Delete(T, e) == OK)return OK;//删除成功返回OK
	return ERROR;
}


/*
函数名称：visit
函数功能：访问一个结点的key和orthers
*/
void visit(BiTree T)
{
	printf(" %d,%s", T->data.key, T->data.others);
}


/*
函数名称：PreOrderTraverse
函数功能：输出先序遍历二叉树的序列
初始条件：已构建的二叉树，访问函数visit
操作结果：输出二叉树的先序遍历
*/
status PreOrderTraverse(BiTree T, void (*visit)(BiTree))
{
	BiTree st[100];//结点数组
	int top = 0;//栈的顶部
	if (T)
	{
		st[top++] = T;//初始化时将根入栈
		while (top)
		{
			BiTree tem = st[--top];//每次取栈顶元素
			if (tem)visit(tem);//非空则访问
			if (tem->rchild)st[top++] = tem->rchild;//由于先序遍历先输出左子树，则入栈时先右子树入栈
			if (tem->lchild)st[top++] = tem->lchild;//左子树入栈
		}
	}
	return OK;
}


/*
函数名称：InOrderTraverse
函数功能：输出中序遍历二叉树的序列
初始条件：已构建的二叉树，访问函数visit
操作结果：输出二叉树的中序遍历
*/
status InOrderTraverse(BiTree T, void (*visit)(BiTree))
{
	if (!T)return OK;
	InOrderTraverse(T->lchild, visit);//先递归遍历左子树
	visit(T);//输出结点
	InOrderTraverse(T->rchild, visit);//后递归遍历右子树
	return OK;
}


/*
函数名称：PostOrderTraverse
函数功能：输出后序遍历二叉树的序列
初始条件：已构建的二叉树，访问函数visit
操作结果：输出二叉树的后序遍历
*/
status PostOrderTraverse(BiTree T, void (*visit)(BiTree))
{
	if (!T)return OK;
	PostOrderTraverse(T->lchild, visit);//先递归左子树
	PostOrderTraverse(T->rchild, visit);//后递归右子树
	visit(T);
	return OK;
}


/*
函数名称：LevelOrderTraverse
函数功能：输出层次遍历二叉树的序列
初始条件：已构建的二叉树，访问函数visit
操作结果：输出二叉树的层次遍历
*/
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree))
{
	BiTree a[1000];//创建一个结点数组作为队列
	int in = 0, out = 0;//in是队列的尾部，out指向队列的头
	a[in++] = T;//根入队
	while (in > out)
	{
		if (a[out])
		{
			visit(a[out]);//从头输出
			a[in++] = a[out]->lchild;//左孩子入队
			a[in++] = a[out]->rchild;//右孩子入队
		}
		out++;//每访问一个结点，out后移
	}
	return OK;
}


/*
函数名称：write
函数功能：递归地将树中各个结点的内容读入文件
*/
int write(BiTree T, FILE* fp)
{
	if (!T) {
		fprintf(fp, "%d %s ", 0, '\0');
		return 0;
	}//空结点就读入0和空字符
	fprintf(fp, "%d %s ", T->data.key, T->data.others);//
	write(T->lchild, fp);//递归地去读入左子树的内容
	write(T->rchild, fp);//递归地去读入右子树的内容
	return 0;
}
/*
函数名称：SaveBiTree
函数功能：将二叉树的内容写入文件
初始条件：写入文件名和一棵已建好的二叉树
操作结果：创建一个文件，包含二叉树中所有结点的内容
*/
status SaveBiTree(BiTree T, char FileName[])
{
	FILE* fp = fopen(FileName, "w");//定义文件指针
	if (!fp) return ERROR;//空树返回error
	write(T, fp);//使用write函数写入树
	int a = -1;
	fprintf(fp, "%d ", a);//写入一个结束的结点
	fprintf(fp, "%s ", "jieshu");
	fclose(fp);
	return 0;
}


/*
函数名称：Create
函数功能：依据关键字数组和字符串数组递归地构建二叉树
*/
int create(BiTree& T, int a[100], char b[100][20])
{
	T = (BiTree)malloc(sizeof(BiTNode));//为新结点申请内存
	if (!a[tail]) { tail++; T = NULL; return 0; }//空树
	T->data.key = a[tail];
	int i;
	for (i = 0; b[tail][i] != '\0'; i++)
	{
		T->data.others[i] = b[tail][i];
	}
	T->data.others[i] = '\0';//读入字符串完毕后后一位置为空字符表示字符串结束的标志
	T->lchild = T->rchild = NULL;//左右子树置为NULL
	tail++;
	create(T->lchild, a, b);//递归构建左子树
	create(T->rchild, a, b);//递归构建右子树
}
/*
函数名称：LoadBiTree
函数功能：读入文件FileName的结点数据，创建二叉树
初始条件：包含二叉树各个结点内容的文件，一棵空树
操作结果：依据包含二叉树结点内容的文件构建一棵二叉树
*/
status LoadBiTree(BiTree& T, char FileName[])
{

	FILE* fp = fopen(FileName, "r");//文件指针，使用只读
	if (!fp) return ERROR;
	int a[100];//存储结点关键字key
	char b[100][20];//存储结点的内容字符串
	int i;
	for (i = 0; i < 100; i++) a[i] = 0;//key初始化置为0
	i = 0;
	do
	{
		fscanf(fp, "%d", &a[i]);
		fscanf(fp, "%s", b[i]);
		i++;
	} while (a[i - 1] != -1);//当读取的关键字不为-1时说明循环尚未结束，否则到达结尾退出循环
	create(T, a, b);//使用create函数构建二叉树
	fclose(fp);
	return OK;
}


/*
函数名称：IsBalanced
函数功能：判断一棵二叉树是否是二叉平衡树
初始条件：一棵已建好的二叉树
操作结果：若是二叉树返回1否则返回0
*/
status IsBalanced(BiTree T)
{
	return !T ? true : abs(BiTreeDepth(T->lchild) - BiTreeDepth(T->rchild)) <= 1 && IsBalanced(T->lchild) && IsBalanced(T->rchild);
	//若为空树直接返回OK，否则判断这个结点的左右子树高度差是否小于等于1以及递归判断左右孩子结点是否都满足
}


/*
函数名称：SearchAncestor
函数功能：递归地去寻找两个结点p，q的最近公共祖先
*/
BiTNode* SearchAncestor(BiTree T, BiTNode* p, BiTNode* q)
{
	if (T == p || T == q || T == NULL)return T;//若根结点为p或q或NULL直接返回
	BiTNode* left = SearchAncestor(T->lchild, p, q);//left为左子树中寻找公共祖先
	BiTNode* right = SearchAncestor(T->rchild, p, q);//right为右子树中寻找公共祖先
	if (left && right)return T;//若left和right均不为空则说明最近的祖先是当前的T
	return left ? left : right;//left和right存在空指针则最近公共祖先为不为空的那个结点
}
/*
函数名称：CommonAncestor
函数功能：查找两个关键字所在的结点的最近公共祖先
初始条件：两个结点关键字与一棵已建好的二叉树
操作结果：返回最近公共祖先结点
*/
BiTNode* CommonAncestor(BiTree T, int key1, int key2)
{
	BiTNode* p = LocateNode(T, key1);
	BiTNode* q = LocateNode(T, key2);//先定位两个结点
	if (!p || !q)return NULL;//若有空结点返回空指针
	return SearchAncestor(T, p, q);//两个结点都存在则通过SearchAncestor递归寻找公共祖先
}


/*
函数名称：IsCousins
函数功能：判断两个关键字所代表的结点是否为堂兄弟
初始条件：一棵已建好的二叉树，两个关键字key1,key2
操作结果：若是堂兄弟结点则返回OK，否则返回FALSE
*/
status IsCousins(BiTree T, int key1, int key2)
{
	BiTNode* p = LocateNode(T, key1);
	BiTNode* m = LocateNode(T, key2);//先判断两个结点是否存在
	if (!p || !m)return INFEASIBLE;//若有空结点返回INFEASIBLE
	queue<BiTNode*>q;
	q.push(T);
	int flag = 2;//设置标签
	while (!q.empty())
	{
		int n = q.size();
		for (int i = 0; i < n; i++)
		{
			T = q.front();
			q.pop();
			if (T->lchild && T->rchild && (T->lchild->data.key == key1 && T->rchild->data.key == key2) || (T->lchild->data.key == key2 && T->rchild->data.key == key1))
				return false;//如果为亲兄弟那么返回false
			if (T->lchild) {
				q.push(T->lchild);
				if (T->lchild->data.key == key1 || T->lchild->data.key == key2)flag--;//左孩子存在就入队，如果该结点值是x或y,标记值减一，说明找到一个；
			}
			if (T->rchild) {
				q.push(T->rchild);
				if (T->rchild->data.key == key1 || T->rchild->data.key == key2)flag--;//右孩子存在就入队，如果该结点值是x或y,标记值减一，说明找到一个；
			}
		}
		if (flag == 1)return FALSE;//一层只出现了一个，说明不为堂兄弟，返回FALSE
		if (!flag)return TRUE;//出现两个，返回TRUE
	}
	return FALSE;
}


/*
函数名称：UpdateDepth
函数功能：更新子树的深度的同时更新MaxDistance
*/
int UpdateDepth(BiTree T)
{
	if (T == NULL)return 0;//访问到空结点，返回0
	int L = UpdateDepth(T->lchild);//L为左子树的深度
	int R = UpdateDepth(T->rchild);//R为右子树的深度
	MaxDistance = max(MaxDistance, L + R + 1);//更新MaxDistance
	return max(L, R) + 1;//返回该节点为根的子树的深度
}
/*
函数名称：DiameterOfTree
函数功能：求二叉树的直径，即两个相距最远的点的距离
初始条件：一棵已构建好的二叉树
操作结果：返回二叉树的直径
*/
int DiameterOfTree(BiTree T)
{
	MaxDistance = 1;
	UpdateDepth(T);
	return MaxDistance - 1;//更新完毕后返回深度和-1即为最大距离
}


/*
函数名称：InvertTree
函数功能：翻转二叉树，交换每一个左右孩子结点
初始条件：一棵已建好的二叉树
操作结果：得到翻转后的二叉树
*/
status InvertTree(BiTree T)
{
	if (!T)return OK;//空树直接返回
	BiTNode* tem = T->lchild;
	T->lchild = T->rchild;
	T->rchild = tem;//交换左右结点
	InvertTree(T->lchild);//递归翻转左孩子
	InvertTree(T->rchild);//递归翻转右孩子
	return OK;
}


/*
函数名称：HasPathSum
函数功能：判断是否存在从根节点到叶子结点的路径，使得路径上所有结点关键字和为目标和sum
初始条件：一棵已建好的二叉树，目标和sum
操作结果：若存在这样的一条路径返回TRUE,否则返回FALSE
*/
status HasPathSum(BiTree T, int sum)
{
	if (!T)return FALSE;//空树直接返回FALSE
	if (T->lchild == nullptr && T->rchild == nullptr)return T->data.key == sum;//左右结点均为空指针时直接比较key的值和sum的值
	return HasPathSum(T->lchild, sum - T->data.key) || HasPathSum(T->rchild, sum - T->data.key);//递归判断，左子树和右子树只要有一个满足路径和为sum-T中的key即可
}


/*
函数名称：maxGain
函数功能：递归更新最大路径和MaxNum
*/
int maxGain(BiTree node)
{
	if (!node)return 0;//若node为空，返回贡献为0
	int l = max(maxGain(node->lchild), 0);//当左孩子的贡献大于0时才有资格加入路径
	int r = max(maxGain(node->rchild), 0);//当右孩子的贡献大于0时才有资格加入路径
	int price = node->data.key + l + r;//以当前结点为拐点所能得到的路径和
	MaxNum = (MaxNum > price) ? MaxNum : price;//更新最大路径和MaxNum
	return node->data.key + max(l, r);//每一个结点（不为路径拐点）的最大贡献为左右子树中的最大路径和加上本结点关键字
}
/*
函数名称：MaxPathSum
函数功能：得到树中的最大路径和
初始条件：一棵构建好的树
操作结果：返回树中的最大路径和
*/
int maxPathSum(BiTree T)
{
	maxGain(T);//调用maxGain函数的过程中更新最大路径
	return MaxNum;
}
