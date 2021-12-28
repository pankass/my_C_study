#include <stdio.h>
#include <stdlib.h>
#include "dataType.h"
#include "orderManage.h"

void showHomePage()//显示系统主页
{
	printf("\n\n\n");
	printf("\t\t\t欢迎使用菜单管理系统1.0\n\n");
	printf("\t\t\t-----1.菜单管理---------\n\n");
	printf("\t\t\t-----2.订单管理---------\n\n");
	printf("\t\t\t-----3.统计分析---------\n\n");
	printf("\t\t\t-----0.退出系统---------\n\n");
}

void showMenuManage()//显示菜单管理页面
{
	printf("\n\n\n");
	printf("\t\t\t########菜单管理##########\n\n");
	printf("\t\t\t------1.添加菜品----------\n\n");
	printf("\t\t\t------2.删除菜品----------\n\n");
	printf("\t\t\t------3.修改菜品----------\n\n");
	printf("\t\t\t------4.查询菜品----------\n\n");
	printf("\t\t\t------5.显示所有菜品-------\n\n");
	printf("\t\t\t------0.退出菜单管理-------\n\n");
}

void showOrderManage()//订单管理界面
{
	printf("\n\n\n");
	printf("\t\t\t########订单管理##########\n\n");
	printf("\t\t\t------1.添加订单----------\n\n");
	printf("\t\t\t------2.删除订单----------\n\n");
	printf("\t\t\t------3.修改订单----------\n\n");
	printf("\t\t\t------4.查询订单----------\n\n");
	printf("\t\t\t------5.显示所有订单-------\n\n");
	printf("\t\t\t------0.退出订单管理-------\n\n");
}

void showAnalyse()//统计分析界面
{
	printf("\n\n\n");
	printf("\t\t\t########统计分析##########\n\n");
	printf("\t\t\t------1.菜品销售统计--------\n\n");
	printf("\t\t\t------2.订单统计----------\n\n");
	printf("\t\t\t------0.退出订单管理-------\n\n");
}

//统计分析中的菜品显示
void showMenuSale(struct menu* head)
{
	struct menu* temp;
	temp = head;
	printf("\t\t菜号%10s菜名\t\t日销量\t\t日净收入\n", " ");
	while (temp)
	{
		printf("\t\t%02d\t%10s\t\t%d\t\t%d\n",
			temp->foodNum, temp->foodName, temp->dailySales, temp->dailyIncome);
		temp = temp->next;
	}
}

//统计分析中的订单显示
void showFormInfo(struct orderForm* orderFormHead, struct menu* menuHead, struct date inputDate)
{
	struct orderForm* temp;
	struct menu* searchTemp;
	int sum = 0, num = 0;
	temp = orderFormHead;
	while (temp)//遍历订单链表
	{
		if (temp->formDate.year == inputDate.year
			&& temp->formDate.month == inputDate.month
			&& temp->formDate.day == inputDate.day)//找到对应日期的订单进行输出
		{
			num++;//统计满足条件的订单总量
			sum += temp->sumPrice;//统计对应日期的订单的总价
			printf("订单号【%02d】\t下单时间【%d/%02d/%02d】\t共%d人\t该订单总价为【%d￥】\n",
				temp->orderFormNum, temp->formDate.year, temp->formDate.month, temp->formDate.day, temp->people, temp->sumPrice);
			for (int i = 0; i < temp->menuNum; i++)
			{
				searchTemp = searchMenu(menuHead, temp->menu[i][0]);
				if (searchTemp)
					printf("[%02d]号菜【%s】x %d\t\t", temp->menu[i][0], searchTemp->foodName, temp->menu[i][1]);
				if ((i + 1) % 3 == 0)
					printf("\n");
			}
			printf("\n\n");
		}
		temp = temp->next;
	}
	printf("%d年%02d月%02d日的所有订单总价为 %d元\t单均价为 %.2f元\n",
		inputDate.year, inputDate.month, inputDate.day, sum, 1.0 * sum / num);
}

//菜单管理相关显示和菜单文件读取

//菜单显示
void showMenu(struct menu* head, int oneOrAll)//oneOrAll参数为显示多少1为显示一个，否则为显示所有
{
	if (oneOrAll == 1)
	{
		printf("\t\t菜号%10s菜名\t\t价格\t\t成本\n"," ");
		printf("\t\t%02d\t%10s\t\t%d\t\t%d\n", head->foodNum, head->foodName, head->price, head->cost);
	}
	else
	{
		struct menu* temp;
		temp = head;
		printf("\t\t菜号%10s菜名\t\t价格\t\t成本\n"," ");
		while (temp)
		{
			printf("\t\t%02d\t%10s\t\t%d\t\t%d\n", 
				temp->foodNum, temp->foodName, temp->price, temp->cost);
			temp = temp->next;
		}
	}
}


struct menu* readMenuFile(struct menu* head)//读取菜单文件内容
{
	FILE* menuFile;
	menuFile = fopen("menu.txt", "r");//文件读取
	if (!menuFile)//没有menu.txt文件返回NUL
		return NULL;
	//menu.txt文件,执行下面的读取操作读取
	char fill[256] = { 0 };
	struct menu* temp, *newNode;
	struct menu tempMenu;
	fgets(fill, 256, menuFile);//填充读取文件第一行的标题栏
	while (fscanf(menuFile, "\t\t%d\t%s\t\t%d\t\t%d\n",
		&tempMenu.foodNum, tempMenu.foodName, &tempMenu.price, &tempMenu.cost) != EOF)//读到结束为止
	{//链表的尾插法
		if (!head)//如果没有头节点
		{
			newNode = (struct menu*)malloc(sizeof(struct menu));
			*newNode = tempMenu;
			head = newNode;
			temp = head;
			temp->next = NULL;
		}
		else //有头节点
		{
			newNode = (struct menu*)malloc(sizeof(struct menu));
			*newNode = tempMenu;
			temp->next = newNode;
			temp = temp->next;
			temp->next = NULL;
		}

	}
	fclose(menuFile);//关闭文件流操作
	return head;
}

