#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include "linkqueue.h"
//写的是链式存储的环形泛型队列，但是静态分配
int main()
{
	int flag,queueLength=0,type=0;
	Queue queue;
	queue.Len = -1;
r3:
	while (1)
	{
		flag = menu();
		switch (flag)
		{
		case 1:
		{
			if (queue.Len == -1)
			{
			r2:
				system("cls");
				printf("最大元素个数:");
				scanf("%d", &queueLength);
				printf("\n元素类型:");
				printf("1:int 2:float 3:char\n");
				scanf("%d", &type);
				switch (type)
				{
				case 1:
					initQueue(&queue, sizeof(int), queueLength);
					break;
				case 2:
					initQueue(&queue, sizeof(float), queueLength);
					break;
				case 3:
					initQueue(&queue, 30*sizeof(char), queueLength);
					break;
				default:
					goto r2;
				}
			}
			else
				printf("已初始化过");
			Sleep(1000);
			break;
		}
		case 2:
		{
			if (queue.Len == -1)
				printf("请初始化");
			else if (isEmptyQueue(&queue) == 0)
				deQueue(&queue);
			else
				printf("原本为空！");
			Sleep(1000);
			break;
		}
		case 3:
		{
			if (type == 0)
				printf("请先初始化");
			else
			{ 
				printf("输入数据:");
				switch (type)
				{
				case 1:
				{
					int data;
					scanf("%d", &data);
					enQueue(&queue,&data,sizeof(int));
					break;
				}
				case 2:
				{
					float data;
					scanf("%f", &data);
					enQueue(&queue, &data,sizeof(float));
					break;
				}
				case 3:
				{
					char data[31];
					scanf("%s",&data);
					enQueue(&queue, &data,strlen(data)+1);
					break;
				}
				default:
					exit(114514);
				}
			}
			Sleep(1000);
			break;
		}
		case 4:
		{
			if (queue.Len == -1)
				printf("请初始化");
			else if (queue.count == 0)
				printf("NULL");
			else {
				Node* ptr = queue.tailPtr;
				while (ptr != queue.headPtr)
				{
					switch (type)
					{
					case 1:
						printf("%d->", ptr->data);
						break;
					case 2:
						printf("%f->", ptr->data);
						break;
					case 3:
						printf("%s->", &ptr->data);
						break;
					}
					ptr = ptr->next;
				}
			}
			Sleep(1000);
			break;
		}
		case 5:
		{
			clearQueue(&queue);
			Sleep(1000);
			break;
		}
		case 6:
			exit(0);
		default:
			goto r3;
		}
	}
	return 0;
}
int menu()
{
	int flag;
	r1:
	system("cls");
	system("mode con Cols=30 Lines=20");
	printf("     1:   初始化队列\n");
	printf("     2:   排出队列尾\n");
	printf("     3:   加入新成员\n");
	printf("     4:   查看全队列\n");
	printf("     5:   清空本队列\n");
	printf("     6:      退出\n");
	printf("请输入:       ");
	scanf("%d", &flag);
	if (flag !=1&& flag!=2&&flag != 3 && flag != 4&&flag != 5 && flag != 6)
		goto r1;
	return flag;
}