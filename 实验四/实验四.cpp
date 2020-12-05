/*Author:HUST-CSXJ1901-骆瑞霖*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "memory.h"

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20
#define inf 1000
typedef int status;
typedef int KeyType;
typedef enum { DG, DN, UDG, UDN } GraphKind;
typedef struct {
	KeyType  key;
	char others[20];
} VertexType; //顶点类型定义

//无向无权图
typedef struct ArcNode {         //表结点类型定义
	int adjvex;              //顶点位置编号 
	struct ArcNode* nextarc;	   //下一个表结点指针
} ArcNode;
typedef struct VNode {				//头结点及其数组类型定义
	VertexType data;       	//顶点信息
	ArcNode* firstarc;      	 //指向第一条弧
} VNode, AdjList[MAX_VERTEX_NUM];
typedef  struct {  //邻接表的类型定义
	AdjList vertices;     	 //头结点数组
	int vexnum, arcnum;   	  //顶点数、弧数
	GraphKind  kind;        //图的类型
	char name[20];
} ALGraph;
typedef struct {
	ALGraph G[20];
	int listsize;
}GList;

//有向网
typedef struct {
	int key;//结点的关键字
}DNnode;
typedef struct {
	int start;//边的起点
	int end;//边的终点
	int length;//边的权重
}Edge;
typedef struct {
	int NodeSum = 0;//有向带权图中的结点数目，初始值为0
	int EdgeSum = 0;
	DNnode n[100];//结点数组
	Edge e[500];//边的数组
}Net;

//无向网
typedef struct {
	int key;//结点关键字
}UDNnode;
typedef struct {
	int node1, node2;//边连接的两结点位序
	int length;//边权
}UDNedge;
typedef struct {
	int NodeSum = 0;//结点总数
	int EdgeSum = 0;//边总数
	UDNnode n[100];
	UDNedge e[500];
}UDNet;

//辅助函数
bool CheckKey(VertexType V[], KeyType VR[][2]);
status check(ALGraph& G, KeyType u, VertexType value);
bool CheckDouble(ALGraph& G, VertexType v);
void DFS(ALGraph& G, int i, int vis[], void (*visit)(VertexType));
void visit(VertexType v);
void getPath(ALGraph G, int u, int vis[], int ShortestPath[], int dis);
bool isBipartite(ALGraph G, int i, int color[], int c);
void Sign(ALGraph G, int vis[], int i);


//主要函数
status CreateGraph(ALGraph& G, VertexType V[], KeyType VR[][2]);
status DestroyGraph(ALGraph& G);
int LocateVex(ALGraph G, KeyType u);
status PutVex(ALGraph& G, KeyType u, VertexType value);
int FirstAdjVex(ALGraph G, KeyType u);
int NextAdjVex(ALGraph G, KeyType v, KeyType w);
status InsertVex(ALGraph& G, VertexType v);
status DeleteVex(ALGraph& G, KeyType v);
status InsertArc(ALGraph& G, KeyType v, KeyType w);
status DeleteArc(ALGraph& G, KeyType v, KeyType w);
status DFSTraverse(ALGraph& G, void (*visit)(VertexType));
status BFSTraverse(ALGraph& G, void (*visit)(VertexType));
status SaveGraph(ALGraph G, char FileName[]);
status LoadGraph(ALGraph& G, char FileName[]);
void getShortestPath(ALGraph G, int u, int ShortestPath[]);
bool BipartiteJudge(ALGraph G);
int getComponentNum(ALGraph G);
status CreateDN(Net& net, int DNkey[], int se[][2], int weight[]);
void Dijkstra(Net net, int vertex);
status CreateUDN(UDNet& UDnet, int DNkey[], int se[][2], int weight[]);
int prim(UDNet UDnet);


int main()
{
	VertexType V[30], value;//V用于存储输入，value记录单个结点的内容
	KeyType VR[100][2]; char FileName[20];
	GList Graph;
	Net net;  UDNet UDnet;
	int i; int num = 1;//所操作的图的序号，默认为1
	int u;//用来表示结点的序号
	int v, w;//用来表示单个结点的关键字
	int ShortestPath[100];//记录最短路径的数组
	int mp[100][100];
	//初始化时每一张图的结点数，弧数为0，图的种类为无向图
	int DNkey[100]; //记录有向(无向)带权图的结点的关键字
	int se[500][2];//记录有向边的起点与终点或无向边连接的结点位序
	int weight[500];//记录权值
	int tem;
	for (int i = 0; i < 20; i++)
	{
		Graph.G[i].arcnum = 0;
		Graph.G[i].vexnum = 0;
		Graph.G[i].kind = UDG;
		strcpy(Graph.G[i].name, "GraphExample");
	}
	int op = 1;//op用来输入case
	while (op)
	{
		system("cls");//系统函数，用于清屏
		printf("\n\n");
		printf("\t\t      Menu for Undirected Graph On Graph List \n");
		printf("\t*****************************************************************************\n");
		printf("\t\t\t1.  CreateGraph         2.  DestroyGraph\n");
		printf("\t\t\t3.  LocateVex		4.  PutVex\n");
		printf("\t\t\t5.  FirstAdjVex		6.  NextAdjVex\n");
		printf("\t\t\t7.  InsertNode          8.  DeleteNode\n");
		printf("\t\t\t9.  InsertArc           10.  DeleteArc\n");
		printf("\t\t\t11.  DFSTraverse        12.  BFSTraverse\n");
		printf("\t\t\t13.  SaveGraph          14.  LoadGraph\n");
		printf("\t\t\t15.  PrintGraph		16.  ShortestPath\n");
		printf("\t\t\t17.  BipartiteJudge     18.  getComponentNum\n");
		printf("\t\t\t19.  CreateDN		20.  Dijkstra\n");
		printf("\t\t\t21.  CreateUDN          22.prim\n");
		printf("\t\t\t23.  Choose The Graph\n");
		printf("\t\t\t请选择功能（0-23）选择23以选择在几号图上操作（支持1到20个图的操作）\n");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			printf("请先按顺序输入各个结点的关键字与内容，以-1 nil结束；\n然后输入每一条边所连接的结点关键字，以-1 -1结束\n");
			i = 0;
			do {
				scanf("%d%s", &V[i].key, V[i].others);
			} while (V[i++].key != -1);//将表头结点的关键字和内容输入VertexType类型数组V
			i = 0;
			do {
				scanf("%d%d", &VR[i][0], &VR[i][1]);
			} while (VR[i++][0] != -1);//将每一条弧的两端连接的结点的序号输入KeyType型二维数组VR
			if (CreateGraph(Graph.G[num - 1], V, VR) == ERROR)printf("输入数据有误，创建失败!\n");
			else printf("创建成功!\n");
			getchar(); getchar();
			break;

		case 2:
			if (Graph.G[num - 1].vexnum == 0)
			{
				printf("图中无结点!\n");
				getchar(); getchar();
				break;
			}
			DestroyGraph(Graph.G[num - 1]);
			printf("图销毁成功!\n");
			getchar(); getchar();
			break;

		case 3:
			if (Graph.G[num - 1].vexnum == 0)
			{
				printf("图中无结点!\n");
				getchar(); getchar();
				break;
			}
			printf("请输入要查找的结点的关键字\n");
			scanf("%d", &u);
			i = LocateVex(Graph.G[num - 1], u);
			if (i == -1)printf("查找失败\n");
			else printf("结点为：%d %s\n", Graph.G[num - 1].vertices[i].data.key, Graph.G[num - 1].vertices[i].data.others);
			getchar(); getchar();
			break;

		case 4:
			if (Graph.G[num - 1].vexnum == 0)
			{
				printf("图中无结点!\n");
				getchar(); getchar();
				break;
			}
			printf("请依次输入所要赋值的结点的关键字，新的关键字，新的内容:\n");
			scanf("%d %d %s", &u, &value.key, value.others);
			i = PutVex(Graph.G[num - 1], u, value);
			if (i == OK)printf("赋值成功!\n");
			else if (i == INFEASIBLE)printf("所查找的关键字不存在!\n");
			else printf("赋值后出现关键字重复!\n");
			getchar(); getchar();
			break;

		case 5:
			if (Graph.G[num - 1].vexnum == 0)
			{
				printf("图中无结点!\n");
				getchar(); getchar();
				break;
			}
			printf("请输入所要查找的头结点的关键字:\n");
			scanf("%d", &u);
			i = FirstAdjVex(Graph.G[num - 1], u);
			if (i == -1)printf("查找失败!\n");
			else printf("查找成功！\n第一邻接点为%d %s", Graph.G[num - 1].vertices[i].data.key, Graph.G[num - 1].vertices[i].data.others);
			getchar(); getchar();
			break;

		case 6:
			if (Graph.G[num - 1].vexnum == 0)
			{
				printf("图中无结点!\n");
				getchar(); getchar();
				break;
			}
			printf("请依次输入所要查找的结点，结点中获得下一邻接点的前驱结点关键字:\n");
			scanf("%d %d", &v, &w);
			i = NextAdjVex(Graph.G[num - 1], v, w);
			if (i == -1)printf("无下一邻接顶点");
			else printf("下一邻接顶点为：\n%d %s\n", Graph.G[num - 1].vertices[i].data.key, Graph.G[num - 1].vertices[i].data.others);
			getchar(); getchar();
			break;

		case 7:
			if (Graph.G[num - 1].vexnum == 0)
			{
				printf("图中无结点!\n");
				getchar(); getchar();
				break;
			}
			printf("请输入插入结点的关键字和内容:\n");
			scanf("%d %s", &value.key, value.others);
			i = InsertVex(Graph.G[num - 1], value);
			if (i == -1)printf("插入结点失败!\n");
			else printf("插入成功!\n");
			getchar(); getchar();
			break;

		case 8:
			if (Graph.G[num - 1].vexnum == 0)
			{
				printf("图中无结点!\n");
				getchar(); getchar();
				break;
			}
			printf("请输入所要删除的结点的关键字:\n");
			scanf("%d", &v);
			i = DeleteVex(Graph.G[num - 1], v);
			if (i == -1)printf("删除失败!\n");
			else printf("删除成功!\n");
			getchar(); getchar();
			break;

		case 9:
			if (Graph.G[num - 1].vexnum == 0)
			{
				printf("图中无结点!\n");
				getchar(); getchar();
				break;
			}
			printf("请输入所插入的弧所连接的两个结点的关键字:\n");
			scanf("%d%d", &v, &w);
			i = InsertArc(Graph.G[num - 1], v, w);
			if (i == INFEASIBLE)printf("该弧已存在!\n");
			else if (i == ERROR)printf("所输入的结点有的不存在此图中!\n");
			else printf("插入成功!\n");
			getchar(); getchar();
			break;

		case 10:
			if (Graph.G[num - 1].vexnum == 0)
			{
				printf("图中无结点!\n");
				getchar(); getchar();
				break;
			}
			if (Graph.G[num - 1].arcnum == 0)
			{
				printf("图中无弧!\n");
				getchar(); getchar();
				break;
			}
			printf("请输入要删除的弧所连接的两个结点的关键字:\n");
			scanf("%d%d", &v, &w);
			i = DeleteArc(Graph.G[num - 1], v, w);
			if (i == INFEASIBLE)printf("图中不存在这条弧!\n");
			else if (i == ERROR)printf("输入的结点有的不存在此图中!\n");
			else printf("删除成功!\n");
			getchar(); getchar();
			break;

		case 11:
			if (Graph.G[num - 1].vexnum == 0)
			{
				printf("图中无结点!\n");
				getchar(); getchar();
				break;
			}
			printf("图的深度优先遍历：\n");
			DFSTraverse(Graph.G[num - 1], visit);
			getchar(); getchar();
			break;

		case 12:
			if (Graph.G[num - 1].vexnum == 0)
			{
				printf("图中无结点!\n");
				getchar(); getchar();
				break;
			}
			printf("图的广度优先遍历：\n");
			BFSTraverse(Graph.G[num - 1], visit);
			getchar(); getchar();
			break;

		case 13:
			if (Graph.G[num - 1].vexnum == 0)
			{
				printf("图中无结点!\n");
				getchar(); getchar();
				break;
			}
			SaveGraph(Graph.G[num - 1], Graph.G[num - 1].name);
			printf("文件保存成功!\n");
			getchar(); getchar();
			break;

		case 14:
			LoadGraph(Graph.G[num - 1], Graph.G[num - 1].name);
			printf("文件加载成功!\n");
			getchar(); getchar();
			break;

		case 15:
			if (Graph.G[num - 1].vexnum == 0)
			{
				printf("图中无结点!\n");
				getchar(); getchar();
				break;
			}
			else
			{
				printf("图的邻接表信息如下：\n");
				for (int i = 0; i < Graph.G[num - 1].vexnum; i++)
				{
					ArcNode* p = Graph.G[num - 1].vertices[i].firstarc;
					printf("%d %s", Graph.G[num - 1].vertices[i].data.key, Graph.G[num - 1].vertices[i].data.others);
					while (p)
					{
						printf(" %d", p->adjvex);
						p = p->nextarc;
					}
					printf("\n");
				}
			}
			getchar(); getchar();
			break;

		case 16:
			if (Graph.G[num - 1].vexnum == 0)
			{
				printf("图中无结点!\n");
				getchar(); getchar();
				break;
			}
			for (int i = 0; i < 100; i++)ShortestPath[i] = 100000;
			printf("请输入顶点的位序:");
			scanf("%d", &u);
			if (u < 0 || u >= Graph.G[num - 1].vexnum)printf("不存在该顶点！");
			else
			{
				getShortestPath(Graph.G[num - 1], u, ShortestPath);
				for (int i = 0; i < Graph.G[num - 1].vexnum; i++)
				{
					if (i == u)continue;
					if (ShortestPath[i] == 100000)printf("%d号结点与%d号结点间无通路\n", i, u);
					else printf("%d号结点与%d号结点间的最短路长为%d\n", i, u, ShortestPath[i]);
				}
			}
			getchar(); getchar();
			break;

		case 17:
			if (Graph.G[num - 1].vexnum == 0)
			{
				printf("图中无结点!\n");
				getchar(); getchar();
				break;
			}
			if (BipartiteJudge(Graph.G[num - 1]) == true)printf("是二分图!");
			else printf("不是二分图!");
			getchar(); getchar();
			break;


		case 18:
			if (Graph.G[num - 1].vexnum == 0)
			{
				printf("图中无结点!\n");
				getchar(); getchar();
				break;
			}
			printf("该图有%d个连通分量.", getComponentNum(Graph.G[num - 1]));
			getchar(); getchar();
			break;

		case 19:
			printf("请先输入有向带权图的所有顶点的关键字，以-1为结束，然后输入所有的边，\n一条边用三个数字表示，分别为起点位序，终点位序，边的权重,以-1，-1，-1结束\n");
			i = 0;
			do {
				scanf("%d", &DNkey[i]);
			} while (DNkey[i++] != -1);
			i = 0;
			do {
				scanf("%d %d %d", &se[i][0], &se[i][1], &weight[i]);
			} while (se[i++][0] != -1);
			CreateDN(net, DNkey, se, weight);
			printf("有向无权图创建成功!\n");
			printf("按顺序结点关键字为:");
			for (i = 0; i < net.NodeSum; i++)printf("%d ", net.n[i].key); printf("\n");
			printf("图的所有边为:\n");
			for (int i = 0; i < net.EdgeSum; i++)printf("%d->%d(权:%d) ", net.e[i].start, net.e[i].end, net.e[i].length);
			printf("\n");
			getchar(); getchar();
			break;

		case 20:
			printf("请选择最短路径的源点:\n");
			scanf("%d", &v);
			if (net.NodeSum == 0 || net.EdgeSum == 0) {
				printf("图中无结点或边!");
				getchar(); getchar();
				break;
			}
			Dijkstra(net, v);
			getchar(); getchar();
			break;

		case 21:
			printf("请先输入无向带权图的所有顶点的关键字，以-1为结束，然后输入所有的边，\n一条边用三个数字表示，分别为连接的两点的输入位序，边的权重,以-1，-1，-1结束\n");
			i = 0;
			do {
				scanf("%d", &DNkey[i]);
			} while (DNkey[i++] != -1);
			i = 0;
			do {
				scanf("%d %d %d", &se[i][0], &se[i][1], &weight[i]);
			} while (se[i++][0] != -1);
			CreateUDN(UDnet, DNkey, se, weight);
			printf("无向网创建成功!\n");
			printf("按顺序结点关键字为:");
			for (i = 0; i < UDnet.NodeSum; i++)printf("%d ", UDnet.n[i].key); printf("\n");
			printf("图的所有边为:\n");
			for (int i = 0; i < UDnet.EdgeSum; i++)printf("%d-%d(权:%d) ", UDnet.e[i].node1, UDnet.e[i].node2, UDnet.e[i].length);
			printf("\n");
			getchar(); getchar();
			break;

		case 22:
			if (UDnet.EdgeSum == 0 || UDnet.NodeSum == 0) {
				printf("图无结点或无边!");
				getchar(); getchar();
				break;
			}
			printf("无向网的最小生成树的总权值为%d", prim(UDnet));
			getchar(); getchar();
			break;

		case 23:
			printf("在第几个图操作支持20个图进行操作: \n");
			scanf("%d", &num);
			printf("请输入这个图的文件名:\n");
			scanf("%s", Graph.G[num - 1].name);
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
函数名称：CheckKey
函数功能：检查输入参数生成图时是否有关键字重复的情况，以及输入结点是否超过图的结点上限，以及输入的弧集中是否有不存在的关键字；
是则返回false生成失败，否则返回true在CreateGraph中完成生成
*/
bool CheckKey(VertexType V[], KeyType VR[][2])
{
	int sum[100] = { 0 };//初始化记录关键字出现次数数组sum，每一个元素为0
	for (int i = 0; V[i].key != -1; i++)
	{
		sum[V[i].key]++;//关键字出现次数+1
		if (sum[V[i].key] > 1)return false;//关键字重复，返回false
	}
	int s = 0;//记录结点个数
	for (int i = 0; i < 100; i++)
		if (sum[i])s++;
	if (s > 20)return false;//超过上限，返回false
	for (int i = 0; VR[i][0] != -1; i++)
	{
		if (!sum[VR[i][0]] || !sum[VR[i][1]])return false;//有图中没出现过的关键字，返回false
	}
	return true;
}
/*
函数名称：CreateGraph
函数功能：根据V和VR构造图T
初始条件：记录了结点关键字的数组,记录了相连结点关键字对的二维数组
操作结果：根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR如果有相同的关键字，返回ERROR。
*/
status CreateGraph(ALGraph& G, VertexType V[], KeyType VR[][2])
{
	if (CheckKey(V, VR) == false)return ERROR;//生成失败
	int i = 0, j, one, two;//one,two用于记录每一对连接的结点的下标
	VertexType e;
	do {
		G.vertices[i].data = V[i];
		G.vertices[i].firstarc = NULL;
	} while (V[i++].key != -1);//V数组记录的顶点的关键字，初始时每一个表头结点的firstarc指针域均赋值为空
	G.vexnum = i - 1;//顶点个数
	i = 0;
	while (VR[i][0] != -1) {
		ArcNode* p;
		for (j = 0; j < G.vexnum; j++)
			if (VR[i][0] == G.vertices[j].data.key)
			{
				one = j; break;//遇到结点关键字为两个相连结点其一，记录下标
			}
		for (j = 0; j < G.vexnum; j++)
			if (VR[i][1] == G.vertices[j].data.key)
			{
				two = j; break;
			}//one two记录的是弧连接的两个结点在头结点中的序号
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = two; p->nextarc = G.vertices[one].firstarc; G.vertices[one].firstarc = p;//将新的结点插入头结点后面的相邻结点链表中（首插法）
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = one; p->nextarc = G.vertices[two].firstarc; G.vertices[two].firstarc = p;
		i++;
	}
	G.arcnum = i - 1;//弧的数目
	return OK;
}


