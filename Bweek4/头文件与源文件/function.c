#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include "binary_tree.h"

void init_binary_tree(T* tree)  // 初始化排序树
{
	tree->count = 0;
	tree->ancestor = (N*)malloc(sizeof(N));
	tree->ancestor->left = NULL;
	tree->ancestor->right = NULL;

	int temp;
	FILE* fp = NULL;
	if ((fp = fopen("data.txt", "rb")) == NULL)
	{
		printf("file open is error\n");
		exit(0);
	}
	fread(&tree->ancestor->value, sizeof(int), 1, fp);
	tree->count++;
	while (!feof(fp))
	{
		fread(&temp, sizeof(int), 1, fp);
		insert_tree(tree->ancestor, temp);
		tree->count++;
	}
}

int insert_tree(N* node, int value)
{
	if (value == node->value)
	{
		printf("插入失败!");
		return 0;
	}
	if (value > node->value)
	{
		if (node->right == NULL)
		{
			N* p = (N*)malloc(sizeof(N));
			node->right = p;
			p->left = p->right = NULL;
			p->value = value;
			printf("插入成功!");
		}
		else
			insert_tree(node->right, value);
		return 1;
	}
	if (value < node->value)
	{
		if (node->left== NULL)
		{
			N* p = (N*)malloc(sizeof(N));
			node->left = p;
			p->left = p->right = NULL;
			p->value = value;
			printf("插入成功!");
		}
		else
			insert_tree(node->left, value);
		return 1;
	}
}

N* find_tree(N* node, int value)
{
	if (value > node->value)
	{
		if (node->right == NULL)
		{
			printf("查找失败！");
			return NULL;
		}
		else
			return find_tree(node->right, value);
	}
	if (value < node->value)
	{
		if (node->left == NULL)
		{
			printf("查找失败！");
			return NULL;
		}
		else
			return find_tree(node->left, value);
	}
	if (value == node->value)
	{
		return node;
	}
}

N* find_front(N* p)
{
	if (p->right != NULL)
		return find_front(p->right);
	return p;
}

N* find_post(N* p)
{
	if (p->left != NULL)
		return find_post(p->left);
	return p;
}

N* find_dad(N* p0, N* pt)
{
	if (p0 == pt)
		return NULL;
	if (p0->left == pt || p0->right == pt)
		return p0;
	if (p0->value > pt->value)
		return find_dad(p0->left, pt);
	return find_dad(p0->right, pt);
}

void delete_tree(T* tree,int value)
{
	N* p = find_tree(tree->ancestor,value);
	if (p == NULL)
	{
		printf("删除失败!");
		return;
	}
	if (p == tree->ancestor)
	{
		if (p->right != NULL)
		{
			N* d = find_post(p->right);
			p->value = d->value;
			N* dad = find_dad(p,d);
			if (dad->right == d)
				dad->right = d->right;
			else
				dad->left = d->right;
			free(d);
			tree->count--;
			return;
		}
		if (p->left != NULL)
		{
			N* d = find_front(p->left);
			p->value = d->value;
			N* dad = find_dad(p, d);
			if (dad->left == d)
				dad->left = d->left;
			else
				dad->right = d->left;
			free(d);
			tree->count--;
			return;
		}
		tree->ancestor = NULL;
		tree->count = 0;
		return;	
	}
	N* d = NULL;
	N* dad = find_dad(tree->ancestor, p);
	if (p->right != NULL)
	{
		d = find_post(p->right);
		p->value = d->value;
		dad = find_dad(p, d);
		if (dad->right == d)
			dad->right = d->right;
		else
			dad->left = d->right;
		free(d);
		tree->count--;
		return;
	}
	if (p->left != NULL)
	{
		d = find_front(p->left);
		p->value = d->value;
		dad = find_dad(p, d);
		if (dad->left == d)
			dad->left = d->left;
		else
			dad->right = d->left;
		free(d);
		tree->count--;
		return;
	}
	if (dad->left == p)
		dad->left = NULL;
	else
		dad->right = NULL;
	tree->count--;
	return;
}

