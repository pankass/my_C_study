#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct student
{
	int studentNum;
	char name[20];
	int che;
	int math;
	int eng;
	int sum;
	struct student* next;
}STUDENT;

STUDENT list;

STUDENT* last = &list;

void saveStudent(STUDENT*);
void paintMenu();
void getFileData(STUDENT*);
void studetSum(STUDENT*);
void addStudent(STUDENT*);
void searchBynum(STUDENT*);
void searchByname(STUDENT*);
void searchStudent(STUDENT*);
void deleteStudent();
void fixStudent();
void printAll(STUDENT*);

void paintMenu()
{
	printf("----------成绩管理系统-------------\n");
	printf("----------作者：PI---------------\n");
	printf("----------1.添加学生信息-----------\n");
	printf("----------2.删除学生信息-----------\n");
	printf("----------3.更改学生信息-----------\n");
	printf("----------4.查找学生信息-----------\n");
	printf("----------5.打印所有学生信息-------\n");
	printf("----------6.退出系统--------------\n");
	printf("-----请输入您要实现的功能号码------\n");
}

void saveStudent(STUDENT* head)//遍历整个链表写入文件
{
	STUDENT* tmpHead = head->next;
	FILE* fp = fopen("student.txt", "w");
	while (tmpHead != NULL)
	{
		fprintf(fp, "%d\t%s\t%d\t%d\t%d\t%d\n", tmpHead->studentNum, tmpHead->name,
			tmpHead->che, tmpHead->math, tmpHead->eng, tmpHead->sum);
		tmpHead = tmpHead->next;
	}
	fclose(fp);
}

void getFileData(STUDENT* headNode)//尾插法!!!!!!!!!!!!!!!
{
	FILE* fp = NULL;
	fp = fopen("student.txt", "r");//可使用尾插法实现本地数据的读取。。栈区作为临时中介的作用，要操作几个变量就在栈区开辟几个中介。。
	STUDENT stu;
	STUDENT* pstu =	NULL;
	STUDENT* tmpHead = headNode;
	if (fp != NULL)
	{
		while (fscanf(fp, "%d\t%s\t%d\t%d\t%d\t%d\n", &stu.studentNum, &stu.name,
			&stu.che, &stu.math, &stu.eng, &stu.sum) != EOF)
		{
			pstu = (STUDENT*)malloc(sizeof(STUDENT));
			*pstu = stu;
			tmpHead->next = pstu;
			tmpHead = pstu;
			tmpHead->next = NULL;
		}
		fclose(fp);
	}
}
//计算每个学生的总分
void studetSum(STUDENT* head)
{
	STUDENT* stusum = head;
	while (stusum != NULL)
	{
		stusum->sum = stusum->che + stusum->math + stusum->eng;
		stusum = stusum->next;
	}
}
void addStudent(STUDENT* head)//添加学生信息
{//链表的头插法
	int i = 1;
	STUDENT* stu;
	while (i)
	{
		system("cls");
		stu = (STUDENT*)malloc(sizeof(STUDENT));
		printf("请输入学号：");
		scanf("%d", &(stu->studentNum));
		printf("\n请输入姓名：");
		scanf("%s", &(stu->name));
		printf("\n请输入语文成绩：");
		scanf("%d", &(stu->che));
		printf("\n请输入数学成绩：");
		scanf("%d", &(stu->math));
		printf("\n请输入英语成绩：");
		scanf("%d", &(stu->eng));
		//头插法插入链表。。
		stu->next = head->next;
		head->next = stu;
		saveStudent(&list);
		printf("\n学生信息录入成功!\n是否继续？（yes:1/no:0）\n");
		scanf("%d", &i);
	}
}
void searchBynum(STUDENT* head)
{
	printf("请输入学号：");
	int num;
	scanf("%d", &num);
	STUDENT* tmhe = head->next;
	while (true)
	{
		if (tmhe == NULL)
		{
			printf("查无此人！\n");
			system("pause");
			break;
		}
		else if (num == tmhe->studentNum)
		{
			system("cls");
			printf("\n学号\t姓名\t语文\t数学\t英语\t总分\n");
			printf("%d\t%s\t%d\t%d\t%d\t%d\n", tmhe->studentNum,
				tmhe->name, tmhe->che, tmhe->math, tmhe->eng, tmhe->sum);
			system("pause");
			return;
		}
		last = tmhe;
		tmhe = tmhe->next;
	}
}

