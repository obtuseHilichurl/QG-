typedef struct linkQueueNode
{
	void* data;
	struct linkQueueNode* next;
}Node;
typedef struct linkQueue
{
	Node *headPtr,*tailPtr;
	int elemSize,Len,count;
	
}Queue;
int menu();
void initQueue(Queue* Q, int elemSize, int size);
void traverseQueue(Queue* Q, Node* p);
int lengthQueue(Queue* Q);
int isEmptyQueue(Queue* Q);
int isFullQueue(Queue* Q);
Queue* getQueueHead(Queue* Q);
void clearQueue(Queue* Q);
void deQueue(Queue* Q);
void enQueue(Queue* Q, void* base, int elemSize);
void destoryQueue(Queue* Q);
