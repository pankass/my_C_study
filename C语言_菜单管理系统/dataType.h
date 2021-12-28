#pragma once
struct menu {//定义菜品结构体
	int foodNum;
	char foodName[30];
	int price;//价格
	int cost;//成本
	int dailySales;//日销量
	int dailyIncome;//日净收入
	struct menu* next;
};

struct date {//订单日期
	int year;
	int month;
	int day;
};

struct orderForm {//定义订单结构体
	int orderFormNum;
	int people;//人数
	struct date formDate;//日期
	int menu[50][2];//每份订单中所选的菜,一个二维数组menu[i][0]存菜号,menu[i][1]存对应菜的数量。
	int menuNum;//菜的种数
	int sumPrice;//订单总价
	struct orderForm* next;
};