/*
函数名称：DestroyGraph
函数功能：销毁无向图
初始条件：一个已创建的无向图
操作结果：清空ALGraph类型G的所有空间
*/
status DestroyGraph(ALGraph& G)
{
	ArcNode* tem;
	for (int i = 0; i < G.vexnum; i++)
	{
		ArcNode* p = G.vertices[i].firstarc;//ArcNode*型的指针指向每一个首结点的firstarc指针域
		while (p->nextarc)
		{
			tem = p->nextarc;//有后继结点时记录
			free(p);//删除当前指向结点
			p = tem;//后移
		}
		free(p);//删除最后一个
	}
	G.vexnum = 0; G.arcnum = 0;//空图的顶点个数，弧个数为0
	return OK;
}


/*
函数名称：LocateVex
函数功能：查找关键字u所在图中的结点位序
初始条件：一个已构建的图，查找关键字
操作结果：找到该关键字返回下标，否则返回-1
*/
int LocateVex(ALGraph G, KeyType u)
{
	//遍历所有头结点，当有结点的数据域关键字等于u，返回下标i
	for (int i = 0; i < G.vexnum; i++)
		if (G.vertices[i].data.key == u)
			return i;
	return -1;//未返回下标则表明查找失败，返回-1
}


/*
函数名称：check
函数功能：检查赋值操作后是否会出现关键字重复或者所要赋值的结点不存在的情况
*/
status check(ALGraph& G, KeyType u, VertexType value)
{
	int sum[100] = { 0 }; int tag = 0;//sun用于记录关键字出现次数，tag用于判断情况
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.vertices[i].data.key == u)
		{
			tag = 1;//查找成功
			sum[value.key]++;//由于目标关键字会被替换，所以是value中的key的出现次数增加
			if (sum[value.key] > 1)return FALSE;//超过1，则说明出现关键字重复，返回FALSE
		}
		else {
			sum[G.vertices[i].data.key]++;//不相等，直接出险次数增加
			if (sum[G.vertices[i].data.key] > 1)return FALSE;//次数大于1返回FALSE
		}
	}
	if (!tag)return INFEASIBLE;//未能找到目标关键字，返回INFEASIBLE
	return TRUE;
}
/*
函数名称：PutVex
函数功能：根据u在图G中查找顶点，查找成功将该顶点值修改成value
初始条件：一个已建好的图，所查找的关键字，用来替换的VertexType类型value
操作结果：对不正确的情况返回错误信息，否则将所查找到的结点数据域修改完毕返回OK
*/
status PutVex(ALGraph& G, KeyType u, VertexType value)
{
	int tag = check(G, u, value);//调用检查函数
	if (tag == INFEASIBLE)return INFEASIBLE;//检查返回INFEASIBLE，则返回INFEASIBLE
	else if (tag == ERROR)return ERROR;//检查返回ERROR,返回ERROR
	//检查通过
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.vertices[i].data.key == u)
		{
			G.vertices[i].data = value;//关键字为u，修改数据域为value
		}
	}
	return OK;
}