void searchByname(STUDENT* head)
{
	printf("请输入姓名：");
	STUDENT* tmphe = head->next;
	char putName[20];
	scanf("%s", putName);
	while (strcmp(putName, tmphe->name))//strcmp()比较字符串是否相同，相同返回0
	{
		last = tmphe;
		tmphe = tmphe->next;
		if (tmphe == NULL)
		{
			printf("\n查无此人！\n");
			system("pause");
			break;
		}
	}
	if (tmphe != NULL)
	{
		printf("\n学号\t姓名\t语文\t数学\t英语\t总分\n");
		printf("%d\t%s\t%d\t%d\t%d\t%d\n", tmphe->studentNum,
			tmphe->name, tmphe->che, tmphe->math, tmphe->eng, tmphe->sum);
		system("pause");
	}
}

void searchStudent(STUDENT* head)//遍历链表进行查找。。
{
	int i = 0;
	printf("通过学号查找（1）/通过姓名查找（2）：");
	scanf("%d", &i);
	switch (i)
	{
	case 1:
		searchBynum(&list);
		break;
	case 2:
		searchByname(&list);
		break;
	default:
		printf("\n请按要求输入：\n");
		system("pause");
	}
}

void deleteStudent()//删除学生信息
{
	searchStudent(&list);
	if (last->next != NULL)
	{
		printf("确认删除该生所有信息吗？（yes:1/no:0）\n");
		STUDENT* tmp = NULL;
		int choice = 0;
		scanf("%d", &choice);
		if (choice == 1)
		{
			tmp = last->next;
			last->next = last->next->next;
			free(tmp);
			printf("删除成功！\n");
			system("pause");
		}
		else
		{
			printf("请按规定输入！\n");
		}
	}
}

void fixStudent()
{
	searchStudent(&list);
	int choice = 0;
	int fixNum;
	char fixName[20];
	if (last->next != NULL)
	{
		printf("修改学号(1)\n修改姓名(2)\n修改语文成绩(3)\n修改数学成绩(4)\n修改英语成绩(5)\n");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			printf("修改学号为：");
			scanf("%d", &fixNum);
			last->next->studentNum = fixNum;
			break;
		case 2:
			printf("修改姓名为：");
			scanf("%s", &fixName);
			strcpy(last->next->name, fixName);
			break;
		case 3:
			printf("修改语文成绩为：");
			scanf("%d", &fixNum);
			last->next->che = fixNum;
			break;
		case 4:
			printf("修改数学成绩为：");
			scanf("%d", &fixNum);
			last->next->math = fixNum;
			break;
		case 5:
			printf("修改英语成绩为：");
			scanf("%d", &fixNum);
			last->next->eng = fixNum;
			break;
		default:
			printf("请按规定输入！\n");
			break;
		}
		system("cls");
		studetSum(&list);//计算总分
		printf("修改成功！\n");
		printf("\n学号\t姓名\t语文\t数学\t英语\t总分\n");
		printf("%d\t%s\t%d\t%d\t%d\t%d\n", last->next->studentNum,
			last->next->name, last->next->che, last->next->math,
			last->next->eng, last->next->sum);
		system("pause");
	}
}

void printAll(STUDENT* head)
{
	system("cls");
	STUDENT* tmhe = head->next;
	printf("学号\t姓名\t语文\t数学\t英语\t总分\n");
	while (tmhe != NULL)
	{
		printf("%d\t%s\t%d\t%d\t%d\t%d\n", tmhe->studentNum,
			tmhe->name, tmhe->che, tmhe->math, tmhe->eng, tmhe->sum);
		tmhe = tmhe->next;
	}
	system("pause");
}
int main()
{
	int choice = 0;
	getFileData(&list);//获取本地数据于内存中 ok
	while (1)
	{
		choice = 0;
		system("cls");
		paintMenu();//绘制主菜单栏。。
		printf("请输入需要的功能代号：\n");
		scanf("%d", &choice);
		switch (choice)//1.add  2.delete   3.fix   4.search  5.exit
		{
		case 1:
			addStudent(&list);
			break;
		case 2:
			deleteStudent();
			break;
		case 3:
			fixStudent();
			break;
		case 4:
			searchStudent(&list);
			break;
		case 5:
			printAll(&list);
			break;
		case 6:
			system("cls");
			system("pause");
			printf("感谢您的使用！再见！\n");
			exit(0);
			break;
		default:
			printf("请按照规定输入！\n");
			system("pause");
			break;
		}
		studetSum(&list);//计算总分
		saveStudent(&list);
	}
	system("pause");
	return 0;
}