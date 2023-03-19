//这是双向：
typedef struct student
{
	char name[16];
	char number[20];
	float score;
	struct student* next;
	struct student* front;
}stu;
//这是单向：
typedef struct teacher
{
	char name[16];
	char phonenumber[16];
	char subject[16];
	struct teacher* next;
}tea;
void menu();
stu* createStu();
tea* createTea();
void putStu(stu* p);
void putTea(tea* p);
stu* searchCentreNode1(stu* p);
tea* searchCentreNode2(tea* p);
tea* exchangeOdd_EvenNode(tea* p);
int isCircleChainListTea(tea* p);
int isCircleChainListStu(stu* p);
stu* reverseStuChainList(stu* p);
tea* reverseTeaChainList(tea* head, tea* t, tea* tail);
void destoryChainListStu(stu* p);
void destoryChainListTea(tea* p);