/*
函数名称：FirstAdjVex
函数功能：根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序
初始条件：一个已构建的图G，所要查找的关键字
操作结果：查找成功返回顶点u的第一邻接点的位序，否则返回-1
*/
int FirstAdjVex(ALGraph G, KeyType u)
{
	//for循环遍头结点vertices数组，当找到关键字等于u的结点时，判断它的firstarc指针域是否为空，为空则返回-1否则返回它指向的adjvex大小
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.vertices[i].data.key == u)
			return G.vertices[i].firstarc ? G.vertices[i].firstarc->adjvex : -1;
	}
	return -1;//关键字在图中不存在，返回-1
}


/*
函数名称：NextAdjVex
函数功能：查找结点的相对某一关键字的下一个位序
初始条件：一个已建好的图，所查找的关键字，前驱结点的关键字
操作结果：查找成功返回顶点v的邻接顶点相对于w的下一邻接顶点的位序，否则返回-1
*/
int NextAdjVex(ALGraph G, KeyType v, KeyType w)
{
	//遍历每一个首结点
	for (int i = 0; i < G.vexnum; i++)
	{
		//找到与v相等的关键字所在结点
		if (G.vertices[i].data.key == v)
		{
			ArcNode* p = G.vertices[i].firstarc;//p指向所查找首结点的firstarc域
			while (G.vertices[p->adjvex].data.key != w && p->nextarc)
				p = p->nextarc;//查找w的前驱
			if (G.vertices[p->adjvex].data.key == w && p->nextarc)return p->nextarc->adjvex;//查找到w所在结点并且下一个指针域非空，返回下一个结点的adjvex
			else return -1;//在目标首结点的后继邻接链表中未找到w或w没有后继，返回-1
		}
	}
	return -1;//未找到与v相等的关键字,返回-1
}


