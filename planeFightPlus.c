#define MAPX 25
#define MAPY 79
#define STANDARD 26
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
typedef struct enemyBullet {
	int demage;
	int x;
	int y;
	char icon;
	struct enemyBullet* next;//链表的相关知识点。。next用于指向下一个链表。。
}ENEMYBullet;
typedef struct enemy {
	int x;
	int y;
	int HP;
	int deamage;
	char icon;
	int isUpDown;
	int moveToward;
	struct enemy* next;
}ENEMY;
typedef struct bullet {//定义结构体类型。。还未创建对象。。
	int deamage;
	int x;
	int y;
	char icon;
	struct bullet* next;//子弹链表的使用
}BULLET;
typedef struct hero {
	int x;
	int y;
	int HP;
	char icon;
}HERO;

char map[512][512];
int produceSpeed = 0;
int upDownCount = 0;
int score = 0;
//创建相关hero、enemy、hero bullet、enemy bullet 的相关对象。。
//链表头，不存储内容。。
ENEMY enemy;
BULLET heroBullet;
ENEMYBullet enemyBullet;
HERO hero;
//函数的声明，都在main()函数前面貌似没用，写上凑字数(doge)。。
void gotoxy(int, int);
void HideCursor();
void produceEnemy();
void heroShoot(BULLET*);
void init();
void paintMap();
void paintMenu();
void crash(ENEMY* );
void aboutHero();
void aboutEnemy();
void withInput(HERO*);
//************************************************************以下为功能函数
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

void produceEnemy()
{
	ENEMY* temp;
	int tempX;
	srand((unsigned)time(0));
	temp = (ENEMY*)malloc(sizeof(ENEMY));
	tempX = 2 + rand() % (MAPX - 3);
	
}

//hero发射子弹
void heroShoot(BULLET* heroBullet)//默认子弹
{

	//利用尾插法创建链表。。
	BULLET* bullet = (BULLET*)malloc(sizeof(BULLET));
	BULLET* head;
	if (bullet != NULL)
	{
		bullet->deamage = 10;
		bullet->x = hero.x;
		bullet->y = hero.y + 1;
		bullet->icon = '+';
		bullet->next = NULL;
	}
	head = heroBullet;
	while (1)
	{
		if (head->next == NULL)
		{
			head->next = bullet;
			break;
		}
		else
		{
			head = head->next;
		}
	}
}
void init()//初始化函数  hero飞机   enemy飞机  子弹链表next的初始化   生命值等。。  
{
	memset(map, ' ', sizeof(map));
	heroBullet.next = NULL;
	enemy.next = NULL;//初始化enmey的next节点。。
	//初始化hero
	hero.x = (MAPX - 1)/2;
	hero.y = 2;
	hero.HP = 100;
	hero.icon = '@';
	map[hero.x][hero.y] = hero.icon;
	//初始化enemy
	
}
void paintMap()//绘制游戏所有的内容。。
{
	for (int i = 1; i < MAPX; i++)
	{
		for (int j = 1; j < MAPY; j++)
		{
			if (j == 1 || j == MAPY - 1 || i == 1 || i == MAPX-1)//对游戏边框的绘制判断。。
			{
				printf("#");
				if (i == (MAPX - 1) / 4 && j == MAPY - 1)
				{
					printf("  当前得分：%d  ", score);
				}
				if (i == (MAPX - 1) / 3 && j == MAPY - 1)
				{
					printf("  HP: %d  ", hero.HP);
				}
			}
			else
			{
				printf("%c",map[i][j]);
			}
		}
		printf("\n");
	}
}
void paintMenu()
{
	printf("*************************************\n");
	printf("*        飞机大战乞丐版0.0           *\n");
	printf("*        按回任意键开始游戏           *\n");
	printf("*        提示:                       *\n");
	printf("*        移动:wasd/射击:j            *\n");
	printf("*************************************\n");
}

void crash(ENEMY* temp)//碰撞检测功能
{
	BULLET* head;
	BULLET* headLast;
	BULLET* headTemp;
	headLast = &heroBullet;
	head = heroBullet.next;
	if (temp->x == hero.x && temp->y-1 == hero.y+1)//判断是否enemy是否与hero相撞，及时释放内存。。
	{
		temp->HP = 0;
		hero.HP -= temp->deamage;
	}
	else if ((temp->x + 1 == hero.x - 1 && temp->y == hero.y)
		|| (temp->x + 1 == hero.x && temp->y == hero.y + 1)
		|| (temp->x - 1 == hero.x + 1 && temp->y == hero.y)
		|| (temp->x - 1 == hero.x && temp->y == hero.y + 1))
	{
		temp->HP = 0;
		hero.HP -= (temp->deamage-30);
	}
	while (head != NULL)
	{
		if (head->x == temp->x && head->y == temp->y - 1)
		{
			temp->HP -= (head->deamage * 3);
			headTemp = head;
			headLast->next = head->next;
			free(headTemp);
			break;
		}
		if ((head->x == temp->x - 1 || head->x == temp->x + 1) && head->y == temp->y)
		{
			temp->HP -= head->deamage;
			headTemp = head;
			headLast->next = head->next;
			free(headTemp);
			break;
		}
		head = head->next;
	}
}
void aboutHero()//有关hero的相关函数。。。
{
	//hero图标的改变
	map[hero.x][hero.y] = hero.icon;
	map[hero.x][hero.y + 1] = '>';
	map[hero.x - 1][hero.y] = '\\';
	map[hero.x + 1][hero.y] = '/';

	BULLET* temp = heroBullet.next;
	BULLET* tempLast = &heroBullet;//用于记录temp的上一个。方便后续的删除操作。。
	while (temp != NULL)//遍历hero子弹链表。。碰撞模块。。。
	{
		map[temp->x][temp->y] = temp->icon;
		//子弹飞行碰撞等相关操作;
		if (temp->y == MAPY - 1)
		{
			tempLast->next = temp->next;
			free(temp);
			temp = tempLast->next;
		}
		else if(temp != NULL)
		{
			map[temp->x][temp->y] = temp->icon;
			temp->y++;
			tempLast = temp;
			temp = temp->next;
		}

	}
}

