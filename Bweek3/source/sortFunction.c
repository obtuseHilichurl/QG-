#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include "head.h"
void insertSort(int* arr, int count)  // 暂时是普通插入，有时间就改成希尔
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
	int* tmp = (int*)malloc(sizeof(int) * count);  // 辅助数组
	if (tmp == NULL)
		exit(114);
	assistMergeSort(arr, tmp, 0, count-1);  // 尾下标是count-1嘛
	free(tmp);
}
void assistMergeSort(int *arr, int *tmp, int begin, int end)
{
	if (end - begin<=0)
		return;
	int middle = (begin + end) / 2,b1=begin,b2=middle+1,e1=middle,e2=end;
	assistMergeSort(arr, tmp, b1,e1);
	assistMergeSort(arr, tmp, b2,e2);  // 递归
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
	//先化为非负数,借用了基数排序的思想（没错我最后做计数排序)
	for (int i = 0; i < count; i++)
	{
		a[arr[i]]++;
	}
	//计数
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
		arr[i] -= Min;  // 非正数
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
//我笨比了。看了下别人的，可以只用两个数组（一个临时存放，一个用来一组一组的放数据)（正负数问题可以通过记录负数最大值然后把全元素加为正，排列后再减回去）
//实在是太妙了！但我没时间改了，如果能跑就这样吧。论文还没看呢
//桶使用先进先出（IFIO）的原理是：在个位开始的排序放回原数组后个位大的肯定在个位小的后面，按IFIO的方法可以保证这一位的排序始终成立.
//刚学会用calloc，怕不熟练出错，所以没用
//2023_4_3_20:17 发现大数据会分配失败，没办法只好改了
void findData(int* arr, int count, int loc)  // 返回下标
{
	int datum = 0,tempb=0,tempe=count-1,b=1,e=count-1,restore;//都是指下标
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
	//由于不想生成新数据，我就改变数组的数据为0/1/2来实现吧
	{
		int* temp = (int*)malloc(sizeof(int) * count);  // 由于我的finddata会少量的排序数组，又不能影响原数组，所以我开个新数组
		memcpy(temp , arr , sizeof(int) * count);
		int w1,w2,flag=0;
		findData(temp, count, count * 2 / 3);//还没改完
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
	printf("初始数据（请尽量在test数据内测试）:>");
	Sleep(1000);
	for (int i = 0; i < count; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	Sleep(1000);
	//正式实现
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