/*
函数名称：CheckDouble
函数功能：检查元素是否超限，以及插入结点时是否会出现关键字重复
*/
bool CheckDouble(ALGraph& G, VertexType v)
{
	if (G.vexnum >= 20)return false;//超过上限
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.vertices[i].data.key == v.key)return false;//出现关键字重复返回false
	}
	return true;
}
/*
函数名称：InsertVex
函数功能：在图中插入一个新的结点
初始条件：一个已建好的图，新的结点VertexType类型的变量
操作结果：在图G中插入顶点v，成功返回OK,否则返回ERROR
*/
status InsertVex(ALGraph& G, VertexType v)
{
	if (!CheckDouble(G, v))return ERROR;
	G.vertices[G.vexnum].data = v;//最后一个位置加入v
	G.vertices[G.vexnum].firstarc = NULL;//初始时后继为空
	G.vexnum++;//顶点数增加1
	return OK;
}


/*
函数名称：DeleteVex
函数功能：删除一个结点
初始条件：一个已建好的图，待删除的结点的关键字
操作结果：在图G中删除关键字v对应的顶点以及相关的弧，头结点数组中位于该结点后的结点的下标-1，成功返回OK,否则返回ERROR
*/
status DeleteVex(ALGraph& G, KeyType v)
{
	if (G.vexnum == 1 && v == G.vertices[0].data.key)return ERROR;//删除后为空图
	int x = -1, i;
	for (i = 0; i < G.vexnum; i++)
	{
		if (G.vertices[i].data.key == v)
		{
			x = i;//定位到待删除结点
			for (int j = i; j < G.vexnum - 1; j++)
				G.vertices[j] = G.vertices[j + 1];//后序结点的下标-1
			G.vexnum--;//结点总数减少1个
			break;
		}
	}
	if (x == -1)return ERROR;//未找到待删除的结点，返回ERROR
	for (int j = 0; j < G.vexnum; j++)
	{
		ArcNode* p = G.vertices[j].firstarc;//定义ArcNode型的指针指向每一层结点的firstarc
		if (!p)continue;
		//只有一个相邻结点
		if (p->nextarc == NULL)
		{
			if (p->adjvex == x) {
				free(p);
				G.vertices[j].firstarc = NULL;//直接删除
			}
			else
			{
				if (p->adjvex > x)p->adjvex -= 1;//位于结点后的，位序减1
			}
		}
		//有多个相邻结点
		else
		{
			//第一个就是待删除结点，firstarc指针指向下一个结点
			if (p->adjvex == x) {
				G.vertices[j].firstarc = p->nextarc;
				free(p);
			}
			else
			{
				while (p->nextarc)
				{
					if (p->nextarc->adjvex == x)
					{
						ArcNode* tem = p->nextarc;//定位待删除结点
						p->nextarc = tem->nextarc;//调整后继
						free(tem);//释放空间
						break;
					}
					else p = p->nextarc;
				}
			}
			if (G.vertices[j].firstarc)
			{
				ArcNode* q = G.vertices[j].firstarc;
				//对位序大于删除的结点的结点，位序减1
				while (q)
				{
					if (q->adjvex > x)q->adjvex -= 1;
					q = q->nextarc;
				}
			}
		}
	}
	return OK;
}