void creatEnemy(ENEMY* enemy)//附加碰撞检测函数
{
	int tempX;
	ENEMY* head;
	head = enemy;
	//依旧是尾插法
	while (1)//遍历链表的过程中写入enemy数据。。
	{
		srand(time(0));
		tempX = rand() % (MAPX - 3) + 2;
		ENEMY* temp;

		if(head != NULL && head->next != NULL)//此处是每一个有效enemy结构体。
		{
			ENEMY* freeTemp;
			freeTemp = head->next;
			crash(freeTemp);
			if (freeTemp->HP <= 0 || freeTemp->y-1 == 1)//判断是否enemy是否到达最左端以及碰撞，及时释放内存。。
			{
				if (freeTemp->next != NULL)
				{
					if (freeTemp->HP <= 0)
					{
						if (freeTemp->isUpDown)
						{
							score += 10;
						}
						else
						{
							score++;
						}
					}
					head->next = freeTemp->next;
					if (freeTemp->y-1 != 1 && freeTemp->x-1 !=1)//击杀特效的简单实现
					{
						map[freeTemp->x - 1][freeTemp->y] = '█';
						map[freeTemp->x + 1][freeTemp->y] = '█';
						map[freeTemp->x][freeTemp->y - 1] = '█';
						map[freeTemp->x][freeTemp->y + 1] = '█';
					}
					free(freeTemp);
				}
			}
			head = head->next;
			if (head != NULL)
			{
				//enemy的移动实现。
				head->y--;
				if (head->isUpDown)
				{
					if (head->x == MAPX - 4 || head->x == 3)
					{
						head->moveToward = !head->moveToward;
					}
					if (head->moveToward > 0)
					{
						head->x++;
					}
					else
					{
						head->x--;
					}
				}
				if (head->y - 1 != 0 && head->x + 1 != MAPX - 1
					&& head->x - 1 != 1 && head->y != 1)//加判断防止缓冲区溢出产生
				{
					map[head->x][head->y] = head->icon;//画出enemy
					map[head->x - 1][head->y] = '/';
					map[head->x + 1][head->y] = '\\';
					map[head->x][head->y - 1] = '<';
				}
			}
		}
		if (head != NULL && head->next == NULL)
		{		//遍历结束退出循环。。。此处为最后一个enemy元素，也是enemy创造起点
			//创建enemy对象的链表。。
			temp = (ENEMY*)malloc(sizeof(ENEMY));
			if (produceSpeed == STANDARD)//达到STANDARD时执行。
			{
				if (temp != NULL)
				{					//初始化一下新创建的enemy结构体
					temp->deamage = 50;
					temp->HP = 30;
					temp->icon = '*';
					temp->x = tempX;
					temp->y = MAPY - 2;
					temp->moveToward = rand() % 2 ;
					temp->next = NULL;
					upDownCount++;
					if (upDownCount >= 4)
					{
						temp->isUpDown = 1;
						temp->HP = 50;
						temp->icon = '█';
						upDownCount = 0;
					}
					else
					{
						temp->isUpDown = 0;
					}
				}

				head->next = temp;
				produceSpeed = 0;
				break;
			}
			break;
		}
	}
}

void aboutEnemy()
{
	creatEnemy(&enemy);
	produceSpeed++;
}

void withInput(HERO* hero)//与用户输入相关。。
{
	int ch;
	if (_kbhit())
	{
		ch = _getch();
		if (ch == 'w' && hero->x > 2)
		{
			hero->x--;
		}
		if (ch == 's' && hero->x < MAPX - 2)
		{
			hero->x++;
		}
		if (ch == 'a' && hero->y > 2)
		{
			hero->y--;
		}
		if (ch == 'd' && hero->y < MAPY - 2)
		{
			hero->y++;
		}
		if (ch == 'j')
		{
			heroShoot(&heroBullet);
		}
	}
}

int main()
{
	init();//初始化
	paintMenu();
	system("pause");

	HideCursor();//隐藏控制台光标
	while (1)//游戏主循环..
	{
		gotoxy(0, 0);//将控制台光标移动至(0,0)处
		paintMap();//刷新绘制内容
		memset(map, ' ', sizeof(map));//刷新map[][]二维数组。。
		aboutEnemy();
		aboutHero();
		withInput(&hero);
		if (hero.HP <= 0)//游戏结束判定
		{
			break;
		}
	}
	system("cls");
	printf("\n\n\n\n\n\t\t\tgame over!!!!!\n\n\n\t\t\t您的得分为：%d\n\n\n",score);
	system("pause");
	system("pause");
	return 0;
}