#include<stdio.h>
#include<stdlib.h>
/*  필요한 헤더파일 추가 if necessary */

typedef struct Node
{
	int key;
	struct Node* llink; //이전 노드를 저장
	struct Node* rlink; // 다음 노드를 저장, 맨 마지막 노드는 NULL을 저장
} listNode;

typedef struct Head
{
	struct Node* first;
}headNode;

/* 함수 리스트 */
/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList싱글포인터를 매개변수로 받음
        - initialize왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);
void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("------------최용석-------------------------------2017038102--------------\n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(headNode** h)
{
	headNode* temp;
	if(*h != NULL)
		freeList(*h); // 정확하게 개념이 잡히지는 않았지만, *h를 매개변수로 넘김으로서 현재 main 내부에 있는 포인터를 넘기는듯 함.  **h, *h, h 의 차이를 정확히 알아야 할 필요성이 있음.

	*h = (headNode*)malloc(sizeof(headNode));
	temp = *h; // 위와 비슷한 맥락
	temp->first = NULL;
	return 0;
}

int freeList(headNode* h)
{
	listNode *cur = h->first;
	listNode *prev = NULL;

	while(cur != NULL)
	{
		prev = cur;
		cur = cur->rlink; //cur 를 진행시키며 prev를 할당해제 함
		free(prev);
	}
	free(h); // 마지막으로 첫번째노드까지 할당해제
	return 0;
}

void printList(headNode* h)
 {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}
// 제공된 함수

/**
 * list에 key에 대한 노드하나를 추가 (맨 마지막 부분)
 */
int insertLast(headNode* h, int key)
{

	if(h == NULL) // z기능 사용 이전의 사용시 처리부분
	{
		printf("현재 리스트의 헤드노드가 정의되어있지 않습니다. z 기능으로 초기화한 이후 사용하세요\n");
		return 0;
	}

	listNode *cur = h->first;
	listNode *prev = NULL;
	listNode *node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = NULL; // node의 초기화 부분
	node->rlink = NULL;

	if(h->first == NULL)
	{
		h->first = node;   // 첫번째 노드가 비었다면 해당 노드를 삽입 후 함수 종료
		return 0;
	}

	while(cur->rlink != NULL) // 함수의 끝이 나올때 까지 이동 이후 추가될 노드의 llink를 cur 를 가르키게 함으로써 양방향으로 서로 가르키게 됨.
	{
		prev = cur;
		cur = cur->rlink;
	}
	cur->rlink = node;
	node->llink = cur;
	return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h)
{
	listNode *cur;
	listNode *prev;

	if(h == NULL)
	{
		printf("현재 헤드노드가 존재하지 않습니다. z 기능으로 초기화한 이후 사용하세요\n");
		return 0;
	}
	else if(h->first->rlink == NULL)// 첫번째 노드의 다음 노드를 가르키는부분이 널이라면, 첫번쨰 노드를 삭제하는 연산
	{
		cur = h->first;
		h->first = cur->rlink;
		free(cur);
	}

	else
	{
		cur = h->first;
		prev = NULL;
		while(cur->rlink != NULL) // 그렇지 않다면 리스트에 여러개 노드가 있으므로 cur를 끝까지 보내고 마지막노드 삭제처리
		{
			prev = cur;
			cur = cur->rlink;

		}
		free(cur);
		prev->rlink = NULL; // cur를 가르켰던 link를 NULLfh 변경하여 마지막 노드임을 나타냄
	}
	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key)
{
	if(h == NULL) //z기능 이전에 사용한 경우
	{
		printf("현재 리스트의 헤드노드가 정의되어있지 않습니다. z 기능으로 초기화한 이후분사용하세요\n");
		return 0;
	}

	listNode *node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = NULL;// node초기화 부분
	node->rlink = h->first; // 기존에 가르키고 있었던 노드를 추가될 노드가 가르키는 다음 노드로 하고
	h->first = node; // 현재 노드를 헤드노드로 추가
	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h)
{
	if(h == NULL)
	{
		printf("현재 리스트의 헤드노드가 정의되어있지 않습니다. z 기능으로 초기화한 이후 사용하세요\n");
		return 0;
	}

	listNode *cur = h->first;

	h->first = cur->rlink; //첫번째 노드가 가르키는 다음 노드를 첫번째 노드로 하고
	free(cur); // 기존의 있던 첫번째 노드를 삭제

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h)
{
	listNode* prev;
	listNode* cur;
	listNode* tail;

	if(h == NULL) // z 기능 처리부분
	{
		printf("헤드노느가 정의되어있지 않습니다. z 기능을 먼저 사용한 이후 사용하십시오.\n");
		return 0;
	}
	else
	{
		prev = NULL; // cur,prev가 같은 곳을 가르키고 tail이 바로 뒤를 가리키며 따라온다.
		tail = NULL; // 그리고 cur가 앞으로 가면, prev가 현재포인터의 link를 tail을 가르키게하고 tail을 따라오게 함
		cur = h->first;
		while(cur->rlink != NULL)
		{
			tail = prev;
			prev = cur;
			cur = cur->rlink;
			prev->rlink = tail;
		}
		tail = prev;    // 왜냐하면 cur가 먼저 link를 통해 한 노드 앞으로 가고 위의 반복분 탈출조건에 해당되어 반복이 종료되기 때문.
		prev = cur;
		prev->rlink = tail;  // 따라서 prev를 한번 더 앞으로 옮겨줌으로써 맨 마지막 노드까지 invert를 하게된다
		h->first = prev; // headnode를 prev를 가르킴으로써 역순으로 바꿈
	}
	return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key)
{
	if(h == NULL)//z기능 실행하지 않은경우 처리
	{
		printf("현재 리스트에 노드가 존재하지 않습니다.\n");
		return 0;
	}

	listNode *node = (listNode*)malloc(sizeof(listNode));
	listNode *cur;
	listNode *prev;

	node->llink = NULL;
	node->rlink = NULL;
	node->key = key; // node 의 초기화 부분

	if(h->first == NULL) // 초기화만 되고 삽입이 이루어지지 않은 경우
	{
		h->first = node;
		return 0;
	}
	else if(h->first->key > key) // 첫번째 노드와 비교해서 첫번쨰 노드 앞에 삽입해야 하는경우
	{
		node->rlink = h->first;
		h->first = node;
		return 0;
	}
	else //  위의 조건문들을 실행하지 않았다면 해당 else문에서 리스트를 돌며 자리를 찾음
	{
		cur = h->first;
		prev = NULL;
		while((cur->rlink != NULL) && (cur->key < key))
		{
			prev = cur;
			cur = cur->rlink;
		}
		if((cur->rlink == NULL) && (cur->key < key)) // 리스트의 마지막에 삽입해야하는 조건이 성립이 되면 마지막에 노드 추가
		{
			cur->rlink = node;
			node->llink = cur; //추가될 마지막 노드의 llink를 이전노드를 가르키도록 설정
		}

		else // 마지막 노드가 아닌 리스트의 중간에서 삽입이 된다면 삽입될 node와 prev, cur의 연결을 수행
		{
			node->rlink = cur;
			cur->llink = node;
			node->llink = prev;
			prev->rlink = node;
		}
	}
	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key)
{
	listNode *cur;
	listNode *prev;

	cur = h->first;
	prev = NULL;

	if(h == NULL)
	{
		printf("해당 리스트에 헤드노드가 존재하지 않습니다. Z 기능을 먼저 사용하십시오.\n");
		return 0;
	}
	else if(h->first->key == key) // 첫번째 노드를 삭제해야하는 경우
	{
		h->first = cur->rlink;
		free(cur);
	}
	else
	{
		while((cur->rlink != NULL) && (cur->key != key)) //NULL이 아니고 삭제해야할 키가 아닌동안 리스트를 이동
		{
			prev = cur;
			cur = cur->rlink;
		}
		if((cur->rlink == NULL) && (cur->key == key)) // list의 마지막이고 삭제해야할 키와 같은경우 즉 마지막 노드가 삭제노드인 경우 삭제연산
		{
			free(cur);
			prev->rlink = NULL;
			return 0;
		}
		else if(cur->key == key) /*리스트 중간에서 삭제해야하는경우
		 현재노드가 가르키는 다음노드를 이전노드의 다음노드가 가르키도록 하고 현재노드의 다음노드의 이전 노드를 가르키는 llink를 이전 노드를 가르키도록 만듦.
		*/
		{
			prev->rlink = cur->rlink;
			cur->rlink->llink = prev->rlink;
			free(cur);
		}
		else //위의 조건들을 만족하지 못한 경우 해당되는 값이 없으므로 에러메시지 출력
		{
			printf("the key isn't in the list\n");
		}
	}
	return 1;
}

