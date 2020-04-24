#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);

element getElement();


int main(void)
{
	QueueType *cQ = createQueue();
	element data;

	char command;

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("====================2017038102========최용석==============\n"); // 자신의 학번과 이름을 print하는 문장
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Dubug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ,&data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	}while(command != 'q' && command != 'Q');


	return 1;
}


QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}
element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}

/*
 * 교수님께서 작성하신 코드에는 주석을 달지 않았습니다.
 */
int isEmpty(QueueType *cQ)
{
	if(cQ->front == cQ->rear) // 해당 함수에서 rear와  front가 같은 위치인지 확인하고 같다면 에러 통보후 비정상 종료 값을 반환
	{
		printf("---------Queue is empty!!-----------\n");
		return -1;
	}
    else
    	return 0;
}
int isFull(QueueType *cQ) // 해당 함수가 호출이 되면 에러 메시지만 출력하고 종료
{
	 /*원래 해당 함수에서 if문을 통하여 full condition을 검사하려 했으나
	    에러가 발상하여 enQ함수 내에서 검사하도록 하였습니다.*/

		printf("---------Queue is full!!-----------\n");
		return 0;
}

void enQueue(QueueType *cQ, element item)
{
	cQ->rear += 1;
	cQ->rear %= MAX_QUEUE_SIZE; //  먼저 증가를 하나를 시킨 뒤에  if 문으로 같은지를 확인

	if(cQ->rear == cQ->front)
	{
		isFull(cQ);           // 이후 if문에서 같다고 판정이 되면 다시 rear를 이전의 원소를 가르키는 index 가 되도록 roll back
		cQ->rear -= 1;
		return;
	}
	else
	{
		cQ->queue[cQ->rear] = item; // 공간이 있다면 매개변수로 받아온 element를 해당 index에 대입
	}
}

void deQueue(QueueType *cQ, element *item)
{
	if(isEmpty(cQ) == -1) // 검사한 함수의 반환값이 비정상 종료와 동일하다고 판정이 되면 해당함수를 작동시키지 않음.
			return;
		else //그렇지 않은경우  else문 실행
		{
			cQ->front += 1;
			cQ->front %= MAX_QUEUE_SIZE; //모듈러 연산을 하며 0,1,2,3 반복하며 동작
			cQ->queue[cQ->front] = ' '; // 해당 번째index에 공백 문자 대입 함으로 기존의 문자가 삭제
		}
}

/*
 * 이번  과제를 통해 선형 큐에 대한 기초적인 개념을
 * 조금더 확실하게 느낄 수 있는 시간이였습니다.
 *
 */
void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1) % MAX_QUEUE_SIZE;
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);
		i = (i+1) % MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}
void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}