/*
函数名称：InsertArc
函数功能：在图中插入弧
初始条件：一个已建好的图，待插入的弧两端结点关键字
操作结果：在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
*/
status InsertArc(ALGraph& G, KeyType v, KeyType w)
{
	int x1 = -1, x2 = -1;
	//定位待插入弧两端结点的下标
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.vertices[i].data.key == v)x1 = i;
		if (G.vertices[i].data.key == w)x2 = i;
	}
	if (x1 == -1 || x2 == -1)return ERROR;//有结点未找到则返回ERROR
	ArcNode* p = G.vertices[x1].firstarc; ArcNode* q = G.vertices[x2].firstarc;//ArcNode型的指针分别指向两个结点的首个指针域
	int tag = 0;
	while (p)
	{
		if (p->adjvex == x2)return INFEASIBLE;//弧已存在
		p = p->nextarc;
	}
	p = G.vertices[x1].firstarc;
	ArcNode* tem1 = (ArcNode*)malloc(sizeof(ArcNode));//为新结点申请空间
	tem1->adjvex = x2;//结点赋值
	tem1->nextarc = p;
	G.vertices[x1].firstarc = tem1;//链表首结点指向位置修改
	ArcNode* tem2 = (ArcNode*)malloc(sizeof(ArcNode));
	tem2->adjvex = x1;
	tem2->nextarc = q;
	G.vertices[x2].firstarc = tem2;
	G.arcnum++;//G的弧数增加1
	return OK;
}


