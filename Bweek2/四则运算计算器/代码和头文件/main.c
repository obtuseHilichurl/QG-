#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include "calculation.h"
//��ѽ���ź�����bug���鷳
int main()
{
	float value=0,num1,num2, flag = 0;
	int i = 0;
	BOOL isPoint=0, isSign=0;//isPointΪ1��������'.' isSignΪ1���������������
	char arr[1001] = { 0 };
	S num_stack,sign_stack;
	N* p1=NULL;
	initStack(&num_stack);
	initStack(&sign_stack);
	system("mode con cols=40 lines=20");
	printf("������׺���ʽ(��=��β,��Ҫ����ո�)\n:");
	scanf("%s", arr);
	{//���,�ı����
		int l=0, r=0;
		for (int j = 0; j <= 1000; j++)
		{
			if (arr[j] != '*' && arr[j] != '-' && arr[j] != '+' && arr[j] != '/' && arr[j] != '.'&&(arr[j]>'9'||arr[j]<'0'))
			{
				if (arr[j] == 'x' || arr[j] == 'X')
					arr[j] = '*';
				else if (arr[j] == '��' || arr[j] == ':')
					arr[j] = '/';
				else if (arr[j] == '(')
					l++;
				else if (arr[j] == ')')
					r++;
				else if (arr[j] == '=')
					flag++;
			}
		}
		for (int j = 0; j < 1001; j++)
		{
			if ((arr[j] <= 'z' && arr[j] >= 'a') || (arr[j] <= 'Z' && arr[j] >= 'A'))
				exit(1919810);
			if ((arr[j] >= '!' && arr[j] <= '&') || arr[j] == '<' || arr[j] == '>' || arr[j] == '?' || arr[j] == '^')
			{
				printf(">_<");
				exit(0);
			}
		}
		if (l != r)
		{
			printf("��ʽ����\n");
			exit(0);
		}
		if (!flag)
		{
			printf("������Ⱥţ�");
			exit(0);
		}
		if(flag>1)
		{
			printf("�Ⱥ�̫����\n");
			exit(0);
		}
	}
	
	if (arr[0] == '-')//��ǰ�жϷ���λ
	{
		p1 = (N*)malloc(sizeof(N));
		p1->value = 0;
		pushStack(&num_stack, p1);
		p1 = (N*)malloc(sizeof(N));
		p1->value = '-';
		pushStack(&sign_stack, p1);
		i++;
	}
	while(arr[i]!='='||isEmptyStack(&sign_stack) == 0)
	{
		if (i == 1000)
			break;
		if (isPoint == 0 && arr[i] == '.')//�ж�С����
		{
			isPoint = 1;
			flag = 0.1;
			i++;
			continue;
		}
		if (arr[i] <= '9' && arr[i] >= '0')
		{
			if(isPoint==0)
				value=value*10+arr[i]-'0';
			if (isPoint)
			{
				value += (arr[i] - '0') * flag;
				flag /= 10;
			}
			if ((arr[i + 1] < '0' || arr[i + 1]>'9')&&arr[i+1]!='.')
			{
				p1 = (N*)malloc(sizeof(N));
				p1->value = value;
				value = 0;
				pushStack(&num_stack, p1);
				flag = 0,isSign = 0;
			}
			i++;
			continue;
		}
		if (arr[i] == '+' || arr[i] == '-' || arr[i] == '*' || arr[i] == '/' || arr[i] == '(' || arr[i] == ')'||arr[i]=='=')
		{
			if (arr[i] == ')')
				isSign = 0;
			if(arr[i]=='+'||arr[i]=='-'||arr[i]=='*'||arr[i]=='/')
			{
				if (isSign)
				{
					printf("���������Ŷ\n");
					exit(0);
				}
				else
					isSign = 1;
			}
			isPoint = 0;
			p1 = (N*)malloc(sizeof(N));
			p1->value = arr[i];
			if (isEmptyStack(&sign_stack)||priority(arr[i])>priority(getTopStack(&sign_stack)->value)||(getTopStack(&sign_stack)->value=='('&&arr[i]!=')'&&arr[i]!='='))
			{
				pushStack(&sign_stack, p1);
				i++;
				continue;
			}
			if (getTopStack(&sign_stack)->value== '(' && arr[i] == ')')
			{
				popStack(&sign_stack);
				i++;
				continue;
			}
			if (priority(arr[i]) <= priority(getTopStack(&sign_stack)->value) || arr[i] == ')'&&getTopStack(&sign_stack)->value!='('||arr[i]=='='&&isEmptyStack(&sign_stack)==0)
			{
				isSign = 0;
				switch ((char)popStack(&sign_stack))
				{
				case '+':
				{
					num1 = popStack(&num_stack);
					num2 = popStack(&num_stack);
					p1 = (N*)malloc(sizeof(N));
					p1->value = num1 + num2;
					pushStack(&num_stack, p1);
					break;
				}
				case '-':
				{
					num1 = popStack(&num_stack);
					num2 = popStack(&num_stack);
					p1 = (N*)malloc(sizeof(N));
					p1->value = num2 - num1;
					pushStack(&num_stack, p1);
					break;
				}
				case '*':
				{
					num1 = popStack(&num_stack);
					num2 = popStack(&num_stack);
					p1 = (N*)malloc(sizeof(N));
					p1->value = num1 * num2;
					pushStack(&num_stack, p1);
					break;
				}
				case '/':
				{
					num1 = popStack(&num_stack);
					num2 = popStack(&num_stack);
					p1 = (N*)malloc(sizeof(N));
					p1->value = num2 / num1;
					pushStack(&num_stack, p1);
					break;
				}
				default:
					break;
				}
			}
		}
	}
	if ((arr[i - 1] < '0' || arr[i - 1]>'9') && arr[i - 1] != ')')
	{
		printf("������񲻶���\n");
		exit(0);
	}
	printf("%f",popStack(&num_stack));
	return 0;
}

int priority(char sign)
{
	switch (sign)
	{
	  case '(':
		  return 3;
	  case '/':
	  case '*':
		  return 2;
	  case '+':
	  case '-':
		  return 1;
	  default:
		  return 0;
	}
}

