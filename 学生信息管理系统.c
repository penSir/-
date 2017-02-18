#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//学生节点
typedef struct _STU
{
	char arrStuNum[10];
	char arrStuName[10];
	int  iStuScore;
	struct _STU* pNext;
} STUNODE;

//声明链表的头和尾
STUNODE* g_pHead = NULL;  //O 
STUNODE* g_pEnd = NULL; 

//添加一个学生的信息
void AddStuMSG(char *arrStuNum, char arrStuName[10], int iStuScore);

//链表头添加一个节点
void AddStuMSGToLinkHead(char *arrStuNum, char arrStuName[10], int iStuScore);

//清空链表
void FreeLinkData();

//打印数据
void ShowStuData();

//显示指令
void ShowOrder();

//查找制定学生
STUNODE* FindStuByNum(char* arrStuNum); //【】

//指定位置插入节点
void InsertNode(STUNODE* pTemp, char *arrStuNum, char arrStuName[10], int iStuScore);

//删除指定学生
void DeleteStuNode(STUNODE* pNode);

//保存信息进文件
void SaveStuToFile();

//读取文件中学生信息
void ReadStuFromFile();


int main(void)
{
	int nOrder = -1; //nOrder iOrder  s db arr p
	                 //初始化
	char arrStuNum[10] = {'\0'};
	char arrStuName[10] = {'\0'};
	int  iStuScore = -1;

	int nFlag = 1;

	STUNODE* pTemp = NULL;
	ShowOrder();

	//读取文件中学生信息
	ReadStuFromFile();

	while(nFlag)
	{
		printf ("请输入指令(10、查看指令):");
		scanf("%d", &nOrder);

		switch (nOrder)
		{
		case 1://尾添加
			//添加一个学生的信息
			printf ("输入学号:");
			scanf ("%s", arrStuNum);
			printf ("输入姓名:");
			scanf ("%s", arrStuName);
			printf ("输入分数:");
			scanf ("%d", &iStuScore);

			AddStuMSG(arrStuNum, arrStuName, iStuScore);
			break;
		case 11: //头添加
			//添加一个学生的信息
			printf ("输入学号:");
			scanf ("%s", arrStuNum);
			printf ("输入姓名:");
			scanf ("%s", arrStuName);
			printf ("输入分数:");
			scanf ("%d", &iStuScore);

			AddStuMSGToLinkHead(arrStuNum, arrStuName, iStuScore);
			break;
		case 111:  //中间添加
			
			printf ("输入指定学号:");
			scanf ("%s", arrStuNum);
			pTemp = FindStuByNum(arrStuNum);
			if (NULL != pTemp)  //200501013  1254
			{
				//TODO：插入
				printf ("输入学号:");
				scanf ("%s", arrStuNum);
				printf ("输入姓名:");
				scanf ("%s", arrStuName);
				printf ("输入分数:");
				scanf ("%d", &iStuScore);

				InsertNode(pTemp, arrStuNum, arrStuName, iStuScore);
			}
			break;
		case 2: //打印指定学生的信息
			//输入一个学号
			printf ("输入指定学号:");
			scanf ("%s", arrStuNum);
			//查找
			pTemp = FindStuByNum(arrStuNum);

			//打印
			if (NULL != pTemp)  //200501013  1254
			{
				printf("学号:%s, 姓名:%s, 分数:%d\n", pTemp->arrStuNum, pTemp->arrStuName, pTemp->iStuScore);
			}

			break;
		case 3:  //修改指定学生的信息
			//输入一个学号
			printf ("输入指定学号:");
			scanf ("%s", arrStuNum);

			//查找
			pTemp = FindStuByNum(arrStuNum);

			//打印
			if (NULL != pTemp)  //200501013  1254
			{
				//修改学好
				printf ("输入学号:");
				scanf("%s", arrStuNum);
				strcpy(pTemp->arrStuNum, arrStuNum);

				//修改名字、
				printf ("输入名字:");
				scanf("%s", arrStuName);
				strcpy(pTemp->arrStuName, arrStuName);

				//修改分数
				printf ("输入分数:");
				scanf("%d", &iStuScore);
				pTemp->iStuScore = iStuScore;
			}
			break;
		case 4:
			//保存学生信息
			SaveStuToFile();
			break;
		case 6:
			//输入一个学号
			printf ("输入要删除的学生学号:");
			scanf ("%s", arrStuNum);

			//查找
			pTemp = FindStuByNum(arrStuNum);

			//删除这个节点
			if (NULL != pTemp)  //200501013  1254
			{
				//调用删除学生的函数
				DeleteStuNode(pTemp);
			}
			break;
		case 7:
			//,释放
			FreeLinkData();
			g_pHead = NULL;
			g_pEnd = NULL;
			//回复 添加节点
			ReadStuFromFile();

			break;
		case 9:
			//显示链表内容
			ShowStuData();
			break;
		case 10:
			//查看指令
			ShowOrder();
			break;
		case 0:
			//退出
			nFlag = 0;
			break;
		default:
			printf("输入的指令不对！\n");
		}
	}
	
	//保存
	SaveStuToFile();
	//释放链表
	FreeLinkData();
	system("pause");
	return 0;
}