/*
函数名称：DeleteArc
函数功能：删除图中的一个弧
初始条件：一个已建好的图，待删除的弧的两端结点的关键字
操作结果：在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
*/
status DeleteArc(ALGraph& G, KeyType v, KeyType w)
{
	int x1 = -1, x2 = -1;
	//定位弧两端连接的结点
	for (int i = 0; i < G.vexnum; i++)
	{
		if (G.vertices[i].data.key == v)x1 = i;
		if (G.vertices[i].data.key == w)x2 = i;
	}
	if (x1 == -1 || x2 == -1)return ERROR;//有结点不存在则返回ERROR
	ArcNode* p = G.vertices[x1].firstarc;
	int tag = 0;
	while (p)
	{
		if (p->adjvex == x2) {
			tag = 1;//tag为1说明找到弧
			break;
		}
		else p = p->nextarc;
	}
	if (!tag)return INFEASIBLE;//未找到弧，返回INFEASIBLE
	p = G.vertices[x1].firstarc;//p指向待删除弧的端点的首个指针域
	//仅一个结点，直接删除
	if (p->nextarc == NULL) {
		free(p);
		G.vertices[x1].firstarc = NULL;
	}
	//多个结点，找到后删除
	else
	{
		while (p->nextarc)
		{
			if (p->nextarc->adjvex == x2)
			{
				ArcNode* tem = p->nextarc;
				p->nextarc = tem->nextarc;
				free(tem);
			}
		}
	}
	//与x1相同
	ArcNode* q = G.vertices[x2].firstarc;
	if (q->nextarc == NULL) {
		free(q);
		G.vertices[x2].firstarc = NULL;
	}
	else
	{
		while (q->nextarc)
		{
			if (q->nextarc->adjvex == x1)
			{
				ArcNode* tem = q->nextarc;
				q->nextarc = tem->nextarc;
				free(tem);
			}
		}
	}
	G.arcnum--;//删除后图G的弧总数减少1
	return OK;
}


/*
函数名称：visit
函数功能：访问一个结点，输出它的数据域和others
*/
void visit(VertexType v)
{
	printf(" %d %s", v.key, v.others);
}


/*
函数名称：DFS
函数功能：深度优先搜索得到结点序列
*/
void DFS(ALGraph& G, int i, int vis[], void (*visit)(VertexType))
{
	if (!vis[i]) {
		visit(G.vertices[i].data);//访问结点
		vis[i] = 1;//访问后vis置为1
		ArcNode* p = G.vertices[i].firstarc;//p指向结点i的首个结点域
		while (p)
		{
			DFS(G, p->adjvex, vis, visit);//深度优先搜索，则在后继链表中每搜索一个结点，则进入该结点的下一层遍历
			p = p->nextarc;//前一个结点深度搜索完毕后再进入下一个结点
		}
	}
	return;
}
/*
函数名称：DFSTraverse
函数功能：搭配visit输出图的深度优先遍历
初始条件：一个已建好的图
操作结果：输出深度优先搜索遍历的序列
*/
status DFSTraverse(ALGraph& G, void (*visit)(VertexType))
{
	int vis[100] = { 0 };//vis记录访问结果，0表示第i个结点尚未被访问
	DFS(G, 0, vis, visit);//使用DFS函数深层调用自身输出序列
	return OK;
}


/*
函数名称：BFSTraverse
函数功能：对图G进行广度优先遍历
初始条件：一个已建好的图
操作结果：输出图的广度优先遍历序列
*/
status BFSTraverse(ALGraph& G, void (*visit)(VertexType))
{
	int vis[100] = { 0 };//vis记录访问结果
	int a[100];//a用于模拟队列
	int left = 0, right = 0;//新的结点从右侧加入，访问左边的结点后left右移
	a[0] = 0; right++;//第一个结点入队
	while (left < right)
	{
		if (vis[a[left]] == 0) {
			visit(G.vertices[a[left]].data);//访问结点
			vis[a[left]] = 1;//访问的结点下标对应vis的值置为1
			ArcNode* p = G.vertices[a[left]].firstarc;//定义ArcNode型指针指向该结点的首个指针域
			left++;//访问一个结点left++
			while (p)
			{
				if (vis[p->adjvex] == 0) {
					a[right] = p->adjvex;
					right++;//该结点的邻接结点中未被访问的入队，right右移
				}
				p = p->nextarc;
			}
		}
		else left++;
	}
	return OK;
}


/*
函数名称：SaveGraph
函数功能：将图的数据写入到文件中
初始条件：一个已建好的图
操作结果：将图的结点关键字，others和弧的内容记录在文件中
*/
status SaveGraph(ALGraph G, char FileName[])
{
	FILE* fp; fp = fopen(FileName, "w+");//定义文件指针
	fprintf(fp, "%d ", G.vexnum);//先写入图G的结点数目
	for (int i = 0; i < G.vexnum; i++)
	{
		fprintf(fp, "%d %s ", G.vertices[i].data.key, G.vertices[i].data.others);//写入每一个结点的关键字和others
		ArcNode* p = G.vertices[i].firstarc;
		//写入以当前结点为头结点的后继链表中的所有邻接结点的位序
		while (p)
		{
			fprintf(fp, "%d ", p->adjvex);
			p = p->nextarc;
		}
		fprintf(fp, "%d ", -1);//以-1作为一个结点的邻接结点链表的结束
	}
	fclose(fp);
	return OK;
}