void preorder_traversal_re(N* node)
{
	if (node == NULL)
		return;
	printf("%d ", node->value);
	preorder_traversal_re(node->left);
	preorder_traversal_re(node->right);
	return;
}

void inorder_traversal_re(N* node)
{
	if (node == NULL)
		return;
	inorder_traversal_re(node->left);
	printf("%d ", node->value);
	inorder_traversal_re(node->right);
	return;
}

void postorder_traversal_re(N* node)
{
	if (node == NULL)
		return;
	postorder_traversal_re(node->left);
	postorder_traversal_re(node->right);
	printf("%d ", node->value);
	return;
}

void preorder_traversal(T* tree)
{
	int size = 10,tep=-1,flag=0;//flag 标志是否处于撤退状态
	N** arr = (N**)malloc(tree->count * sizeof(N*));  // stack
	N* p = tree->ancestor;
	do
	{
		if (flag == 1)
		{
			if (p == arr[tep]->left)
			{
				if (arr[tep]->right == NULL)
				{
					p = arr[tep--];
					continue;
				}
				else
				{
					p = arr[tep]->right;
					flag = 0;
					continue;
				}
			}
			if (p == arr[tep]->right)
			{
				p = arr[tep--];
				continue;
			}
		}
		printf("%d ", p->value);
		if (p->left != NULL)
		{
			arr[++tep] = p;
			p = p->left;
			continue;
		}
		if (p->right != NULL)
		{
			arr[++tep] = p;
			p = p->right;
			continue;
		}
		flag=1;
	} while (tep!=-1);
	free(arr);
}

void inorder_traversal(T* tree)
{
	int size = 10, tep = -1, flag = 0;//flag 标志是否处于撤退状态
	N** arr = (N**)malloc(tree->count * sizeof(N*));  // stack
	N* p = tree->ancestor;
	do
	{
		if (flag == 1)
		{
			if (p == arr[tep]->left)
			{
				if (arr[tep]->right == NULL)
				{
					p = arr[tep--];
					printf("%d ", p->value);
					continue;
				}
				else
				{
					p = arr[tep]->right;
					printf("%d ",arr[tep]->value);
					flag = 0;
					continue;
				}
			}
			if (p == arr[tep]->right)
			{
				p = arr[tep--];
				continue;
			}
		}
		if (p->left != NULL)
		{
			arr[++tep] = p;
			p = p->left;
			continue;
		}
		printf("%d ", p->value);
		if (p->right != NULL)
		{
			arr[++tep] = p;
			p = p->right;
			continue;
		}
		flag = 1;
	} while (tep != -1);
	free(arr);
}

void postorder_traversal(T* tree)
{
	int size = 10, tep = -1, flag = 0;//flag 标志是否处于撤退状态
	N** arr = (N**)malloc(tree->count * sizeof(N*));  // stack
	N* p = tree->ancestor;
	do
	{
		if (flag == 1)
		{
			if (p == arr[tep]->left)
			{
				if (arr[tep]->right == NULL)
				{
					p = arr[tep--];
					printf("%d ", p->value);
					continue;
				}
				else
				{
					p = arr[tep]->right;
					flag = 0;
					continue;
				}
			}
			if (p == arr[tep]->right)
			{
				p = arr[tep--];
				printf("%d ", p->value);
				continue;
			}
		}
		if (p->left != NULL)
		{
			arr[++tep] = p;
			p = p->left;
			continue;
		}
		if (p->right != NULL)
		{
			arr[++tep] = p;
			p = p->right;
			continue;
		}
		printf("%d ", p->value);
		flag = 1;
	} while (tep != -1);
	free(arr);
}

void level_traversal(T* tree)
{
	N* p = tree->ancestor;
	N* arr[10];
	int head = 0, tail = 0;
	if (p)
	{
		tail = (tail + 1) % 10;
		arr[tail] = p;
	}
	while(head!=tail)
	{
		head = (head + 1) % 10;
		p = arr[head];
		printf("%d ", p->value);
		if (p->left != NULL)
		{
			tail = (tail + 1) % 10;
			arr[tail] = p->left;
		}
		if (p->right != NULL)
		{
			tail = (tail + 1) % 10;
			arr[tail] = p->right;
		}
	}

	return;
}

