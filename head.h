#define true 1
#define false 0
#define ROWS 28
#define COLS 60
#define SNAKE_LENGTH 20	//贪吃蛇长度
typedef int bool;

//地图
char maps[ROWS][COLS]=
{
	"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n",
	"■                                                      ■\n",
	"■                                                      ■\n",
	"■                                                      ■\n",
	"■                                                      ■\n",
	"■                                                      ■\n",
	"■                                                      ■\n",
	"■                                                      ■\n",
	"■                                                      ■\n",
	"■                                                      ■\n",
	"■                                                      ■\n",
	"■                                                      ■\n",
	"■                                                      ■\n",
	"■                                                      ■\n",
	"■                                                      ■\n",
	"■                                                      ■\n",
	"■                                                      ■\n",
	"■                                                      ■\n",
	"■                                                      ■\n",
	"■                                                      ■\n",
	"■                                                      ■\n",     
	"■                                                      ■\n",
	"■                                                      ■\n",
	"■                                                      ■\n",
	"■                                                      ■\n",
	"■                                                      ■\n",
	"■                                                      ■\n",
	"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n"
};

enum{to_north=-1,to_south=1,to_west=-2,to_east=2};
int snakeLen=2;	//初始化贪吃蛇长度，默认为三节
int arr_snake[SNAKE_LENGTH][3]={0};//贪吃蛇
int snakeDirection=to_west;//贪吃蛇的默认移动方向
int rand_Food_x;		   //食物的随机初始位置(行)
int rand_Food_y;		   //食物的随机初始位置(列)
int bisFroFood=true;	   //定义是否产生食物的开关变量