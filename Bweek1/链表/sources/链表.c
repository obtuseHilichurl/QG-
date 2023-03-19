#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdlib.h>
#include "链表.h"

//int main()//无交互的main函数,但有注释
//{
//	//前言:不怎么考虑malloc失败的情况, 对于输入的数据，可以简单的使用1 2 3…代替
//	system("mode con cols=60 lines=21");//界面不想整太大
//	stu* stuhead = NULL,*flag1=NULL;
//	tea* teahead = NULL,*flag2=NULL;
//
//	stuhead = createStu();//创建双向循环链表
//	system("cls");
//	putStu(stuhead);//输出该循环链表
//	if (isCircleChainListStu(stuhead))//判断是否为循环链表
//		printf("\n是循环链表\n");
//	else
//		printf("\n不是循环链表\n");
//	flag1=searchCentreNode1(stuhead);//找到链表中间结点（靠左）
//	printf("\n%s %s %.2f\n",flag1->name,flag1->number,flag1->score);
//	Sleep(5000);
//	system("cls");
//	stuhead = reverseStuChainList(stuhead);//不递归地倒转链表
//	putStu(stuhead);
//	Sleep(5000);
//	system("cls");
//	teahead = createTea();//创建单向链表
//	system("cls");
//	putTea(teahead);//输出该单向链表
//	if (isCircleChainListTea(teahead))//判断是否为循环链表
//		printf("\n是循环链表\n");
//	else
//		printf("\n不是循环链表\n");
//	flag2 = searchCentreNode2(teahead);//找到链表中间结点（靠左）
//	printf("\n%s %s %s\n", flag2->name, flag2->phonenumber, flag2->subject);
//	Sleep(5000);
//	system("cls");
//  if(teahead!=NULL)
//	if(teahead->next!=NULL)//链表至少含有两个节点才能使用下方函数
//	teahead = reverseTeaChainList(teahead,teahead,teahead->next);//递归地倒转链表
//	putTea(teahead);
//	Sleep(5000);
//	system("cls");
//	teahead = exchangeOdd_EvenNode(teahead);//将单向链表奇偶节点互换
//	putTea(teahead);//输出互换后链表
//	flag2 = searchCentreNode2(teahead);//找到互换后链表中间结点（靠左）
//	printf("\n%s %s %s\n", flag2->name, flag2->phonenumber, flag2->subject);
//	Sleep(5000);
//	system("cls");
//	destoryChainListStu(stuhead);
//	destoryChainListTea(teahead);
//	return 0;
//}

int main()//有交互的main函数(但没有注释)
{
	//前言：由于懒，没有写插入函数（也不难），所以输入数据仅使用一次
	system("mode con cols=60 lines=21");
	int flag = 0;
	stu* stuhead = NULL,*p1=NULL;
	tea* teahead = NULL,*p2=NULL;
	menu();
	while (1)
	{
		Sleep(1000);
		scanf("%d", &flag);
		switch(flag)
		{
			case 1:
			{
				system("cls");
				stuhead=createStu();
				printf("\n输入完毕，准备返回菜单\n");
				Sleep(3000);
				menu();
				break;
			}
			case 2:
			{
				system("cls");
				teahead=createTea();
				printf("\n输入完毕，准备返回菜单\n");
				Sleep(3000);
				menu();
				break;
			}
			case 3:
			{
				system("cls");
				printf("  你想要判断哪个链表？\n");
				printf("1:学生链表   2:教师链表\n");
				scanf("%d", &flag);
				if (flag == 1)
				{
					if (isCircleChainListStu(stuhead))
						printf("\n是循环链表\n");
					else
						printf("\n不是循环链表\n");
				}
				else if (flag == 2)
				{
					if (isCircleChainListTea(teahead))
						printf("\n是循环链表\n");
					else
						printf("\n不是循环链表\n");
				}
				else
				{
					printf("\n输入错误\n");
				}
				Sleep(3000);
				menu();
				break;
			}
			case 4:
			{
				system("cls");
				printf("  你想翻转哪个链表？\n");
				printf("1:学生链表  2:教师链表\n");
				scanf("%d", &flag);
				if (flag == 1)
				{
					stuhead=reverseStuChainList(stuhead);
					printf("\n翻转完毕，准备返回菜单\n");
				}
				else if (flag == 2)
				{
					if(teahead!=NULL)
						if(teahead->next!=NULL)
						teahead = reverseTeaChainList(teahead,teahead,teahead->next);
					printf("\n翻转完毕，准备返回菜单\n");

				}
				else
				{
					printf("\n输入错误\n");
				}
				Sleep(3000);
				menu();
				break;
			}
			case 5:
			{
				system("cls");
				printf("  你想查找哪个链表？\n");
				printf("1:学生链表  2:教师链表\n");
				scanf("%d", &flag);
				if (flag == 1)
				{
					p1=searchCentreNode1(stuhead);
					if (p1 != NULL)
						printf("\n%s %s %.2f\n",p1->name,p1->number,p1->score);
					printf("\n输出完毕，准备返回菜单\n");
				}
				else if (flag == 2)
				{
					p2 = searchCentreNode2(teahead);
					if (p2 != NULL)
						printf("\n%s %s %s\n", p2->name, p2->phonenumber, p2->subject);
					printf("\n输出完毕，准备返回菜单\n");
				}
				else
				{
					printf("\n输入错误\n");
				}
				Sleep(3000);
				menu();
				break;
			}
			case 6:
			{
				system("cls");
				printf("由于要求是单链表，只做了tea的\n");
				teahead = exchangeOdd_EvenNode(teahead);
				printf("已完成，准备返回菜单\n");
				Sleep(3000);
				menu();
				break;
			}
			case 7://懒得做输入任意字符返回，就5秒吧
			{
				system("cls");
				putStu(stuhead);
				printf("\n5s后返回菜单\n");
				Sleep(5000);
				menu();
				break;
			}
			case 8:
			{
				system("cls");
				putTea(teahead);
				printf("\n5s后返回菜单\n");
				Sleep(5000);
				menu();
				break;
			}
			case 9:
			{
				destoryChainListStu(stuhead);
				destoryChainListTea(teahead);
				system("cls");
				exit(0);
			}
		}
	}
	
	return 0;
}