#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

//播放音乐头文件
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

#include "head.h"

void showHomePage();	//显示首页
void homePageSound();	//播放音乐
void testSpace();		//检测空格和暂停音乐
void stopSound();		//停止音乐
void showMaps();		//显示地图
void getSnakeRandPosition();	//得到贪吃蛇随机出现的位置
void showSnake();		//把贪吃蛇显示在地图上
void snakeMove();		//贪吃蛇移动
void dropSnake();		//去除残留
void changeDirection();	//改变贪吃蛇的移动方向
bool isSnakeBoom();		//判断蛇死亡
void getFoodRandPosition();		//得到食物随机出现的位置
void snakeGrowUp();		//贪吃蛇吃到食物后变长

int main()
{
	showHomePage();
	homePageSound();
	testSpace();

	getSnakeRandPosition();
	showMaps();

	//游戏界面
	while (1)
	{
		system("cls");
		//食物随机出现位置
		getFoodRandPosition();
		//贪吃蛇吃到食物后体长边长
		snakeGrowUp();
		//改变蛇的方向
		changeDirection();
		//贪吃蛇的死亡判断
		if (false == isSnakeBoom())
		{
			printf("贪吃蛇炸了！！\a\n");
			break;
		}
		//蛇动
		snakeMove();
		//显示背景
		showMaps();
		Sleep(500);//显示蛇的移动速度
	}

	system("pause");
	return 0;
}


void showHomePage()
{
	printf("\n\n\n\n\n");
	printf("\t\t\t\t\t    欢迎来到贪吃蛇的世界 \n\n");
	printf("\t\t\t\t\t     按空格键开始游戏\n");
	printf("\t\t\t\t\t 操作指南：上W 左A 下S 右D 退出游戏Q\n");

}

void homePageSound()
{
	PlaySound(L"f:\\1.wav", NULL, SND_FILENAME | SND_ASYNC);
}

void testSpace()
{
	char ch;
	while (true)
	{
		ch = _getch();
		if (' ' == ch)
		{
			stopSound();
			break;
		}
	}
	printf("\n\n");
	printf("\t\t\t\t\t\t正在进入游戏中...\n");
	Sleep(2500);//2500ms
	system("cls");//清屏
}

void stopSound()
{
	PlaySound(NULL, 0, 0);
}

void showMaps()
{
	for (int i = 0; i<ROWS; i++)
		printf(maps[i]);//打印地图
}

void getSnakeRandPosition()
{
	int rand_x = -1;	//贪吃蛇的随机初始位置(行）
	int rand_y = -1;	//贪吃蛇的随机初始位置(列)
	srand((unsigned int)time(NULL));//随机数种子 uint-消除警告  time(NULL)当前系统时间值
	rand_x = rand() % 24 + 1;
	rand_y = rand() % 25 + 1;

	//贪吃蛇头部
	arr_snake[0][0] = rand_x;
	arr_snake[0][1] = rand_y * 2;
	arr_snake[0][2] = to_west;//方向
							  //贪吃蛇的第一个节点(除了头部)
	arr_snake[1][0] = rand_x;
	arr_snake[1][1] = rand_y * 2 + 2;
	arr_snake[1][2] = to_west;//方向
							  //贪吃蛇的第二个节点
	arr_snake[2][0] = rand_x;
	arr_snake[2][1] = rand_y * 2 + 4;
	arr_snake[2][2] = to_west;//方向

	showSnake();
}

void showSnake()
{
	for (int i = 0; arr_snake[i][0] != 0; i++)
		strncpy(&maps[arr_snake[i][0]][arr_snake[i][1]], "■", 2);
}

void snakeMove()
{
	dropSnake();
	for (int i = SNAKE_LENGTH - 1; i >= 1; i--)
	{
		//过滤非法蛇身
		if (0 == arr_snake[i][0])
			continue;
		//把前一个节点的值赋给后一个节点
		arr_snake[i][0] = arr_snake[i - 1][0];
		arr_snake[i][1] = arr_snake[i - 1][1];
		arr_snake[i][2] = arr_snake[i - 1][2];
	}

	//处理贪吃蛇的蛇头
	arr_snake[0][2] = snakeDirection;
	if (to_west == arr_snake[0][2] || to_east == arr_snake[0][2])
		arr_snake[0][1] += arr_snake[0][2];
	else
		arr_snake[0][0] += arr_snake[0][2];
	showSnake();
}

