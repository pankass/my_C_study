#pragma once
struct menu* queryMenu(struct menu* head, struct menu** oldNode);//查询菜品

struct menu* addMenu(struct menu* head);//添加

struct menu* deleteMenu(struct menu* head);//删除菜品

struct menu* changeMenu(struct menu* head);//修改菜品

int ifRepeatMenu(struct menu* head, int foodNum, char* foodName, int select);//判断是否菜号或菜名重复

void sortByNum(struct menu* menuHead);//将菜品按照菜号排好序排序
