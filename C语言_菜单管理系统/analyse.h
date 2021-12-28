#pragma once
//按销量排序
void sortBySales(struct menu* menuHead);

//按净收入排序
void sortByIncome(struct menu* menuHead);

//菜品销售统计
void menuSaleAnalyse(struct orderForm* orderFormHead, struct menu* menuHead);

//将菜品中的日销量和日净利润清0
void clearSalesAndIncome(struct menu* menuHead);

//计算所有订单的总价
void calculatePrice(struct orderForm* orderFormHead, struct menu* menuHead);

//将所有订单中的sumPrice清0
void clearSumPrice(struct orderForm* orderFormHead);

//按订单总价排序
void sortBySumPrice(struct orderForm* orderFormHead);

//按订单就餐人数排序
void sortByPeople(struct orderForm* orderFormHead);

//订单统计
void orderFormAnalyse(struct orderForm* orderFormHead, struct menu* menuHead);
