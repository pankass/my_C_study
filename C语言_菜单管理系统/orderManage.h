#pragma once
//查询订单
void queryOrderForm(struct orderForm* orderFormHead,struct menu* menuHead);

//添加订单
struct orderForm* addOrderForm(struct orderForm* orderFormHead, struct menu* menuHead);

//删除订单
struct orderForm* deleteOrderForm(struct orderForm* orderFormHead, struct menu* menuHead);

//修改订单
struct orderForm* changeOrderForm(struct orderForm* orderFormHead, struct menu* menuHead);

//对菜单的简单查询
struct menu* searchMenu(struct menu* menuHead, int foodNum);

//订单号查重
int ifRepeatOrder(struct orderForm* orderFormHead, int orderNum);