void dropSnake()
{
	for (int i = 0; arr_snake[i][0] != 0; i++)
		strncpy(&maps[arr_snake[i][0]][arr_snake[i][1]], "  ", 2);
}

void changeDirection()
{
	if (GetAsyncKeyState(VK_UP))//向上
	{
		if (to_south != arr_snake[0][2])
			snakeDirection = to_north;
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		if (to_north != arr_snake[0][2])
			snakeDirection = to_south;
	}
	else if (GetAsyncKeyState(VK_LEFT))
	{
		if (to_east != arr_snake[0][2])
			snakeDirection = to_west;
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		if (to_west != arr_snake[0][2])
			snakeDirection = to_east;
	}
}

bool isSnakeBoom()
{
	//判断贪吃蛇的蛇头是否碰到墙壁或者自爆
	if (to_west == arr_snake[0][2] || to_east == arr_snake[0][2])//东西走向的贪吃蛇
	{
		if (0 == strncmp(&maps[arr_snake[0][0]][arr_snake[0][1] + arr_snake[0][2]], "■", 2))
			return false;
	}
	else
	{
		if (0 == strncmp(&maps[arr_snake[0][0] + arr_snake[0][2]][arr_snake[0][1]], "■", 2))
			return false;
	}
	return true;
}

void getFoodRandPosition()
{
	//判断是否产生新的食物
	if (false == bisFroFood)
	{
		return;
	}
	srand(time(NULL));//随机数种子
	while (true)
	{
		bool bFlag = true;
		rand_Food_x = rand() % 25 + 1;
		rand_Food_y = rand() % 27 + 1;
		for (int i = 0; arr_snake[i][0] != 0; i++)
		{
			if (rand_Food_x == arr_snake[i][0] && rand_Food_y == arr_snake[i][1])
			{
				bFlag = false;
				break;
			}
		}
		if (true == bFlag)
			break;
	}
	strncpy(&maps[rand_Food_x][rand_Food_y * 2], "※", 2);
	bisFroFood = false;//不再产生新的食物
}

void snakeGrowUp()
{
	//如果食物的坐标和贪吃蛇的头部坐标一致，则吃掉食物，体长加1
	if (rand_Food_x == arr_snake[0][0] && rand_Food_y * 2 == arr_snake[0][1])
	{
		if (to_north == arr_snake[snakeLen][2])
		{
			arr_snake[snakeLen + 1][0] = arr_snake[snakeLen][0] + 1;
			arr_snake[snakeLen + 1][1] = arr_snake[snakeLen][0];
			arr_snake[snakeLen + 1][2] = arr_snake[snakeLen][0];
		}
		else if (to_south == arr_snake[snakeLen][2])
		{
			arr_snake[snakeLen + 1][0] = arr_snake[snakeLen][0] - 1;
			arr_snake[snakeLen + 1][1] = arr_snake[snakeLen][0];
			arr_snake[snakeLen + 1][2] = arr_snake[snakeLen][0];
		}
		else if (to_west == arr_snake[snakeLen][2])
		{
			arr_snake[snakeLen + 1][0] = arr_snake[snakeLen][0];
			arr_snake[snakeLen + 1][1] = arr_snake[snakeLen][0] + 2;
			arr_snake[snakeLen + 1][2] = arr_snake[snakeLen][0];
		}
		else if (to_east == arr_snake[snakeLen][2])
		{
			arr_snake[snakeLen + 1][0] = arr_snake[snakeLen][0];
			arr_snake[snakeLen + 1][0] = arr_snake[snakeLen][0] - 2;
			arr_snake[snakeLen + 1][0] = arr_snake[snakeLen][0];
		}
		snakeLen++;//贪吃蛇体长加1
		bisFroFood = true;//让产生食物的开关变量为真，从而产生新的食物
	}
}