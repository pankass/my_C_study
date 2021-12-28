#include <stdio.h>
#include <Windows.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "dataType.h"
#include "showAndFileOperation.h"
//整个订单管理和菜单管理类似
// 
//对菜单的简单查询
struct menu* searchMenu(struct menu* menuHead, int foodNum)
{
	struct menu* temp = menuHead;
	while (temp)
	{
		if (foodNum == temp->foodNum)
		{
			return temp;
		}
		temp = temp->next;
	}
	return NULL;//未查询到则返回NULL
}

//订单号查重
int ifRepeatOrder(struct orderForm* orderFormHead, int orderNum)
{
	struct orderForm* temp;
	temp = orderFormHead;
	while (temp)
	{
		if (orderNum == temp->orderFormNum)//订单号重复返回1否则返回0
			return 1;
		temp = temp->next;
	}
	return 0;
}
//查询订单,该函数与菜单查询略有不同
void queryOrderForm(struct orderForm* orderFormHead,struct menu* menuHead)
{
	int orderFormNum;
	struct date formDate;
	int choice = 0;
	struct orderForm* temp;
	while (1)
	{
		temp = orderFormHead;//记录头节点
		system("cls");
		printf("\t\t\t订单管理-->查询订单\n");
		printf("1:按订单号查询/2:按日期查询/3:退出查询-> ");
		scanf("%d", &choice);
		getchar();//getchar()吞掉'\n',不然会有bug
		if (choice == 1)
		{
			printf("\n请输入订单号-> ");
			scanf("%d", &orderFormNum);
			getchar();
			while (temp)//遍历订单链表  即temp不为NULL时执行
			{
				if (temp->orderFormNum == orderFormNum)
				{
					
					showOrderForm(temp, menuHead, 1);//查询到则显示所查询到的1项
					system("pause");
					return;//(订单号唯一,可直接结束)
				}
				temp = temp->next;
			}
			printf("未查询到订单信息！\n");//没有查询到时输出
			system("pause");
		}
		else if (choice == 2)//按日期查询 ，列出对应日期的所有订单
		{
			printf("\n请输入日期（格式：年/月/日）-> ");
			scanf("%d/%d/%d", &formDate.year, &formDate.month, &formDate.day);
			getchar();
			int flag = 1;//记录是否查询到订单信息
			while (temp)
			{
				if (temp->formDate.year == formDate.year
					&& temp->formDate.month == formDate.month
					&& temp->formDate.day == formDate.day)
				{
					showOrderForm(temp, menuHead, 1);
					printf("\n");//换行，整齐一些
					flag = 0;
				}
				temp = temp->next;
			}
			if (flag)//flag为1则未查询到
				printf("未查询到订单信息！\n");
			system("pause");
			return;
		}
		else if(choice == 3)
		{
			return;
		}
		else
		{
			printf("非法的输入!!\n");
			system("pause");
		}
	}

}

//添加订单
struct orderForm* addOrderForm(struct orderForm* orderFormHead, struct menu* menuHead)
{
	struct date orderFormDate;
	struct orderForm* newNode;
	char choice = 'y';
	int orderNum,people;
	while (choice == 'y')
	{
		system("cls");
		printf("\t\t\t订单管理-->添加订单\n");
		printf("请输入订单号-> ");
		scanf("%d", &orderNum);
		getchar();
		if (ifRepeatOrder(orderFormHead, orderNum))//判断订单号是否重复
		{
			printf("【%d】号订单以存在，请重新输入!\n",orderNum);
			system("pause");
			continue;//continue跳过当前循环到下个循环
		}
		printf("\n请输入下单时间（格式：年/月/日）-> ");
		scanf("%d/%d/%d", &orderFormDate.year, &orderFormDate.month, &orderFormDate.day);
		getchar();
		printf("\n请输入就餐人数-> ");
		scanf("%d", &people);
		getchar();
		system("cls");
		showMenu(menuHead, 0);//显示菜单
		char orderChoice = 'y';
		newNode = (struct orderForm*)malloc(sizeof(struct orderForm));//采用头插法
		//将新建的订单结构体赋值
		newNode->formDate = orderFormDate;
		newNode->orderFormNum = orderNum;//订单号
		newNode->menuNum = 0;//点菜种类
		newNode->people = people;//就餐人数
		while (orderChoice == 'y')
		{
			int foodNum;
			LOOP:
			printf("\n请点菜(输入菜号)-> ");
			scanf("%d", &foodNum);
			getchar();
			if (searchMenu(menuHead, foodNum) == NULL)
			{
				printf("%d号菜不存在，请重新点菜!\n", foodNum);
				goto LOOP;
			}
			newNode->menu[newNode->menuNum][0] = foodNum;
			printf("请输入数量-> ");
			scanf("%d", &newNode->menu[newNode->menuNum][1]);
			getchar();
			newNode->menuNum++;
			printf("是否继续点菜？(继续/y;结束/n)-> ");
			scanf("%c", &orderChoice);
			getchar();
		}
		newNode->next = orderFormHead;//头插法添加
		orderFormHead = newNode;
		showOrderForm(newNode, menuHead, 1);
		printf("添加订单成功\n");
		printf("是否继续添加？（y:继续/n:结束）-> ");
		scanf("%c", &choice);
		getchar();

		choice = tolower(choice);//转为小写字母,方便也支持Y和N
	}
	saveOrderFormFile(orderFormHead);//保存订单文件
	return orderFormHead;//返回进行添加操作后的头节点
}