//添加一个学生的信息
void AddStuMSG(char *arrStuNum, char arrStuName[10], int  iStuScore) //函数定义
{
	//逻辑
	//创建一个节点
	STUNODE* pTemp = malloc(sizeof (STUNODE));

	//第一步，检验参数的合法性
	if (NULL == arrStuNum || NULL == arrStuName || iStuScore < 0)
	{
		printf ("学生信息输入错误!\n");
		return ;
	}
	//节点成员符初始值
	strcpy(pTemp->arrStuNum, arrStuNum);
	strcpy(pTemp->arrStuName, arrStuName);
	pTemp->iStuScore = iStuScore;
	pTemp->pNext = NULL;

	//接在链表上
	if (NULL == g_pHead || NULL == g_pEnd)
	{
		g_pHead = pTemp;
		//g_pEnd = pTemp;
	}
	else
	{
		g_pEnd->pNext = pTemp;  //链接
		//g_pEnd = pTemp;         //向后移动
	}
	g_pEnd = pTemp;
}


//清空链表
void FreeLinkData()
{
	STUNODE* pTemp = g_pHead;
	while (g_pHead != NULL)
	{
		//记录节点
		pTemp = g_pHead;

		//向后移动了一个
		g_pHead = g_pHead->pNext;

		//删除节点
		free(pTemp);
	}
}

//打印数据
void ShowStuData()
{
	STUNODE* pTemp = g_pHead;
	while (pTemp != NULL)
	{
		printf ("学号:%s, 姓名:%s, 分数:%d\n", pTemp->arrStuNum, pTemp->arrStuName, pTemp->iStuScore);
		//向下走一步
		pTemp = pTemp->pNext;
	}
}

//显示指令
void ShowOrder()
{
	printf("*******************学生信息管理系统*********************\n");
	printf("*******************本系统操作指令如下*******************\n");
	printf("***             1、 增加一个学生信息(尾添加)         ***\n");
	printf("***            11、 增加一个学生信息(头添加)         ***\n");
	printf("***           111、 增加一个学生信息(在指定位置添加) ***\n");
	printf("***             2、 查找指定学生的信息（姓名/学号）  ***\n");
	printf("***             3、 修改指定学生的信息               ***\n");
	printf("***             4、 保存业主的信息到文件中           ***\n");
	printf("***             5、 读取文件中的业主信息             ***\n");
	printf("***             6、 删除指定学生的信息               ***\n");
	printf("***             7、 恢复删除的学生的信息             ***\n");
	printf("***             9、 显示所有学生的信息               ***\n");
	printf("***             0、 退出系统                         ***\n");
	printf("********************************************************\n");
}

//链表头添加一个节点
void AddStuMSGToLinkHead(char *arrStuNum, char arrStuName[10], int iStuScore)
{
	//创建一个节点
	STUNODE* pTemp = malloc(sizeof(STUNODE));

	//检测参数的合法性
	if (NULL == arrStuName || NULL == arrStuName || iStuScore < 0)
	{
		printf ("学生信息输入错误!\n");
		return ;
	}
	
	//c成员赋值
	//节点成员符初始值
	strcpy(pTemp->arrStuNum, arrStuNum);
	strcpy(pTemp->arrStuName, arrStuName);
	pTemp->iStuScore = iStuScore;
	pTemp->pNext = NULL;

	if (NULL == g_pHead || NULL == g_pEnd)
	{
		//链表为空
		//g_pHead = pTemp;
		g_pEnd = pTemp;
	}
	else
	{
		//新节点的下一个 指向头
		pTemp->pNext = g_pHead;
		//头向前挪动一个
		//g_pHead = pTemp;
	}
	g_pHead = pTemp;
}

//查找制定学生
STUNODE* FindStuByNum(char* arrStuNum)  //200501013  1254
{
	STUNODE* pTemp = g_pHead;
	//检测参数的合法性
	if (NULL == arrStuNum)
	{
		printf ("学号输入错误！\n");
		return NULL;
	}
	
	//判断链表是否是空
	if (NULL == g_pHead || NULL == g_pEnd)
	{
		printf ("链表为NULL！\n");
		return NULL;
	}

	//遍历链表	
	while(pTemp != NULL)
	{
		if (0 == strcmp(pTemp->arrStuNum, arrStuNum))
		{
			return pTemp;
		}
		pTemp = pTemp->pNext;
	}

	printf ("查无此节点！\n");
	return NULL;
}

