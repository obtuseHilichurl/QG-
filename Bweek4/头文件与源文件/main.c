#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include "binary_tree.h"

//这是文件里边的存数值
//int main()
//{
//	int arr[11] = { 7,-24,75,4,0,223,-5,-22,1 ,-1,-25};
//	FILE* fp;
//	if ((fp = fopen("data.txt", "wb")) == NULL)
//	{
//		printf("file open is error\n");
//		exit(0);
//	}
//	fwrite(arr, sizeof(int), 11, fp);
//	return 0;
//}

int main()
{
	system("mode con cols=70 lines=30");
	menu();
	return 0;
}

void menu()
{
	int flag = -1,value;
	N* p;
	T tree;
	init_binary_tree(&tree);
	system("cls");
	printf("			  \33[34;43m菜 单\33[0m\n");
	printf("0  - > 层序遍历\n");
	printf("1  - >   查找\n");
	printf("2  - >   插入\n");
	printf("3  - >   删除\n");
	printf("4  - > 先序打印\n");
	printf("5  - > 中序打印\n");
	printf("6  - > 后序打印\n");
	printf("7  - > 先序递归\n");
	printf("8  - > 中序递归\n");
	printf("9  - > 后序递归\n");
	printf("10 - >   退出");
	while(1)
	{
		printf("\n请选择: ");
		scanf("%d", &flag);
		while (flag > 10 || flag < 0)
		{
			printf("输入不合法！\n");
			printf("请选择: ");
			scanf("%d", &flag);
		}
		switch (flag)
		{
		case 0:
			level_traversal(&tree);
			break;
		case 1:
			printf("输入查找节点的值:");
			scanf("%d", &value);
			p = find_tree(tree.ancestor, value);
			if (p != NULL)
				printf("节点 地址: %x 值: %d 左儿: %x 右儿: %x", p, p->value, p->left, p->right);
			break;
		case 2:
			printf("输入插入的数值:");
			p = (N*)malloc(sizeof(N));
			scanf("%d", &p->value);
			if (insert_tree(tree.ancestor, p->value) == 1)
				tree.count++;
			break;
		case 3:
			printf("输入删除节点的值:");
			scanf("%d", &value);
			delete_tree(&tree, value);
			break;
		case 4:
			preorder_traversal(&tree);
			break;
		case 5:
			inorder_traversal(&tree);
			break;
		case 6:
			postorder_traversal(&tree);
			break;
		case 7:
			preorder_traversal_re(tree.ancestor);
			break;
		case 8:
			inorder_traversal_re(tree.ancestor);
			break;
		case 9:
			postorder_traversal_re(tree.ancestor);
			break;
		case 10:
			exit(1);
		default:
			printf("NO！！！");
			exit(1);
		}
	}
}
