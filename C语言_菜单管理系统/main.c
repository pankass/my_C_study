#include <stdio.h>
#include <Windows.h>
#include "dataType.h"
#include "showAndFileOperation.h"
#include "menuManage.h"
#include "orderManage.h"
#include "analyse.h"
int main()
{
	struct menu* menuHead = NULL;
	struct menu* menuTemp = NULL;
	struct orderForm* orderFormHead = NULL;
	int mainChoice;
	int menuChoice;
	int orderChoice;
	int analyseChoice;

	//读取菜单文件中的信息到内存中
	menuHead = readMenuFile(menuHead);
	//读取订单文件中的信息到内存中
	orderFormHead = readOrderFormFile(orderFormHead);
	while (1)//系统主循环
	{
		system("cls");
		showHomePage();
		printf("请选择您需要的功能的编号-> ");
		scanf("%d", &mainChoice);
		getchar();

		switch (mainChoice)
		{
		case 1://菜单管理
			while (1)
			{
				int flag = 0;
				system("cls");
				showMenuManage();//显示菜单管理主页
				sortByNum(menuHead);//进入菜单管理就将菜品按照菜号进行排序
				printf("请选择功能-> ");
				scanf("%d", &menuChoice);
				getchar();
				switch (menuChoice)
				{
				case 1://增
					menuHead = addMenu(menuHead);
					break;
				case 2://删
					menuHead = deleteMenu(menuHead);
					break;
				case 3://改
					menuHead = changeMenu(menuHead);
					break;
				case 4://查
					menuTemp = queryMenu(menuHead, NULL);
					if (menuTemp)
						showMenu(menuTemp, 1);//queryMenu函数将查询到的链表地址赋值给showMenu显示
					else
						printf("未查询到相关信息！\n");
					system("pause");
					break;
				case 5://显示所有菜品
					system("cls");
					showMenu(menuHead, 0);
					system("pause");
					break;
				case 0://退出菜单管理
					flag = 1;
					break;
				default://非法输入
					printf("输入不正确哟~~\n");
					system("pause");
					break;
				}
				saveMenuFile(menuHead);//使用一次菜单管理就及时保存文件
				if (flag)//flag==1时表示退出菜单管理
				{
					flag = 0;
					break;
				}
			}
			break;
		case 2://订单管理
			while (1)
			{
				int flag = 0;
				system("cls");
				showOrderManage();
				printf("请选择功能-> ");
				scanf("%d", &orderChoice);
				getchar();
				switch (orderChoice)
				{
				case 1://增
					orderFormHead = addOrderForm(orderFormHead, menuHead);
					break;
				case 2://删
					orderFormHead = deleteOrderForm(orderFormHead, menuHead);
					break;
				case 3://改
					orderFormHead = changeOrderForm(orderFormHead, menuHead);
					break;
				case 4://查
					queryOrderForm(orderFormHead, menuHead);
					break;
				case 5://显示所有订单
					system("cls");//清屏
					showOrderForm(orderFormHead, menuHead, 0);
					system("pause");
					break;
				case 0://退出菜单管理
					flag = 1;
					break;
				default://非法输入
					printf("输入不正确哟~~\n");
					system("pause");
					break;
				}
				saveOrderFormFile(orderFormHead);//使用一次订单管理就及时保存文件
				if (flag)//flag==1时表示退出菜单管理
				{
					flag = 0;
					break;
				}
			}
			break;
		case 3://统计分析
			while (1)//统计分析主循环
			{
				int flag = 0;
				system("cls");
				showAnalyse();//显示统计分析功能的主页面
				printf("请选择功能-> ");
				scanf("%d", &analyseChoice);
				getchar();

				switch (analyseChoice)
				{
				case 1://菜品销售统计
					menuSaleAnalyse(orderFormHead, menuHead);
					break;
				case 2://订单统计
					orderFormAnalyse(orderFormHead, menuHead);
					break;
				case 0:
					flag = 1;//flag==1时表示退出菜单管理
					break;
				default:
					printf("输入不正确哟~~\n");
					system("pause");
					break;
				}
				if (flag)//flag==1时表示退出菜单管理
				{
					flag = 0;
					break;
				}
			}
			break;
		case 0://退出系统
			exit(0);
		default://输入错误
			printf("输入不正确哟~~\n");
			system("pause");
			break;

		}
	}
	return 0;
}