//指定位置插入节点
void InsertNode(STUNODE* pTemp, char *arrStuNum, char arrStuName[10], int iStuScore)
{
	//创建节点
	STUNODE* pNewTemp = malloc(sizeof(STUNODE));
	
	//成员赋值
	strcpy(pNewTemp->arrStuNum, arrStuNum);
	strcpy(pNewTemp->arrStuName, arrStuName);
	pNewTemp->iStuScore = iStuScore;
	pNewTemp->pNext = NULL;    ///

	//插入
	if (pTemp == g_pEnd)  //是尾节点
	{
		g_pEnd->pNext = pNewTemp;
		g_pEnd = pNewTemp;
	}
	else
	{
		//
		pNewTemp->pNext = pTemp->pNext;
		pTemp->pNext = pNewTemp;
	}
}

//删除指定学生
void DeleteStuNode(STUNODE* pNode)
{
	//只有一个节点
	if (g_pHead == g_pEnd)
	{
		free(g_pHead);
		g_pHead = NULL;
		g_pEnd = NULL;
	}
	//只有两个节点
	else if (g_pHead->pNext == g_pEnd)
	{
		if (g_pHead == pNode)
		{
			free(g_pHead);
			g_pHead = g_pEnd;
		}
		else
		{
			free(g_pEnd);
			g_pEnd = g_pHead;
			g_pHead->pNext = NULL;
		}
	}
	else // >=3
	{
		STUNODE* pTemp = g_pHead;
		//判断头
		if(g_pHead == pNode)
		{
			//记住头
			pTemp = g_pHead;
			g_pHead = g_pHead->pNext;
			free(pTemp);
			pTemp = NULL;
			return ;  //结束
		}

		while(pTemp)
		{
			if(pTemp->pNext == pNode)
			{
				//删除
				if (pNode == g_pEnd)
				{
					free(pNode);
					pNode = NULL;
					g_pEnd = pTemp;
					g_pEnd->pNext = NULL;
					return ;
				}
				else
				{
					//记住要删除的节点
					STUNODE* p = pTemp->pNext;
					//链接
					pTemp->pNext = pNode->pNext;
					//释放节点
					free(p);
					p = NULL;
					return ;
				}
			}

			pTemp = pTemp->pNext;
		}
	}
}

//保存信息进文件
void SaveStuToFile()
{
	//判断链表是否是NULL
	FILE* pFile = NULL;
	STUNODE* pTemp = g_pHead;
	char strBuf[30] = {0};
	char strScore[10] = {0};

	if (NULL == g_pHead)
	{
		printf("没有学生\n");
		return ;
	}

	//打开文件
	pFile = fopen("dat.dat", "wb+");
	if (NULL == pFile)
	{
		printf("文件打开失败\n");
		return ;
	}
	//操作文件指针
	while(pTemp)
	{
		//学号赋值进去
		strcpy(strBuf, pTemp->arrStuNum);
		strcat(strBuf, ".");
		//姓名
		strcat(strBuf, pTemp->arrStuName);
		strcat(strBuf, ".");
		//分数
		itoa(pTemp->iStuScore, strScore, 10);
		strcat(strBuf, strScore);

		fwrite(strBuf, 1, strlen(strBuf), pFile); //
		fwrite("\r\n", 1, strlen("\r\n"), pFile);

		pTemp = pTemp->pNext;
	}

	//关闭文件
	fclose(pFile);
}

//读取文件中学生信息
void ReadStuFromFile()
{
	FILE* pFile = fopen("dat.dat", "rb+"); //

	char strBuf[30] = {0};

	char strStuNum[10] = {0};
	char strStuName[10] = {0};
	char strStuScore[10] = {0};

	int nCount = 0;
	int j = 0;

	if (NULL == pFile)
	{
		printf("文件打开失败\n");
		return ;
	}


	//操作指针，读取函数
	while( NULL !=  fgets(strBuf, 30, pFile))  //EOF  feof   3部分
	{
		int i =0;
		nCount = 0;
		j = 0;
		for (i = 0; strBuf[i] != '\r'; i++)
		{
			if(0 == nCount) //没到'.'
			{
				strStuNum[i] = strBuf[i];
				if ('.' == strBuf[i])
				{
					strStuNum[i] = '\0';
					nCount++;
				}
			}
			else if (1 == nCount) //第一个'.'
			{
				strStuName[j] = strBuf[i];
				j++;	
				if ('.' == strBuf[i])
				{
					strStuName[j] = '\0';
					nCount++;
					j = 0;
				}		
			}
			else  //第二个'.' 2 == nCount
			{
				strStuScore[j] = strBuf[i];
				j++;
			}
		}
		//插入到链表
		AddStuMSG(strStuNum, strStuName, atoi(strStuScore));
	}

	fclose(pFile);
}
//释放完空间就将指针赋为空，否则链表易成为野指针
//删除尾节点，尾节点下一个赋空