void saveMenuFile(struct menu* head)//保存菜单数据
{
	FILE* menuFile;
	struct menu* temp;
	temp = head;
	menuFile = fopen("menu.txt", "w");//创建并清空menu.txt文件
	fprintf(menuFile,"\t\t菜号\t%16s菜名\t\t价格\t\t成本\n", " ");//这里%16s的空格为了格式整齐而加
	while (temp)
	{
		fprintf(menuFile,"\t\t%02d\t%16s\t\t%d\t\t%d\n",//这里%16s的空格为了格式整齐而加
			temp->foodNum, temp->foodName, temp->price, temp->cost);
		temp = temp->next;
	}
	fclose(menuFile);
}
//订单管理相关显示和订单文件的读取
void showOrderForm(struct orderForm* orderForm, struct menu* menuHead,int oneOrAll)
//oneOrAll参数为显示多少1为显示一个，否则为显示所有
{
	if (orderForm == NULL)//没有订单
	{
		printf("暂无订单\n");
		return;
	}
	if (oneOrAll)//输出一个订单
	{
		printf("订单号【%02d】\t下单时间【%d/%02d/%02d】\t共%d人\n",
			orderForm->orderFormNum,orderForm->formDate.year,
			orderForm->formDate.month,orderForm->formDate.day, orderForm->people);
		for (int i = 0; i < orderForm->menuNum; i++)
		{
			printf("[%02d]号菜【%s】x %d\t\t", orderForm->menu[i][0], searchMenu(menuHead, orderForm->menu[i][0])->foodName, orderForm->menu[i][1]);
			if ((i + 1) % 3 == 0)
				printf("\n");
		}
		printf("\n");
	}
	else//输出所有订单
	{
		struct orderForm* temp;
		struct menu* searchTemp;
		temp = orderForm;
		while (temp)//遍历订单链表
		{
			printf("订单号【%02d】\t下单时间【%d/%02d/%02d】\t共%d人\n",
				temp->orderFormNum, temp->formDate.year, temp->formDate.month, temp->formDate.day, temp->people);
			for (int i = 0; i < temp->menuNum; i++)
			{
				searchTemp = searchMenu(menuHead, temp->menu[i][0]);
				if (searchTemp)
					printf("[%02d]号菜【%s】x %d\t\t", temp->menu[i][0],searchTemp->foodName, temp->menu[i][1]);
				if ((i + 1) % 3 == 0)
					printf("\n");
			}
			printf("\n\n");
			temp = temp->next;
		}
	}
}

struct menu* readOrderFormFile(struct orderForm* orderFormHead)//读取订单文件内容
{
	FILE* orderFormFile;
	orderFormFile = fopen("orderForm.txt", "r");
	if (!orderFormFile)//如果读取失败返回NULL
		return NULL;
	struct orderForm* orderFormTemp, * newNode;
	struct orderForm temp;//中间变量
	//使用尾插法插入订单数据
	while (!feof(orderFormFile))
	{
		fscanf(orderFormFile, "%d种菜\t%d人\t订单号【%2d】\t下单时间【%d/%02d/%02d】\n",
			&temp.menuNum, &temp.people,&temp.orderFormNum, &temp.formDate.year, &temp.formDate.month, &temp.formDate.day);
		for (int i = 0; i < temp.menuNum; i++)
		{
			fscanf(orderFormFile, "【%d】号菜 x %d\t", &temp.menu[i][0], &temp.menu[i][1]);
			if ((i + 1) % 2 == 0)
				fscanf(orderFormFile, "\n");
		}
		fscanf(orderFormFile, "\n\n");
		newNode = (struct orderForm*)malloc(sizeof(struct orderForm));
		temp.next = NULL;
		*newNode = temp;
		if (!orderFormHead)//没有头节点
		{
			orderFormHead = newNode;
			orderFormTemp = orderFormHead;
		}
		else
		{
			orderFormTemp->next = newNode;
			orderFormTemp = orderFormTemp->next;
		}
	}
	return orderFormHead;
	fclose(orderFormFile);
}

void saveOrderFormFile(struct orderForm* orderFormHead)//保存订单数据
{
	FILE* orderFormFile;
	struct orderForm* temp = orderFormHead;
	orderFormFile = fopen("orderForm.txt", "w");
	while (temp)
	{
		fprintf(orderFormFile, "%d种菜\t%d人\t订单号【%02d】\t下单时间【%d/%02d/%02d】\n",
			temp->menuNum,temp->people,temp->orderFormNum, temp->formDate.year, temp->formDate.month, temp->formDate.day);
		for (int i = 0; i < temp->menuNum; i++)
		{
			fprintf(orderFormFile, "【%d】号菜 x %d\t", temp->menu[i][0], temp->menu[i][1]);
			if ((i + 1) % 2 == 0)
				fprintf(orderFormFile, "\n");
		}
		fprintf(orderFormFile, "\n\n");
		temp = temp->next;
	}
	fclose(orderFormFile);
}