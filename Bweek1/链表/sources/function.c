#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdlib.h>
#include "链表.h"
void menu()
{
	system("cls");
	printf("1：输入学生数据\n");
	printf("2：输入教师数据\n");
	printf("3：判断是否成环\n");
	printf("4：  反转链表  \n");
	printf("5：找到链表中点\n");
	printf("6：单链表换奇偶\n");
	printf("7：输出学生链表\n");
	printf("8：输出教师链表\n");
	printf("9：    退出    \n");
}

stu* createStu()//创建双向循环链表
{
	stu* p1 = NULL, * p2 = NULL, * head = NULL;//不妨让p1作为下一个节点
	printf("输入学生姓名 学号 寄点，当姓名为田所浩二时结束输入\n");
	head = p1 = p2 = (stu*)malloc(sizeof(stu));
	if (head != NULL)
	{
		head->front = NULL;
		scanf("%s %[0-9] %f", &p2->name, &p2->number, &p2->score);
		while (p2 != NULL && strcmp(p2->name, "田所浩二"))
		{
			p1 = (stu*)malloc(sizeof(stu));
			p2->next = p1;
			p1->front = p2;
			p2 = p1;
			scanf("%s %s %f", &p2->name, &p2->number, &p2->score);
		}
		p2->next = head;
		head->front = p2;
	}
	return head;
}
tea* createTea()//创建单向链表
{
	tea* p1 = NULL, * p2 = NULL, * head = NULL;
	printf("输入教师姓名 电话 科目，当姓名为马保国时结束输入\n");
	head = p1 = p2 = (tea*)malloc(sizeof(tea));
	if (head != NULL)
	{
		scanf("%s %s %s", &p2->name, &p2->phonenumber, &p2->subject);
		while (p2 != NULL && strcmp(p2->name, "马保国"))
		{
			p1 = (tea*)malloc(sizeof(tea));
			p2->next = p1;
			p2 = p1;
			scanf("%s %[0-9] %s", &p2->name, &p2->phonenumber, &p2->subject);
		}
		p2->next = NULL;
	}
	return head;
}
void putStu(stu* p)
{
	stu* u = p;
	system("cls");
	printf("\n学生姓名 学号 寄点\n");
	if (p != NULL)
	{
		do
		{
			printf("%s %s %.2f\n", u->name, u->number, u->score);
			u = u->next;
		} while (p != u);
	}
}
void putTea(tea* p)
{
	tea* u = p;
	system("cls");
	printf("\n教师姓名 电话 科目\n");
	if (p != NULL)
	{
		do
		{
			printf("%s %s %s\n", u->name, u->phonenumber, u->subject);
			u = u->next;
		} while (u != NULL);
	}
}
//查找中值方法二 快慢指针
stu* searchCentreNode1(stu* p)
{
	if (p == NULL || p->next == NULL)
		return p;
	stu* u1 = p, * u2 = p->next;
	do
	{
		u1 = u1->next;
		u2 = u2->next;
		if (u2->next != p)
			u2 = u2->next;
	} while (u2->next != p);
	return u1;
}
//查找中值方法二 遍历
tea* searchCentreNode2(tea* p)
{
	if (p == NULL || p->next == NULL)
		return p;
	tea* u1 = p;
	int count = 1;
	while (u1 != NULL)
	{
		u1 = u1->next;
		count++;
	}
	count /= 2;
	u1 = p;
	while (count-- > 1)
	{
		u1 = u1->next;
	}
	return u1;
}
tea* exchangeOdd_EvenNode(tea* p)
{
	if (p == NULL || p->next == NULL)//确保节点大于2
		return p;
	tea* u1 = p, * u2 = p->next, * u3 = p;
	p = u2;
	u1->next = u2->next;
	u2->next = u1;
	u2 = u1->next;
	if (u2 != NULL)
	{
		u1 = u2;
		u2 = u2->next;
	}
	while (u1 != NULL && u2 != NULL)
	{
		u3->next = u2;
		u1->next = u2->next;
		u2->next = u1;
		u2 = u1->next;
		u3 = u1;
		if (u2 != NULL)
		{
			u1 = u2;
			u2 = u2->next;
		}

	}
	return p;
}
int isCircleChainListTea(tea* p)
{
	if (p == NULL)
		return 0;
	tea* u1 = p,*u2=p;
	do
	{
		u1 = u1->next;
		u2 = u2->next;
		if (u2 == NULL)
			return 0;
		u2 = u2->next;
	} while (u1 != u2 && u1 != NULL && u2 != NULL);
	if (u1 == u2)
		return 1;
	return 0;
}
int isCircleChainListStu(stu* p)
{
	if (p == NULL)
		return 0;
	stu* u1 = p, * u2 = p;
	do
	{
		u1 = u1->next;
		u2 = u2->next;
		if (u2 == NULL)
			return 0;
		u2 = u2->next;
	} while (u1 != u2 && u1 != NULL && u2 != NULL);
	if (u1 == u2)
		return 1;
	return 0;
}
stu* reverseStuChainList(stu* p)//非递归,针对双向循环链表
{
	if (p == NULL)
		return;
	if (p->next == p)
		return p;
	stu* temp = NULL, * u1 = p, * u2 = p->next;
	do
	{
		temp = u1->next;
		u1->next = u1->front;
		u1->front = temp;
		u1 = u2;
		u2 = u2->next;
	} while (u1 != p);
	return p->next;
}
tea* reverseTeaChainList(tea* head, tea* t, tea* tail)//递归，针对单向链表   head为原表头，t为tail前一个节点，tail为不断向后的结点 缺点是至少要有两个节点
{
	//请确保链表至少含有两个节点
	tea* p = tail->next;
	if (head == t)//开头时将head的next置空
		head->next = NULL;
	if (p == NULL)//当tail是尾结点时
	{
		tail->next = t;
		return tail;
	}
	else//当tail不是尾结点时
	{
		tail->next = t;
		return reverseTeaChainList(head, tail, p);
	}
}
void destoryChainListStu(stu* p)
{
	if (p == NULL)
		return;
	stu* u1 = p->next, * u2 = u1->next;
	while (u1 != p)
	{
		free(u1);
		u1 = u2;
		u2 = u2->next;
	}
	free(p);
}
void destoryChainListTea(tea* p)
{
	if (p == NULL)
		return;
	tea* u1 = p, * u2 = p->next;
	{
		while (u2 != NULL)
		{
			free(u1);
			u1 = u2;
			u2 = u2->next;
		}
		free(u1);
	}
}