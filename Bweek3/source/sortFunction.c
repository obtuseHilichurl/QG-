#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include "head.h"
void insertSort(int* arr, int count)  // ��ʱ����ͨ���룬��ʱ��͸ĳ�ϣ��
{
	int temp=0;
	for (int i = 1; i < count; i++)
	{
		temp = arr[i];
		for (int j = 0; j < i; j++)
		{
			if (arr[j] > arr[i])
			{
				for (int k = i; k > j; k--)
				{
					arr[k] = arr[k - 1];
				}
				arr[j] = temp;
			}
		}
	}
}

void mergeSort(int* arr, int count)
{
	int* tmp = (int*)malloc(sizeof(int) * count);  // ��������
	if (tmp == NULL)
		exit(114);
	assistMergeSort(arr, tmp, 0, count-1);  // β�±���count-1��
	free(tmp);
}
void assistMergeSort(int *arr, int *tmp, int begin, int end)
{
	if (end - begin<=0)
		return;
	int middle = (begin + end) / 2,b1=begin,b2=middle+1,e1=middle,e2=end;
	assistMergeSort(arr, tmp, b1,e1);
	assistMergeSort(arr, tmp, b2,e2);  // �ݹ�
	int i = begin;
	while (b1 <= e1 && b2 <= e2)
	{
		if (arr[b1] <= arr[b2])
		{
			tmp[i++] = arr[b1++];
		}
		else
		{
			tmp[i++] = arr[b2++];
		}
	}
	while (b1 <= e1)
	{
		tmp[i++] = arr[b1++];
	}
	while (b2 <= e2)
	{
		tmp[i++] = arr[b2++];
	}
	memcpy(arr + begin, tmp + begin, sizeof(int) * (end - begin + 1));
}

void quickSort(int* arr, int begin, int end)
{
	int i = begin + 1, j = end;
	if (begin >= end)
	{
		return;
	}
	if (i==j)
	{
		if (arr[begin] > arr[end])
		{
			swapInt(&arr[end], &arr[begin]);
		}
		return;
	}
	while (i <= j)
	{
		if (arr[i] > arr[begin])
		{
			swapInt(&arr[i], &arr[j]);
			j--;
		}
		else
			i++;
	}
	swapInt(&arr[i-1], &arr[begin]);
	int b1 = begin, b2 = i, e1 = i-2 , e2 = end;
	quickSort(arr, b1, e1);
	quickSort(arr, b2, e2);
	return;
}

void countSort(int* arr, int count)
{
	int Min=0,Max=0;
	for (int i = 0; i < count; i++)
	{
		if (arr[i] < Min)
			Min = arr[i];
		if (arr[i] >= Max)
			Max = arr[i];
	}
	if (Min < 0)
	{
		for (int i = 0; i < count; i++)
		{
			arr[i] -= Min;
		}
	}
	Max -= Min;
	int* a = (int*)malloc(sizeof(int) * (1+Max));
	for (int i = 0; i <= Max; i++)
	{
		a[i]=0;
	}
	//�Ȼ�Ϊ�Ǹ���,�����˻��������˼�루û�����������������)
	for (int i = 0; i < count; i++)
	{
		a[arr[i]]++;
	}
	//����
	for (int i = 0, j = 0; i <= Max;)
	{
		if (a[i] > 0)
		{
			arr[j++] = i;
			a[i]--;
		}
		else
			i++;
	}
	if(Min<0)
		for (int i = 0; i < count; i++)
		{
			arr[i] += Min;
		}
	return;
}

