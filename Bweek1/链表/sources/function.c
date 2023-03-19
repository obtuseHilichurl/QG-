#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdlib.h>
#include "����.h"
void menu()
{
	system("cls");
	printf("1������ѧ������\n");
	printf("2�������ʦ����\n");
	printf("3���ж��Ƿ�ɻ�\n");
	printf("4��  ��ת����  \n");
	printf("5���ҵ������е�\n");
	printf("6����������ż\n");
	printf("7�����ѧ������\n");
	printf("8�������ʦ����\n");
	printf("9��    �˳�    \n");
}

stu* createStu()//����˫��ѭ������
{
	stu* p1 = NULL, * p2 = NULL, * head = NULL;//������p1��Ϊ��һ���ڵ�
	printf("����ѧ������ ѧ�� �ĵ㣬������Ϊ�����ƶ�ʱ��������\n");
	head = p1 = p2 = (stu*)malloc(sizeof(stu));
	if (head != NULL)
	{
		head->front = NULL;
		scanf("%s %[0-9] %f", &p2->name, &p2->number, &p2->score);
		while (p2 != NULL && strcmp(p2->name, "�����ƶ�"))
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
tea* createTea()//������������
{
	tea* p1 = NULL, * p2 = NULL, * head = NULL;
	printf("�����ʦ���� �绰 ��Ŀ��������Ϊ����ʱ��������\n");
	head = p1 = p2 = (tea*)malloc(sizeof(tea));
	if (head != NULL)
	{
		scanf("%s %s %s", &p2->name, &p2->phonenumber, &p2->subject);
		while (p2 != NULL && strcmp(p2->name, "����"))
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
	printf("\nѧ������ ѧ�� �ĵ�\n");
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
	printf("\n��ʦ���� �绰 ��Ŀ\n");
	if (p != NULL)
	{
		do
		{
			printf("%s %s %s\n", u->name, u->phonenumber, u->subject);
			u = u->next;
		} while (u != NULL);
	}
}
//������ֵ������ ����ָ��
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
//������ֵ������ ����
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
	if (p == NULL || p->next == NULL)//ȷ���ڵ����2
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
stu* reverseStuChainList(stu* p)//�ǵݹ�,���˫��ѭ������
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
tea* reverseTeaChainList(tea* head, tea* t, tea* tail)//�ݹ飬��Ե�������   headΪԭ��ͷ��tΪtailǰһ���ڵ㣬tailΪ�������Ľ�� ȱ��������Ҫ�������ڵ�
{
	//��ȷ���������ٺ��������ڵ�
	tea* p = tail->next;
	if (head == t)//��ͷʱ��head��next�ÿ�
		head->next = NULL;
	if (p == NULL)//��tail��β���ʱ
	{
		tail->next = t;
		return tail;
	}
	else//��tail����β���ʱ
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