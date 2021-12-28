#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "dataType.h"
#include "showAndFileOperation.h"
//该.c文件为所有有关菜单管理的相关函数。。

//查询菜品
struct menu* queryMenu(struct menu* head, struct menu** oldNode)
	//二级指针oldNode用于记录目标的上个节点，方便删除函数的使用，不使用时赋值为NULL即可
{
	int foodNum;
	char foodName[30] = { 0 };
	int choice = 0;
	struct menu* temp;
	temp = head;//记录头节点
	if (oldNode != NULL)//这里若oldNode 有值说明使用了删除函数oldNode派上了用场
	{
		*oldNode = head;//二级指针赋值
	}
	while (1)
	{
		system("cls");
		printf("1:按菜号查询/2:按菜名查询-> ");
		scanf("%d", &choice);
		getchar();//getchar()吞掉'\n',不然会有bug
		if (choice == 1)//按菜号查询
		{
			printf("\n请输入菜号-> ");
			scanf("%d", &foodNum);
			getchar();
			while (temp)//遍历菜单链表  temp即temp不为NULL是执行
			{
				if (temp->foodNum == foodNum)
				{
					return temp;//查询到则返回查询到的结构体地址
				}
				if (oldNode != NULL)//如果需要有oldNode
				{
					*oldNode = temp;
				}
				temp = temp->next;
			}
			return NULL;//没有查询到时返回NULL
		}
		else if (choice == 2)//按菜名查询  相应方法同上
		{
			printf("\n请输入菜名-> ");
			scanf("%s", foodName);
			getchar();
			while (temp)//遍历菜品链表
			{
				if (!strcmp(temp->foodName, foodName))//菜名相同
				{
					return temp;
				}
				if (oldNode != NULL)
				{
					*oldNode = temp;
				}
				temp = temp->next;
			}
			return NULL;//返回NULL则未查询到相关信息
		}
		else
		{
			printf("非法的输入!!\n");
			system("pause");
		}
	}
	
}

//添加菜品
struct menu* addMenu(struct menu* menuHead)//插入菜品的方法采用链表的头插法
{
	struct menu* newNode;
	char choice = 'y';
	int foodNum;
	char foodName[30] = { 0 };
	int price;
	int cost;
	system("cls");
	printf("\t\t\t菜单管理-->添加菜品\n");
	while (choice == 'y')
	{
		printf("请输入菜号-> ");
		scanf("%d", &foodNum);
		getchar();
		if (ifRepeatMenu(menuHead, foodNum, NULL, 1) == 1)//第四个参数为1为判断菜号，为0为判断菜名
		{
			printf("【%02d】号菜以存在，请重新添加！\n",foodNum); //返回1表示该菜号以存在,返回2表示该菜名以存在
			system("pause");
			return menuHead;
		}
		printf("\n请输入菜名-> ");
		scanf("%s", foodName);
		getchar();
		if (ifRepeatMenu(menuHead, 0, foodName, 0) == 2)
		{
			printf("【%s】已存在，请重新添加！\n",foodName);
			system("pause");
			return menuHead;
		}
		printf("\n请输入菜价-> ");
		scanf("%d", &price);
		getchar();
		printf("\n请输入成本-> ");
		scanf("%d", &cost);
		getchar();
		newNode = (struct menu*)malloc(sizeof(struct menu));//创建新的节点
		newNode->next = NULL;//别忘了给尾巴赋值为NULL
		//将新建的菜品结构体赋值
		newNode->foodNum = foodNum;
		strcpy(newNode->foodName, foodName);
		newNode->price = price;
		newNode->cost = cost;

		newNode->next = menuHead;//头插法
		menuHead = newNode;
		showMenu(newNode, 1);//显示刚添加的菜品
		printf("添加成功\n");
		printf("是否继续添加？（y:继续/n:结束）-> ");
		scanf("%c", &choice);
		getchar();
		
		choice = tolower(choice);//转为小写字母,方便也支持Y和N
	}
	saveMenuFile(menuHead);
	return menuHead;//返回进行添加操作后的头节点
}

