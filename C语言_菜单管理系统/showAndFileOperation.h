#pragma once

void showMenu(struct menu* head, int oneOrAll);//显示菜品

void showHomePage();//显示系统主页

void showMenuManage();//显示菜单管理页面

void showOrderManage();//显示订单管理界面

void showAnalyse();//显示统计分析界面

struct menu* readMenuFile(struct menu* head);//读取菜单文件内容

void saveMenuFile(struct menu* head);//保存菜单数据

void showOrderForm(struct orderForm* orderFormHead, struct menu* menuHead, int oneOrAll);//显示订单

void saveOrderFormFile(struct orderForm* orderFormHead);//保存订单数据

struct menu* readOrderFormFile(struct orderForm* orderFormHead);//读取订单文件内容

void showMenuSale(struct menu* head);//统计分析中的菜品显示

void showFormInfo(struct orderForm* orderFormHead, struct menu* menuHead, struct date inputDate);//统计分析中的订单显示