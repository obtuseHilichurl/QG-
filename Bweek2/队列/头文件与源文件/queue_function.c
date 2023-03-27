#include "linkqueue.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void initQueue(Queue* Q, int elemSize, int size)
{
	if (Q == NULL || size == 0 || elemSize == 0)
		return;
	Q->elemSize = elemSize;
	Q->Len = size;
	Q->count = 0;
	Node* p1= (Node*)malloc(sizeof(Node));
	Q->headPtr =Q->tailPtr= p1;
	for (int i = 1; i < size; i++)
	{
		p1 = (Node*)malloc(sizeof(Node));
		Q->tailPtr->next = p1;
		Q->tailPtr = p1;
	}
	Q->tailPtr->next = Q->headPtr;
	Q->tailPtr = Q->headPtr;
}
void destoryQueue(Queue* Q)
{
	if (Q == NULL || Q->Len==0)
	{
		free(Q);
		return;
	}
	Node* p=Q->headPtr->next;
	Q->headPtr->next == NULL;
	Q->headPtr = p->next;
	while (Q->headPtr != NULL)
	{
		free(p);
		p=Q->headPtr;
		Q->headPtr = Q->headPtr->next;
	}
	free(p);
	free(Q);
}
void enQueue(Queue* Q,void* base,int elemSize)
{
	if (Q == NULL || Q->Len == Q->count)
		return;
	Q->count++;
	memcpy(&Q->headPtr->data, base, elemSize);
	Q->headPtr = Q->headPtr->next;
}
void deQueue(Queue* Q)
{
	if (Q == NULL || Q->Len == 0)
		return;
	Q->count--;
	Node* p = Q->tailPtr;
	while (p->next != Q->headPtr)
	{
		p = p->next;
	}
	Q->headPtr = p;
}
void clearQueue(Queue* Q)
{
	if (Q == NULL || Q->Len == -1||Q->Len==0)
		return;
	Node* p = Q->headPtr->next;
	Q->headPtr->next == NULL;
	Q->headPtr = p->next;
	while (Q->headPtr != NULL)
	{
		free(p);
		p = Q->headPtr;
		Q->headPtr = Q->headPtr->next;
	}
	free(p);
}
Queue* getQueueHead(Queue* Q)
{
	if (Q == NULL || Q->Len == 0)
		return NULL;
	else
		return Q->headPtr;
}
int isFullQueue(Queue* Q)
{
	if (Q == NULL)
		return -1;
	return Q->count == Q->Len ? 1 : 0;
}
int isEmptyQueue(Queue* Q)
{
	if (Q == NULL)
		return -1;
	return Q->count == 0 ? 1 : 0;
}
int lengthQueue(Queue* Q)
{
	if (Q == NULL)
		return -1;
	return Q->Len;
}
void traverseQueue(Queue* Q, Node* p)//不知道遍历后要干嘛,在网上搜了也不太明白,暂时不写了
{
	;//
}