/*
函数名称：LoadGraph
函数功能：利用文件中的内容构建一个图
初始条件：记录了图的邻接表信息的文件
操作结果：利用文件中的信息构建图G的邻接表
*/
status LoadGraph(ALGraph& G, char FileName[])
{
	FILE* fp; fp = fopen(FileName, "r+");//定义文件指针
	int len, tem;
	fscanf(fp, "%d", &len);//首先读入结点的数目
	G.vexnum = len;
	for (int i = 0; i < len; i++)
	{
		fscanf(fp, "%d%s", &G.vertices[i].data.key, G.vertices[i].data.others);//写入每一个结点的关键字和others
		fscanf(fp, "%d", &tem);//tem记录每一个结点邻接的结点的位序
		if (tem == -1) {
			G.vertices[i].firstarc = NULL;//tem为-1时代表这个结点没有邻接结点
			continue;
		}
		else
		{
			ArcNode* p = G.vertices[i].firstarc;
			p = (ArcNode*)malloc(sizeof(ArcNode));//为新结点申请空间
			p->adjvex = tem; p->nextarc = NULL;//赋值
			fscanf(fp, "%d", &tem);//再读入tem
			//tem不为-1时进行首插法插入结点循环
			while (tem != -1)
			{
				p->nextarc = (ArcNode*)malloc(sizeof(ArcNode));//申请空间
				p = p->nextarc;//后移
				p->adjvex = tem; p->nextarc = NULL;
				fscanf(fp, "%d", &tem);
			}
		}
	}
	fclose(fp);
	return OK;
}


/*
函数名称：getPath
函数功能：通过深度优先搜索得到每一个结点离所给定结点的最短路径
*/
void getPath(ALGraph G, int u, int vis[], int ShortestPath[], int dis)
{
	if (dis < ShortestPath[u])ShortestPath[u] = dis;//更新ShortestPath[u]
	if (!vis[u]) {
		vis[u] = 1;//访问结点后vis置为1
		ArcNode* p = G.vertices[u].firstarc;
		while (p)
		{
			getPath(G, p->adjvex, vis, ShortestPath, dis + 1);//进入下一层，路径大小dis+1
			p = p->nextarc;
		}
	}
	else return;
}
/*
函数名称：getShortestPath
函数功能：得到其他所有结点到目标结点的最短路径
初始条件：一个已建好的图，源结点，记录路径大小数组
操作结果：修改ShortestPath数组，得到各个结点对应的最小路径
*/
void getShortestPath(ALGraph G, int u, int ShortestPath[])
{
	int vis[100];//vis记录结点的访问情况
	for (int i = 0; i < 100; i++)vis[i] = 0;//初始化为0，表示未被访问过
	getPath(G, u, vis, ShortestPath, 0);//调用getPath函数，初始时当前结点u到自己的路径vis为0
}


/*
函数名称：isBipartite
函数功能：递归调用，判断无向图是否为二分图
*/
bool isBipartite(ALGraph G, int i, int color[], int c)
{
	int next = (c == 1) ? 0 : 1;//next是位序为i的结点的邻接结点应该上的色
	if (color[i] != -1 && color[i] != c)return false;//若该点已上色且不为应上的色c返回false
	if (color[i] == -1) {
		color[i] = c;//未上色则上色为c
		ArcNode* p = G.vertices[i].firstarc;
		while (p) {
			if (!isBipartite(G, p->adjvex, color, next))return false;//一旦邻接点中有不符合条件的色，返回false
			p = p->nextarc;//p后移
		}
		return true;//调用深层完毕不返回false说明当前点与邻接点均不同色
	}
	else return true;//已上色且与c相等，符合条件，返回true
}
bool BipartiteJudge(ALGraph G)
{
	int color[100];//color记录每一个结点所上的色，只有0和1两种
	for (int i = 0; i < G.vexnum; i++)color[i] = -1;//初始化为-1表示未上色状态
	return isBipartite(G, 0, color, 0);//递归调用isBipartite进行判断
}


/*
函数名称：Sign
函数功能：进行DFS给结点i为起点的所有有通路到达的结点打上访问标记
*/
void Sign(ALGraph G, int vis[], int i)
{
	vis[i] = 1;//访问标记
	ArcNode* p = G.vertices[i].firstarc;
	while (p)
	{
		if (!vis[p->adjvex])Sign(G, vis, p->adjvex);//未访问则进一步DFS
		p = p->nextarc;//p后移
	}
}
/*
函数名称：getComponentNum
函数功能：得到无向图的连通分量数
初始条件：一个已建好的图
操作结果：返回连通分量数
*/
int getComponentNum(ALGraph G)
{
	int i, count = 0;//i记录当前结点位序
	int vis[100]; for (int i = 0; i < G.vexnum; i++)vis[i] = 0;//初始化所有结点均未访问
	for (int i = 0; i < G.vexnum; i++) {
		if (!vis[i]) {
			count++;//未访问，连通分量加1
			Sign(G, vis, i);//给所有与结点i相连的结点做标记
		}
	}
	return count;//返回数量
}


/*
函数名称：CreateDN
函数功能：创建一个有向带权图
初始条件：Net型变量，记录结点关键字的数组，记录边与权重的数组
操作结果：得到一个有向网net
*/
status CreateDN(Net& net, int DNkey[], int se[][2], int weight[])
{
	int i = 0;
	for (;; i++)
	{
		if (DNkey[i] != -1)
			net.n[i].key = DNkey[i];//将结点关键字写入有向网
		else break;
	}
	net.n[i].key = -1;
	net.NodeSum = i;//有向网中的结点数目
	for (i = 0;; i++)
	{
		if (weight[i] != -1)
		{
			net.e[i].start = se[i][0];
			net.e[i].end = se[i][1];
			net.e[i].length = weight[i];//写入有向网的边的起点，终点，边权
		}
		else break;
	}
	net.e[i].start = net.e[i].end = net.e[i].length = -1;
	net.EdgeSum = i;//有向网的边数
	return OK;
}


