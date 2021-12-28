#include <stdio.h>
#include <Windows.h>
#include "dataType.h"
#include "orderManage.h"
#include "showAndFileOperation.h"

//按销量排序
void sortBySales(struct menu* menuHead)
{
	struct menu temp;
	struct menu* pointTemp_1, *pointTemp_2;
	pointTemp_1 = menuHead;
	while (pointTemp_1)//遍历链表,选择排序
	{
		pointTemp_2 = pointTemp_1->next;
		while (pointTemp_2)
		{
			if (pointTemp_1->dailySales < pointTemp_2->dailySales)//第一个小于则交换
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
//按净收入排序
void sortByIncome(struct menu* menuHead)
{
	struct menu temp;
	struct menu* pointTemp_1, * pointTemp_2;
	pointTemp_1 = menuHead;
	while (pointTemp_1)//遍历链表,选择排序
	{
		pointTemp_2 = pointTemp_1->next;
		while (pointTemp_2)
		{
			if (pointTemp_1->dailyIncome < pointTemp_2->dailyIncome)//第一个小于则交换
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
//将菜品中的日销量和日净利润清0
void clearSalesAndIncome(struct menu* menuHead)
{
	struct menu* temp = menuHead;
	while (temp)
	{
		temp->dailySales = 0;//将日销量初始化为0
		temp->dailyIncome = 0;//将日净收入初始化为0
		temp = temp->next;
	}
}
//菜品销售统计
void menuSaleAnalyse(struct orderForm* orderFormHead, struct menu* menuHead)
{
	struct date inputDate;
	int choice = 1;
	struct orderForm* temp;
	temp = orderFormHead;
	clearSalesAndIncome(menuHead);////将菜品中的日销量和日净利润清0
	system("cls");
	printf("请输入订单日期(格式:年/月/日)-> ");
	scanf("%d/%d/%d", &inputDate.year, &inputDate.month, &inputDate.day);
	getchar();
	system("cls");
	while (temp)
	{
		if (temp->formDate.year == inputDate.year
			&& temp->formDate.month == inputDate.month
			&& temp->formDate.day == inputDate.day)//日期满足条件则
		{
			for (int i = 0; i < temp->menuNum; i++)//循环订单中的菜单数组
			{
				struct menu* target;
				//这里调用orderForm.h中的 searchMenu()函数(其返回值为struct menu*) 来查找对应的菜品
				target = searchMenu(menuHead, temp->menu[i][0]);//menu[][]二维数组第一列为菜号，第二列为对应菜号菜的数量
				target->dailySales += temp->menu[i][1];//对应菜品日销量增加
				target->dailyIncome = (target->price - target->cost) * target->dailySales;//计算日净收入
			}
		}
		temp = temp->next;
	}
	//显示所有统计分析后的菜单
	printf("%d年%02d月%02d日的销售情况\n", inputDate.year, inputDate.month, inputDate.day);
	showMenuSale(menuHead);
	printf("请选择(1.按日销量排序/2.按日净收入排序/0.退出)-> ");
	scanf("%d", &choice);
	getchar();
	system("cls");
	while (1)
	{
		system("cls");
		if (choice == 1)
		{
			sortBySales(menuHead);
		}
		else if (choice == 2) {
			sortByIncome(menuHead);
		}
		else if (choice == 0) {
			return;
		}
		printf("%d年%02d月%02d日的销售情况\n", inputDate.year, inputDate.month, inputDate.day);
		showMenuSale(menuHead);//显示
		printf("请选择(1.按日销量排序/2.按日净收入排序/0.退出)-> ");
		scanf("%d", &choice);
		getchar();
	}
}

//将所有订单中的sumPrice清0
void clearSumPrice(struct orderForm* orderFormHead)
{
	struct orderForm* temp = orderFormHead;
	while (temp)
	{
		temp->sumPrice = 0;
		temp = temp->next;
	}
}

//计算所有订单的总价
void calculatePrice(struct orderForm* orderFormHead, struct menu* menuHead)//计算所有订单的总价
{
	struct orderForm* temp = orderFormHead;
	struct menu* target;//查找到的目标菜品
	while (temp)
	{
		for (int i = 0; i < temp->menuNum; i++)
		{
			target = searchMenu(menuHead, temp->menu[i][0]);//查找对应菜号的菜
			if(target != NULL)
				temp->sumPrice += target->price * temp->menu[i][1];//计算价格
		}
		temp = temp->next;
	}
}

//按订单总价排序
void sortBySumPrice(struct orderForm* orderFormHead)//可以直接copy上面的sortByIncome()函数 (>_<)
{
	struct orderForm temp;
	struct orderForm* pointTemp_1, * pointTemp_2;
	pointTemp_1 = orderFormHead;
	while (pointTemp_1)//遍历链表,选择排序
	{
		pointTemp_2 = pointTemp_1->next;
		while (pointTemp_2)
		{
			if (pointTemp_1->sumPrice < pointTemp_2->sumPrice)//第一个小于则交换
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

//按订单就餐人数排序
void sortByPeople(struct orderForm* orderFormHead)//copy上面的
{
	struct orderForm temp;
	struct orderForm* pointTemp_1, * pointTemp_2;
	pointTemp_1 = orderFormHead;
	while (pointTemp_1)//遍历链表,选择排序
	{
		pointTemp_2 = pointTemp_1->next;
		while (pointTemp_2)
		{
			if (pointTemp_1->people < pointTemp_2->people)//第一个小于则交换
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

//订单统计
void orderFormAnalyse(struct orderForm* orderFormHead, struct menu* menuHead)
{
	struct date inputDate;
	int choice = 1;
	struct orderForm* temp;
	temp = orderFormHead;
	system("cls");
	printf("请输入订单日期(格式:年/月/日)-> ");
	scanf("%d/%d/%d", &inputDate.year, &inputDate.month, &inputDate.day);
	getchar();
	system("cls");
	clearSumPrice(orderFormHead);//将所有订单的总价清0
	calculatePrice(orderFormHead, menuHead);//计算所有订单总价
	//显示所有统计分析后的菜单
	printf("%d年%02d月%02d日的销售情况\n", inputDate.year, inputDate.month, inputDate.day);
	showFormInfo(orderFormHead, menuHead, inputDate);//显示对应的订单信息
	system("pause");
	printf("请选择(1.按订单总价排序/2.按就餐人数排序/0.退出)-> ");
	scanf("%d", &choice);
	getchar();
	system("cls");
	while (1)
	{
		system("cls");
		if (choice == 1)
		{
			sortBySumPrice(orderFormHead);
		}
		else if (choice == 2) {
			sortByPeople(orderFormHead);
		}
		else if (choice == 0) {
			return;
		}
		printf("%d年%02d月%02d日的销售情况\n", inputDate.year, inputDate.month, inputDate.day);
		showFormInfo(orderFormHead, menuHead, inputDate);//显示
		printf("请选择(1.按订单总价排序/2.按就餐人数排序/0.退出)-> ");
		scanf("%d", &choice);
		getchar();
	}
}