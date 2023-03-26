#include"calculation.h"
#include <stdio.h>
#include <stdlib.h>
int initStack(S* stack)
{
	if (stack == NULL)
	{
		printf("fail to init");
		return 0;
	}
	stack->count = 0;
	stack->top = NULL;
	return 1;
}
int isEmptyStack(S* stack)
{
	return stack->top == NULL ? 1:0;
}
N* getTopStack(S* stack)
{
	if (stack == NULL || stack->top == NULL)
		return NULL;
	return stack->top;
}
int clearStack(S* stack)
{
	N* p;
	if (stack == NULL)
		return 1;
	while (stack->top != NULL)
	{
		p = stack->top->next;
		free(stack->top);
		stack->top = p;
	}
	stack->count = 0;
	return 1;
}
int pushStack(S* stack, N* node)
{
	if (stack == NULL)
		return 0;
	stack->count++;
	if (stack->top != NULL)
	{
		node->next = stack->top;
		stack->top = node;
		return 1;
	}
	stack->top = node;
	node->next = NULL;
	return 1;
}
float popStack(S* stack)
{
	float value=0;
	if (stack == NULL || stack->count==0)
		return 0;
	value = stack->top->value;
	stack->count--;
	N* p;
	p = stack->top->next;
	free(stack->top);
	stack->top = p;
	return value;
}