//删除菜品
struct menu* deleteMenu(struct menu* head)//此函数一次只删除一个节点
{
	struct menu* target;
	struct menu* oldNode;
	char confirm = 'n';
	//调用查询函数queryMenu()先进行查询操作
	target = queryMenu(head, &oldNode);
	if (target)//如果查询到了菜品，则进行删除操作
	{
		showMenu(target, 1);//显示查询到的菜品
		printf("确认要删除【%s】吗？(y:确认/n:取消)-> ", target->foodName);
		scanf("%c", &confirm);
		getchar();
		confirm = tolower(confirm);
		if (confirm == 'y')
		{
			if (target == head)//如果头节点即为所需删除的节点
			{
				head = head->next;
				free(target);
			}
			else//非头节点  
			{
				oldNode->next = target->next;//删除target节点
				free(target);
			}
			printf("\n删除成功!");
		}
		else
		{
			printf("\n您已取消操作");
		}
	}
	else
	{
		printf("\n未查询到相关信息!");
	}
	system("pause");
	saveMenuFile(head);
	return head;//返回删除操作后的头节点
}

//修改菜品
struct menu* changeMenu(struct menu* head)
{
	struct menu* target;
	int foodNum;
	char foodName[30] = { 0 };
	int price;//菜品价格
	int cost;
	char select = 'y';
	target = queryMenu(head, NULL);//修改功能先调用查询函数
	if (target)//如果找到则修改
	{
		while (select == 'y')//输入y继续，n结束(输入在下方)
		{
			system("cls");
			showMenu(target, 1);//显示查询到的结果
			LOOP1:
			printf("请选择您需要的功能:\n修改菜号(1)/修改菜名(2)/修改价格(3)/修改成本(4)/取消修改(n)\n");
			scanf("%c", &select);
			getchar();//将回车吞掉，不然有bug
			switch (select)
			{
				case '1':
					printf("修改菜号\n您要将该菜号修改为-> ");
					scanf("%d", &foodNum);
					getchar();
					target->foodNum = foodNum;
					break;
				case '2':
					printf("修改菜名\n您要将菜名修改为-> ");
					scanf("%s", foodName);
					getchar();
					strcpy(target->foodName, foodName);
					break;
				case '3':
					printf("修改价格\n您要将价格修改为-> ");
					scanf("%d", &price);
					getchar();
					target->price = price;
					break;
				case '4':
					printf("修改成本\n您要将成本修改为-> ");
					scanf("%d", &cost);
					getchar();
					target->cost = cost;
					break;
				case 'n':
					return head;
				default:
					printf("非法的输入!\n");
					system("pause");
					goto LOOP1;
			}
			printf("修改成功!\n");
			showMenu(target, 1);
			system("pause");
			LOOP2:
			printf("是否继续修改?/继续(y)/结束(n)-> ");
			scanf("%c", &select);
			getchar();
			
			if (select != 'y' && select != 'n')
			{
				printf("非法的输入!\n");
				//system("pause");
				goto LOOP2;
			}
		}
	}
	else
	{
		printf("未查询到相关信息!\n");
	}

	saveMenuFile(head);
	system("pause");
	return head;
}

//以下为额外添加的细节,用于添加菜品时查重
int ifRepeatMenu(struct menu* head,int foodNum,char *foodName,int select)//判断是否菜号或菜名重复
{//select参数为1为判断菜号，为0为判断菜名
	struct menu* temp;
	temp = head;
	if (select)//按菜号
	{
		while (temp)//遍历链表
		{
			if (foodNum == temp->foodNum)
			{
				return 1;//返回1表示该菜号以存在
			}
			temp = temp->next;
		}
	}
	else 
	{//按菜名同上
		while (temp)
		{
			if (!strcmp(temp->foodName, foodName))//strcmp()函数两字符串相等返回0
			{
				return 2;//返回2表示该菜名以存在
			}
			temp = temp->next;
		}
	}
}

//将菜品按照菜号排好序排序
void sortByNum(struct menu* menuHead)//选择排序
{
	struct menu temp;
	struct menu* pointTemp_1, * pointTemp_2;
	pointTemp_1 = menuHead;
	while (pointTemp_1)//遍历链表,选择排序
	{
		pointTemp_2 = pointTemp_1->next;
		while (pointTemp_2)
		{
			if (pointTemp_1->foodNum > pointTemp_2->foodNum)//第一个大于则交换
			{
				temp = *pointTemp_1;
				*pointTemp_1 = *pointTemp_2;
				*pointTemp_2 = temp;
				pointTemp_2->next = pointTemp_1->next;//将两个节点next的指向保持不变
				pointTemp_1->next = temp.next;
			}
			pointTemp_2 = pointTemp_2->next;//前往下一个节点
		}
		pointTemp_1 = pointTemp_1->next;//前往下一个节点
	}
}