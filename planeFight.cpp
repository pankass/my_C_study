#include<stdio.h>
#include<windows.h>
#include<conio.h>
//定义全局变量 
int high, width;						//定义边界 
int position_x, position_y;			//飞机位置 
int bullet_x, bullet_y;				//子弹位置 
int enemy_x, enemy_y;
int score;
int flag;							//飞机状态 
void gotoxy(int x, int y)  			//光标移动到(x,y)位置
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}
void HideCursor() // 用于隐藏光标
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };  // 第二个值为0表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}


void startup()						//数据初始化 
{
	high = 18;
	width = 26;

	position_x = high - 3;
	position_y = width / 2;

	bullet_x = 0;
	bullet_y = position_y;

	enemy_x = 0;
	enemy_y = position_y;

	score = 0;

	flag = 0;							//飞机完好 

	HideCursor();
}
void show()							//显示界面 
{
	int i, j;
	for (i = 0; i < high; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (flag)
				break;

			else if ((i == position_x) && (j == position_y))		//飞机坐标 
				printf("*");
			else if ((i == enemy_x) && (j == enemy_y))				//敌机坐标 
				printf("*");
			else if ((i == bullet_x) && (j == bullet_y))			//子弹坐标 
				printf("|");
			else if ((j == width - 1) || (i == high - 1) || (j == 0) || (i == 0))				//打印边界 
				printf("#");
			else
				printf(" ");
		}
		printf("\n");
	}
	printf("\n");
	if ((position_x == enemy_x) && (position_y == enemy_y))
	{
		flag = 1;							//飞机撞毁 游戏结束 
		printf("得分: %d\n", score);
		printf("游戏结束");
	}
	else
		printf("得分: %d\n", score);
}
void withoutInpute()						//与用户输入无关
{
	if (bullet_x > 0)							//子弹上升效果 
		bullet_x--;
	if ((bullet_x == enemy_x) && (bullet_y == enemy_y))		//子弹命中敌机 
	{
		score++;
		bullet_x = -1;
		enemy_x = 1;
		enemy_y = 2 + rand() % width - 2;
	}


	static int speed;
	if (speed < 30)					//减慢敌机速度，不影响飞机和子弹速度 
		speed++;
	if (speed == 30)
	{
		if (enemy_x < high)
			enemy_x++;
		else
		{
			enemy_x = 0;
			enemy_y = 2 + rand() % width - 2;
		}
		speed = 0;
	}




}
void withInpute()						//与用户输入有关 
{
	char input;
	if (_kbhit())										//控制飞机方向 
	{
		input = _getch();
		if ((input == 'w') && position_x > 1)
			position_x--;
		if ((input == 's') && position_x < high - 2)
			position_x++;
		if ((input == 'a') && position_y > 1)
			position_y--;
		if ((input == 'd') && position_y < width - 2)
			position_y++;
		if (input == ' ')
		{
			bullet_x = position_x - 1;
			bullet_y = position_y;
		}
	}
}
int main()
{
	system("color 2f");
	startup();					// 数据初始化
	while (1)					//  游戏循环执行
	{
		gotoxy(0, 0);
		show();					// 显示画面
		withoutInpute();		// 与用户输入无关的更新
		withInpute();			// 与用户输入有关的更新
	}
}