//删除订单
struct orderForm* deleteOrderForm(struct orderForm* orderFormHead, struct menu* menuHead)
{
	system("cls");
	printf("\t\t\t订单管理-->删除订单\n");
	if (orderFormHead == NULL)
	{
		printf("没有可删除的订单！\n");
		return NULL;
	}
	int delNum;
	struct orderForm* temp,* oldNode;
	char confirm = 'n';
	showOrderForm(orderFormHead, menuHead, 0);
	printf("请输入您要删除的订单的订单号-> ");
	scanf("%d", &delNum);
	getchar();
	if (orderFormHead->orderFormNum == delNum)//如果头节点即为所需删除节点
	{
		system("cls");
		printf("确认删除吗？(y:确认/n:取消)\n");
		showOrderForm(orderFormHead, menuHead, 1);
		scanf("%c", &confirm);
		getchar();
		if (confirm == 'n')
		{
			printf("您以取消删除操作\n");
			system("pause");
			return orderFormHead;
		}
		else
		{
			temp = orderFormHead;
			orderFormHead = orderFormHead->next;
			free(temp);
			printf("删除成功\n");
			system("pause");
			return orderFormHead;
		}
	}
	//除头节点之外,和上面类似
	oldNode = orderFormHead;
	temp = orderFormHead->next;
	while (temp)
	{
		if (temp->orderFormNum == delNum)
		{
			system("cls");
			printf("确认删除吗？(y:确认/n:取消)\n");
			showOrderForm(temp, menuHead, 1);
			scanf("%c", &confirm);
			getchar();
			if (confirm == 'n')
			{
				printf("您以取消删除操作\n");
				system("pause");
				return orderFormHead;
			}
			else
			{
				oldNode->next = temp->next;
				free(temp);
				printf("删除成功\n");
				system("pause");
				return orderFormHead;
			}
		}
		temp = temp->next;
		oldNode = oldNode->next;
	}
	printf("无此订单号\n");
	system("pause");
	return orderFormHead;
}

