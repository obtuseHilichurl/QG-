typedef struct node
{
	float value;
	struct node* next;
}N;
typedef struct stack
{
	N* top;
	int count;
}S;
int initStack(S* stack);
int isEmptyStack(S* stack);
N* getTopStack(S* stack);
int clearStack(S* stack);
int pushStack(S* stack, N* node);
float popStack(S* stack);
int priority(char sign);