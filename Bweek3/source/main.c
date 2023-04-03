#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include "head.h"

//test:
//int main()
//{
//	int arr[10] = { 7,-24,75,4,0,223,-5,-22,1 ,-1};
//	FILE* fp;
//	if ((fp = fopen("test.txt", "wb")) == NULL)
//	{
//		printf("file open is error\n");
//		exit(0);
//	}
//	fwrite(arr, sizeof(int), 10, fp);
//	return 0;
//}

//随机生成数据的函数
//int main()
//{
//	FILE* fp;
//	int size = 100, seq=0;
//	int* arr = (int*)malloc(sizeof(int) * size);
//	srand(time(NULL) + seq++);
//	rand(); // 先取一次，第一个数看起来有些伪随机
//	for (int i = 0; i < size; i++)
//	{
//		arr[i] = (rand() % 19999) - 9999;
//	}
//	if ((fp = fopen("hundred.txt", "wb")) == NULL)
//	{
//		printf("file open is error\n");
//		exit(0);
//	}
//	fwrite(arr, sizeof(int), size, fp);
//	return 0;
//}

int main()  // 单次大数据计时
{
clock_t start,end; 
	FILE* fp=NULL;
	int flag = -1,size=10,loc=0,*arr=NULL;
r1:
	system("cls");
	printf("选择模式:\n");
	printf("1：10000数据 2：50000数据  3：200000数据 4：10数据小测试\n");
	scanf("%d", &flag);
	switch (flag)
	{
	case 1:
		size = 10000;
		arr = (int*)malloc(sizeof(int) * size);
		fp = fopen("tenThousand.txt", "rb");
		fread(arr, sizeof(int), size, fp);
		break;
	case 2:
		size = 50000;
		arr = (int*)malloc(sizeof(int) * size);
		fp = fopen("fiftyThousand.txt", "rb");
		fread(arr, sizeof(int), size, fp);
		break;
	case 3:
		size = 200000;
		arr = (int*)malloc(sizeof(int) * size);
		fp = fopen("twoHundredThousand.txt", "rb");
		fread(arr, sizeof(int), size, fp);
		break;
	case 4:
		size = 10;
		arr = (int*)malloc(sizeof(int) * size);
		fp = fopen("test.txt", "rb");
		fread(arr, sizeof(int), size, fp);
		break;
	default:
		goto r1;
	}
	flag = -1;
	if (fp == NULL)
	{
		printf("file open is error\n");
		exit(0);
	}
	flag = menu();

	start = clock();
	switch (flag)
	{
	case 1:
		insertSort(arr, size);
		end = clock();
		break;
	case 2:
		mergeSort(arr, size);
		end = clock();
		break;
	case 3:
		quickSort(arr,0, size -1);
		end = clock();
		break;
	case 4:
		countSort(arr, size);
		end = clock();
		break;
	case 5:
		radixCountSort(arr, size);
		end = clock();
		break;
	case 6:
		end = clock();
		system("cls");
		printf("(没有健壮性，别闹求求辣)一共%d个数，求第几小(不进行计时):>>", size);
		scanf("%d", &loc);
		if (loc > size)
			exit(555);
		findData(arr, size,loc-1);
		printf("\n%d\n", arr[loc - 1]);
		break;
	case 7:
		end = clock();
		colorSort(arr, size);
		printf("不进行计时\n");
		break;
	default:
		break;	
	}
	for (int i = 0; i < size; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\ntime = %f ms(%f s)\n",(double)(end-start), (double)(end - start)/CLK_TCK);
	free(arr);
	fclose(fp);
	return 0;
}

//int main()  // 小数据多次计时
//{
//	clock_t start, end;
//	FILE* fp = NULL;
//	int flag = -1, size = 100, loc = 0, * arr = NULL,*t=NULL, timessss = 1, timeflag = 0;
//	system("cls");
//		arr = (int*)malloc(sizeof(int) * size);
//		t = (int*)malloc(sizeof(int) * size);
//		fp = fopen("hundred.txt", "rb");
//		fread(arr, sizeof(int), size, fp);
//	if (fp == NULL)
//	{
//		printf("file open is error\n");
//		exit(0);
//	}
//	flag = menu();
//	start = clock();
//	for (int f=0; f < 100000; f++)
//	{
//		memcpy(t, arr, sizeof(int) * size);
//		switch (flag)
//		{
//		case 1:
//			insertSort(t, size);
//			break;
//		case 2:
//			mergeSort(t, size);
//			break;
//		case 3:
//			quickSort(t, 0, size - 1);
//			break;
//		case 4:
//			countSort(t, size);
//			break;
//		case 5:
//			radixCountSort(t, size);
//			break;
//		case 6:
//		case 7:
//			printf("不进行计时");
//			exit(114514);
//			break;
//		default:
//			break;
//		}
//	}
//	end = clock();
//	for (int i = 0; i < size; i++)
//	{
//		printf("%d ", t[i]);
//	}
//	printf("\ntime = %f ms(%f s)\n", (double)(end - start), (double)(end - start) / CLK_TCK);
//	free(arr);
//	free(t);
//	fclose(fp);
//	return 0;
//}

int menu()
{
	int choose = -1;
r0:
	system("cls");
	printf("1:insertSort 2:mergeSort 3:quickSort 4:countSort 5:radixCountSort 6:findData 7:colorSort 8:exit\n");
	scanf("%d", &choose);
	switch (choose)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		return choose;
	case 8:
		exit(8);
	default:
		printf("输入错误！\n");
		Sleep(1000);
		goto r0;
	}
}
void swapInt(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
	return;
}