//修改订单
struct orderForm* changeOrderForm(struct orderForm* orderFormHead, struct menu* menuHead)
{
	system("cls");
	printf("\t\t\t订单管理-->修改订单\n");
	if (orderFormHead == NULL)//无订单返回NULL
	{
		printf("没有可修改的订单！\n");
		return NULL;
	}
	int changeNum;//要修改的订单号
	showOrderForm(orderFormHead, menuHead, 0);//显示所有订单
	printf("请输入您要修改的订单的订单号-> ");
	scanf("%d", &changeNum);
	getchar();
	struct orderForm* temp;
	temp = orderFormHead;
	while (temp)//遍历订单链表
	{
		if (temp->orderFormNum == changeNum)
		{
			int choice;
			char orderChoice = 'y';
			printf("1.添加菜品/2.删除菜品/3.修改菜品/0.退出-> ");
			scanf("%d", &choice);
			getchar();
			switch (choice)
			{
				case 1://加菜
					while (orderChoice == 'y')//订单中的菜单为二维数组
					{
						system("cls");
						showMenu(menuHead, 0);//显示菜单
						int foodNum;
					LOOP1:
						printf("\n请点菜(输入菜号)-> ");
						scanf("%d", &foodNum);
						getchar();
						if (searchMenu(menuHead, foodNum) == NULL)
						{
							printf("%d号菜不存在，请重新点菜!\n", foodNum);
							goto LOOP1;
						}
						temp->menu[temp->menuNum][0] = foodNum;
						printf("请输入数量-> ");
						scanf("%d", &temp->menu[temp->menuNum][1]);
						getchar();
						temp->menuNum++;
						showOrderForm(temp, menuHead, 1);//显示修改后的订单
						printf("是否继续点菜？(继续/y;结束/n)-> ");
						scanf("%c", &orderChoice);
						getchar();
					}
					printf("\n订单修改成功\n");
					saveOrderFormFile(orderFormHead);//保存修改后的订单
					system("pause");
					return orderFormHead;//返回头节点
				case 2://删菜
					while (orderChoice == 'y')
					{
						int foodNum;//所要删除的菜的菜号
						system("cls");
						showOrderForm(temp, menuHead, 1);
						printf("请输入您要删除的菜的菜号-> ");
						scanf("%d", &foodNum);
						getchar();
						for (int i = 0; i < temp->menuNum; i++)//循环订单中的菜单数组
						{
							if (temp->menu[i][0] == foodNum)//找到要删除的菜的菜号
							{
								for (int j = i; j < temp->menuNum; j++)
								{
									temp->menu[j][0] = temp->menu[j + 1][0];//将后一个赋值给前一个
									temp->menu[j][1] = temp->menu[j + 1][1];
								}
								temp->menuNum--;//删除后菜的种类少一个
								break;
							}
						}
						showOrderForm(temp, menuHead, 1);//显示修改后的订单
						printf("是否继续删除？(继续/y;结束/n)-> ");
						scanf("%c", &orderChoice);
						getchar();
					}
					printf("\n订单修改成功\n");
					saveOrderFormFile(orderFormHead);//保存修改后的订单
					system("pause");
					return orderFormHead;//返回头节点
				case 3://改菜
					while (orderChoice == 'y')
					{
						int foodNum;//所要修改的菜号
						int	foodChanngeNum;//修改后的菜号
						int	foodCount;//对应菜号修改后的数量
						int choice;//功能选择
						system("cls");
						showOrderForm(temp, menuHead, 1);
						printf("请输入您要修改的菜的菜号-> ");
						scanf("%d", &foodNum);
						getchar();
						printf("请选择(1.更换【%s】/2.更改【%s】的数量)-> "
							, searchMenu(menuHead, foodNum)->foodName, searchMenu(menuHead, foodNum)->foodName);
						scanf("%d", &choice);
						getchar();
						if (choice == 1)
						{
							showMenu(menuHead, 0);
							printf("请输入更换后的菜的菜号-> ");
							scanf("%d", &foodChanngeNum);
							getchar();
							for (int i = 0; i < temp->menuNum; i++)//遍历订单中的菜单找到目标菜号修改
							{
								if (temp->menu[i][0] == foodNum)
								{
									temp->menu[i][0] = foodChanngeNum;//修改菜号,注意第二个[]为0
									break;
								}
							}
						}
						else if (choice == 2)
						{
							printf("请输入修改后的数量-> ");
							scanf("%d", &foodCount);
							getchar();
							for (int i = 0; i < temp->menuNum; i++)//遍历订单中的菜单找到目标菜号修改
							{
								if (temp->menu[i][0] == foodNum)
								{
									temp->menu[i][1] = foodCount;//修改数量,注意第二个[]为1
									break;
								}
							}
						}
						showOrderForm(temp, menuHead, 1);//显示修改后的订单
						printf("是否继续修改？(继续/y;结束/n)-> ");
						scanf("%c", &orderChoice);
						getchar();
					}
					printf("\n订单修改成功\n");
					saveOrderFormFile(orderFormHead);//保存修改后的订单
					system("pause");
					return orderFormHead;//返回头节点
				case 0://退出
					return orderFormHead;
			}
		}
		temp = temp->next;
	}
	if (!temp)//输入的订单不存在情况下
	{
		printf("无此订单\n");
		system("pause");
		return orderFormHead;
	}
}