void radixCountSort(int* arr, int count)
{
	int Min = 0,index=0;
	for (int i = 0; i < count; i++)
	{
		if (arr[i] < Min)
			Min = arr[i];
	}
	for (int i = 0; i < count; i++)
	{
		arr[i] -= Min;  // ������
	}
	int* temp = (int*)calloc(count, sizeof(int));
	int* a = (int*)calloc(count, sizeof(int));
	while (1)
	{
		int k = 0, j, z,f=0;
		for (int i = 0; i < 10; i++)
		{
			j = 0, z = 0;
			while (j < count)
			{
				if (((arr[j] / (int)pow(10, index)) % 10) == i)
					a[z++] = arr[j];
				j++;
			}
			if (i == 0 && z == count)
				f = 1;
			for(int n=0;n<z;n++)
				temp[k++] = a[n];
		}
		if (f)
			break;
		while (k > 0)
		{
			arr[count-k] = temp[count - k];
			k--;
		}
		index++;
	}
	for (int i = 0; i < count; i++)
		arr[i] += Min;
	return;
}
//�ұ����ˡ������±��˵ģ�����ֻ���������飨һ����ʱ��ţ�һ������һ��һ��ķ�����)���������������ͨ����¼�������ֵȻ���ȫԪ�ؼ�Ϊ�������к��ټ���ȥ��
//ʵ����̫���ˣ�����ûʱ����ˣ�������ܾ������ɡ����Ļ�û����
//Ͱʹ���Ƚ��ȳ���IFIO����ԭ���ǣ��ڸ�λ��ʼ������Ż�ԭ������λ��Ŀ϶��ڸ�λС�ĺ��棬��IFIO�ķ������Ա�֤��һλ������ʼ�ճ���.
//��ѧ����calloc���²�������������û��
//2023_4_3_20:17 ���ִ����ݻ����ʧ�ܣ�û�취ֻ�ø���
void findData(int* arr, int count, int loc)  // �����±�
{
	int datum = 0,tempb=0,tempe=count-1,b=1,e=count-1,restore;//����ָ�±�
	while (1) 
	{
		while (b <= e)
		{
			if (arr[b] > arr[datum])
			{
				swapInt(&arr[e],&arr[b]);
				e--;
			}
			else
				b++;
		}
		swapInt(&arr[datum], &arr[b - 1]);
		datum = b - 1;
		if (datum == loc)
			return;
		else if (datum < loc)
		{
			e = tempe;
			tempb=datum++;
			b = datum+1;
		}
		else if (datum > loc)
		{
			b = tempb;
			tempe = e = datum-1;
			datum = tempb;
		}
	}
	return ;
}

void colorSort(int* arr, int count)
{
	//���ڲ������������ݣ��Ҿ͸ı����������Ϊ0/1/2��ʵ�ְ�
	{
		int* temp = (int*)malloc(sizeof(int) * count);  // �����ҵ�finddata���������������飬�ֲ���Ӱ��ԭ���飬�����ҿ���������
		memcpy(temp , arr , sizeof(int) * count);
		int w1,w2,flag=0;
		findData(temp, count, count * 2 / 3);//��û����
		findData(temp, count, count / 3);
		w2 = temp[count * 2 / 3];
		w1 = temp[count / 3];
		while (w1 == w2&&flag<count/3)
			w1 = temp[count / 3 - flag++];
		free(temp);
		for (int i = 0; i < count; i++)
		{
			if (arr[i] < w1)
			{
				arr[i] = 0;
				continue;
			}
			if (arr[i] >= w1 && arr[i] <= w2)
			{
				arr[i] = 1;
				continue;
			}
			if (arr[i] > w2)
				arr[i] = 2;
		}
	}
	system("cls");
	printf("��ʼ���ݣ��뾡����test�����ڲ��ԣ�:>");
	Sleep(1000);
	for (int i = 0; i < count; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	Sleep(1000);
	//��ʽʵ��
	int b=0,e=count-1,m=0;
	for(;m<=e;)
	{
		if (arr[m] == 0)
		{
			swapInt(&arr[b++], &arr[m]);
		}
		if (arr[m] == 2)
		{
			swapInt(&arr[e--], &arr[m]);
		}
		if (arr[m] == 1)
		{
			m++;
		}
		if (b > m)
		{
			m = b;
		}
	}
}

