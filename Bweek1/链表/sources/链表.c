#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdlib.h>
#include "����.h"

//int main()//�޽�����main����,����ע��
//{
//	//ǰ��:����ô����mallocʧ�ܵ����, ������������ݣ����Լ򵥵�ʹ��1 2 3������
//	system("mode con cols=60 lines=21");//���治����̫��
//	stu* stuhead = NULL,*flag1=NULL;
//	tea* teahead = NULL,*flag2=NULL;
//
//	stuhead = createStu();//����˫��ѭ������
//	system("cls");
//	putStu(stuhead);//�����ѭ������
//	if (isCircleChainListStu(stuhead))//�ж��Ƿ�Ϊѭ������
//		printf("\n��ѭ������\n");
//	else
//		printf("\n����ѭ������\n");
//	flag1=searchCentreNode1(stuhead);//�ҵ������м��㣨����
//	printf("\n%s %s %.2f\n",flag1->name,flag1->number,flag1->score);
//	Sleep(5000);
//	system("cls");
//	stuhead = reverseStuChainList(stuhead);//���ݹ�ص�ת����
//	putStu(stuhead);
//	Sleep(5000);
//	system("cls");
//	teahead = createTea();//������������
//	system("cls");
//	putTea(teahead);//����õ�������
//	if (isCircleChainListTea(teahead))//�ж��Ƿ�Ϊѭ������
//		printf("\n��ѭ������\n");
//	else
//		printf("\n����ѭ������\n");
//	flag2 = searchCentreNode2(teahead);//�ҵ������м��㣨����
//	printf("\n%s %s %s\n", flag2->name, flag2->phonenumber, flag2->subject);
//	Sleep(5000);
//	system("cls");
//  if(teahead!=NULL)
//	if(teahead->next!=NULL)//�������ٺ��������ڵ����ʹ���·�����
//	teahead = reverseTeaChainList(teahead,teahead,teahead->next);//�ݹ�ص�ת����
//	putTea(teahead);
//	Sleep(5000);
//	system("cls");
//	teahead = exchangeOdd_EvenNode(teahead);//������������ż�ڵ㻥��
//	putTea(teahead);//�������������
//	flag2 = searchCentreNode2(teahead);//�ҵ������������м��㣨����
//	printf("\n%s %s %s\n", flag2->name, flag2->phonenumber, flag2->subject);
//	Sleep(5000);
//	system("cls");
//	destoryChainListStu(stuhead);
//	destoryChainListTea(teahead);
//	return 0;
//}

int main()//�н�����main����(��û��ע��)
{
	//ǰ�ԣ���������û��д���뺯����Ҳ���ѣ��������������ݽ�ʹ��һ��
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
				printf("\n������ϣ�׼�����ز˵�\n");
				Sleep(3000);
				menu();
				break;
			}
			case 2:
			{
				system("cls");
				teahead=createTea();
				printf("\n������ϣ�׼�����ز˵�\n");
				Sleep(3000);
				menu();
				break;
			}
			case 3:
			{
				system("cls");
				printf("  ����Ҫ�ж��ĸ�����\n");
				printf("1:ѧ������   2:��ʦ����\n");
				scanf("%d", &flag);
				if (flag == 1)
				{
					if (isCircleChainListStu(stuhead))
						printf("\n��ѭ������\n");
					else
						printf("\n����ѭ������\n");
				}
				else if (flag == 2)
				{
					if (isCircleChainListTea(teahead))
						printf("\n��ѭ������\n");
					else
						printf("\n����ѭ������\n");
				}
				else
				{
					printf("\n�������\n");
				}
				Sleep(3000);
				menu();
				break;
			}
			case 4:
			{
				system("cls");
				printf("  ���뷭ת�ĸ�����\n");
				printf("1:ѧ������  2:��ʦ����\n");
				scanf("%d", &flag);
				if (flag == 1)
				{
					stuhead=reverseStuChainList(stuhead);
					printf("\n��ת��ϣ�׼�����ز˵�\n");
				}
				else if (flag == 2)
				{
					if(teahead!=NULL)
						if(teahead->next!=NULL)
						teahead = reverseTeaChainList(teahead,teahead,teahead->next);
					printf("\n��ת��ϣ�׼�����ز˵�\n");

				}
				else
				{
					printf("\n�������\n");
				}
				Sleep(3000);
				menu();
				break;
			}
			case 5:
			{
				system("cls");
				printf("  ��������ĸ�����\n");
				printf("1:ѧ������  2:��ʦ����\n");
				scanf("%d", &flag);
				if (flag == 1)
				{
					p1=searchCentreNode1(stuhead);
					if (p1 != NULL)
						printf("\n%s %s %.2f\n",p1->name,p1->number,p1->score);
					printf("\n�����ϣ�׼�����ز˵�\n");
				}
				else if (flag == 2)
				{
					p2 = searchCentreNode2(teahead);
					if (p2 != NULL)
						printf("\n%s %s %s\n", p2->name, p2->phonenumber, p2->subject);
					printf("\n�����ϣ�׼�����ز˵�\n");
				}
				else
				{
					printf("\n�������\n");
				}
				Sleep(3000);
				menu();
				break;
			}
			case 6:
			{
				system("cls");
				printf("����Ҫ���ǵ�����ֻ����tea��\n");
				teahead = exchangeOdd_EvenNode(teahead);
				printf("����ɣ�׼�����ز˵�\n");
				Sleep(3000);
				menu();
				break;
			}
			case 7://���������������ַ����أ���5���
			{
				system("cls");
				putStu(stuhead);
				printf("\n5s�󷵻ز˵�\n");
				Sleep(5000);
				menu();
				break;
			}
			case 8:
			{
				system("cls");
				putTea(teahead);
				printf("\n5s�󷵻ز˵�\n");
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