/*
函数名称：Dijkstra
函数功能：对于给定的源点，使用Dijkstra算法得到源点到其他结点的最短路径
初始条件：一个已建好的有向网
操作结果：返回所有顶点到源点的最短路径，没有有向通路也会进行说明
*/
void Dijkstra(Net net, int vertex)
{
	int adjacent[100][100];//邻接矩阵
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)adjacent[i][j] = inf;
	for (int i = 0; i < net.EdgeSum; i++)
		adjacent[net.e[i].start][net.e[i].end] = net.e[i].length;
	int count = 0; //用于记录访问过的结点数目,后面用于控制循环
	bool find[100]; //用于标记已经找到最短路径的结点
	int pre[100]; //用于存放当前结点的前驱结点的最短路径
	int distance[100]; //用于存放当前结点的最短路径
	for (int i = 0; i < net.NodeSum; i++)
		pre[i] = vertex; //开始所有结点的前驱结点都是开始的vertex
	for (int i = 0; i < net.NodeSum; i++)
		distance[i] = adjacent[vertex][i]; //邻接矩阵中存放的权值就是距离
	for (int i = 0; i < net.NodeSum; i++)
		find[i] = false; //初始化所有结点都没有找到最短路径
	find[vertex] = true;
	distance[vertex] = 0;//vertex到自身的距离为0

	int v = vertex; //用来迭代顶点的变量
	int d; //用来表示距离
	while (count < net.NodeSum)
	{
		d = inf;
		for (int i = 0; i < net.NodeSum; i++) //找到离最初结点最短路径的一个未访问到的结点
		{
			if (!find[i] && distance[i] < d)
			{
				d = distance[i];
				v = i;
			}
		}
		find[v] = true;
		//更新剩余的结点的前驱和最短距离
		for (int i = 0; i < net.NodeSum; i++)
		{
			if (!find[i])
			{
				/*将上面找到的最短路径的结点作为起始点，
				*连到其他未访问过的结点上，
				*当比从最初结点到这个结点的路径短的时候，
				*就将上个结点作为前驱结点，更新一下即可*/
				d = distance[v] + adjacent[v][i];
				if (d < distance[i])
				{
					pre[i] = v;
					distance[i] = d;
				}
			}
		}
		count++;
	}
	for (int i = 0; i < net.NodeSum; i++)
	{
		if (distance[i] != inf)printf("源点到关键字为%d的点的最短路径长为%d\n", net.n[i].key, distance[i]);
		else printf("源点和关键字为%d的结点之间没有有向通路\n", net.n[i].key);
	}

}


/*
函数名称：CreateUDN
函数功能：依据结点和边的数组构建一个无向网UDnet
初始条件：存储结点关键字和边的信息的数组
操作结果；得到一个UDNet类型的无向网UDnet
*/
status CreateUDN(UDNet& UDnet, int DNkey[], int se[][2], int weight[])
{
	int i = 0;
	for (;; i++)
	{
		if (DNkey[i] != -1)
			UDnet.n[i].key = DNkey[i];//将结点关键字写入无向网
		else break;
	}
	UDnet.n[i].key = -1;
	UDnet.NodeSum = i;//无向网中的结点数目
	for (i = 0;; i++)
	{
		if (weight[i] != -1)
		{
			UDnet.e[i].node1 = se[i][0];
			UDnet.e[i].node2 = se[i][1];
			UDnet.e[i].length = weight[i];//写入无向网的边的起点，终点，边权
		}
		else break;
	}
	UDnet.e[i].node1 = UDnet.e[i].node2 = UDnet.e[i].length = -1;
	UDnet.EdgeSum = i;//无向网的边数
	return OK;
}


int prim(UDNet UDnet)
{
	int m[100][100]; int vis[100] = { 0 }; int low[100] = { 0 };//m为邻接矩阵，vis数组存储访问信息，low存储最短路径大小
	for (int i = 0; i < 100; i++)for (int j = 0; j < 100; j++)m[i][j] = 10000;//邻接矩阵初始化时点间距离为最大，这里极限取10000
	for (int i = 0; i < UDnet.EdgeSum; i++)
	{
		m[UDnet.e[i].node1][UDnet.e[i].node2] = m[UDnet.e[i].node2][UDnet.e[i].node1] = UDnet.e[i].length;//记录结点间距离
	}
	vis[0] = 1;//以0号结点为起始点，vis赋值为1
	int sum = 0;
	int pos, minn;
	pos = 0;//以0号结点为基准
	for (int i = 0; i < UDnet.NodeSum; i++)
	{
		low[i] = m[pos][i];//更新每一个结点的最短路径大小为到0号结点的距离
	}
	/*
	先把第一个点放到树里，然后找到剩下的点到这个点的距离
	*/
	for (int i = 1; i < UDnet.NodeSum; i++)//循环遍历 n-1 次数，把点全部加入
	{
		minn = 10000;
		for (int j = 0; j < UDnet.NodeSum; j++)
		{
			if (!vis[j] && minn > low[j]) //没有进树的节点，并且这个节点到树里面 点距离最近，拉进来
			{
				minn = low[j];
				pos = j;
			}
		}
		sum += minn;//更新总权值sum
		vis[pos] = 1;//访问后vis置为1
		/*
		新进入的点作为基准，去更新其他点的low值
		*/
		for (int j = 0; j < UDnet.NodeSum; j++)
		{
			if (!vis[j] && low[j] > m[pos][j])
			{
				low[j] = m[pos][j];//取较小者
			}
		}
	}
	return sum;
}
