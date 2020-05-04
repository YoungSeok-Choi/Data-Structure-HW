#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
	int key;
	struct Node* link;
} listNode;

typedef struct Head
{
	struct Node* first;
}headNode;

headNode* initialize(headNode* h);
int freeList(headNode* h);
int insertFirst(headNode* h, int key); // 첫번째 노드에다가 추가시키는 함수 (리스트가 비어있지 않더라도)
int insertNode(headNode* h, int key); // 특정 노드 사이에다가 추가시키는 함수
int insertLast(headNode* h, int key); // 맨 마지막에 단순히 노드를 추가시키는 함수
int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);
void printList(headNode* h);

/*
 * main 함수 및 제공된 함수에는 별다른 주석을 달지 않았습니다.
 * */

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------2017038102--------------------made by 최용석-------------\n");
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
			headnode = initialize(headnode);
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

headNode* initialize(headNode* h)
{
	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}
// 제공된 함수

int freeList(headNode* h)
{
	/* h와 연결된 listnode 메모리 해제
	 * headnode 도 해제되어야 함
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}
// 제공된 함수

//list 처음에 key에 대한 노드하나를 추가
int insertFirst(headNode* h, int key)
{
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0; // 이거 참고하세요!!
}
// 제공된 함수

//리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
// 즉, 현재 입력받은 key값보다 순회하고 있는 cur의 key값이 큰 경우에만 삽입, cur->key가 더 작다면 뒤로 이동.
int insertNode(headNode* h, int key) // 오름차 순으로 정리
{
	listNode* node; // 동적할당을 받을 node변수와 리스트의 순회 및 삽입연산에 필요한 포인터 2개 추가 선언
	listNode* cur;
	listNode* prev;

	node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL; //각각 필드를 초기화

	if(h == NULL) // HeadNode가 존재하지 않는 경우 예외처리
		{
			printf("현재 리스트의 헤드노드가 정의되어있지 않습니다. z 기능으로 초기화한 이후 사용하세요\n");
			return 0;
		}

	if(h->first == NULL) // HeadNode만 존재하는 경우 삽입연산
		{
			h->first = node;
			return 0;
		}
	else if(h->first->key > key) //첫번째 노드의key값이 입력받은 key보다 큰 경우 해당 노드가 첫번째 노드에 삽입되어야 하므로 이를 처리하는 문장
	{
		node->link = h->first;
		h->first = node;
		return 0;
	}
	else // 첫번째 노도의 조건이 성립되지 않는다면 리스트를 순회하며 조건에 맞는 자리를선택
	{
		prev = h->first;
		cur = h->first; // 최용석 바보 멍청이 똥개
			while((cur->link != NULL) && (cur->key < key))
			{
				prev = cur;
				cur = cur->link;
			}
			if((cur->link == NULL) && (cur->key < key)) // 입력받은 node의 key가 리스트에서 가장 큰 경우, list의 맨 뒤에 삽입되어야 함. 이를 처리하는 문장
				cur->link = node;
			else // 위의 if문을 만족하지 않는다면, list의 끝이 아니고 중간이므로 중간노드삽입 처리
			{
				node->link = cur;
				prev->link = node;
			}
	}
	return 0;
}

//list에 key에 대한 노드하나를 추가
int insertLast(headNode* h, int key)
{
	listNode* node;
	listNode* cur; //변수선언

	node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL; // 새로운 node의 초기화

	if(h == NULL) // main에서 z 기능이 실행되지 않은 경우 처리
	{
		printf("현재 헤드노드가 존재하지 않습니다. z 기능으로 초기화한 이후 사용하세요\n");
		return 0;
	}

	if(h->first == NULL) // HeadNode만 존재하는 경우 에외처리
	{
		h->first = node;
		return 0;
	}

	cur = h->first; // 첫번째 노드의 위치를 받고 리스트의 끝까지 순회하며 끝에 도달하면 단순히 노드 하나를 추가하는 연산
	while(cur->link != NULL)
		cur = cur->link;
	cur->link = node;
	return 0;
}

// list의 첫번째 노드 삭제
int deleteFirst(headNode* h)
{
	if(h == NULL) // z기능이 실행되지 않은 경우 처리
	{
		printf("Nothing to delete....\n"); // 제공된 함수에서 프린트문 참조.....
		return 0;
	}

	listNode* cur;
	cur = h->first; //초기 첫번째 노드를 가르키게 한 뒤 첫번째 노드가 가르키는 다음 노드를 첫 노드로 하고, free
	h->first = cur->link;
	free(cur);
	return 0;
}

//list에서 key에 대한 노드 삭제
int deleteNode(headNode* h, int key)
{
	listNode* cur;
	listNode* prev;

	cur = h->first; // 첫번째 노드를 가르킴
	if(h == NULL)// z기능이 실행되지 않은 경우 처리
	{
		printf("해당 리스트에 노드가 존재하지 않습니다.\n");
		return 0;
	}
	else if(h->first->key == key) // 사용자에게 입력받은 값이 첫번째 노드의 key와 동일한 경우 처리
	{
		h->first = cur->link;
		free(cur);
	}
	else
	{
		cur = h->first->link; // cur를 prev의 한개 노드 앞에서 움직이도록 설정
		prev = h->first;
		while((cur->link != NULL) && (cur->key != key)) // NULL이 아니면서 key가 일치하지 않는동안 리스트 순회
				{
					prev = cur;
					cur = cur->link;
				}
		if(cur->key == key) // 위의 반복문이 list의 끝에 도착해서 끝난것인지, 삭제할 key를 찾아서 끝난것인지 판단하기위한 if()
		{
			prev->link = cur->link; // 이전의 노드를 현재노드가 가르키는 노드를 가르키게 하고 free
			free(cur);
		}
		else // list의 끝까지 검색한 것이므로 key 가 리스트 안에 없음을 말함
			printf(" this key isn't in the list\n");
	}
	return 0;
}

//list의 마지막 노드 삭제
int deleteLast(headNode* h)
{
	listNode* cur;
	listNode* prev;

	if(h == NULL)//z기능 실행하지 않은경우 처리
	{
		printf("현재 리스트에 노드가 존재하지 않습니다.\n");
		return 0;
	}
	else if(h->first->link == NULL) // 첫번째 노드만 있는 경우 cur->link값에는 NULL이 들어가 있을것이므로
	{                                   // 첫번째 노드포인터에 NULL을 넣고 free
		cur = h->first;
		h->first = cur->link;
		free(cur);
		return 0;
	}
	else // 노드가 여러개 있을경우 마지막까지 순회하고 삭제하기 이전 노드의 link를 끝을 나타내는 NULL로 설정
	{
		cur = h->first;
		prev = h->first;
		while(cur->link != NULL)
		{
			prev = cur;
			cur = cur->link;
		}
	}
	free(cur);
	prev->link = NULL;
	return 0;
}

//리스트의 링크를 역순으로 재배치
int invertList(headNode* h)
{
	listNode* prev;
	listNode* cur;
	listNode* tail;

	if(h == NULL) // z 기능
	{
		printf("linked list is Empty.\n");
		return 0;
	}
	else
	{
		prev = NULL; // cur,prev가 같은 곳을 가르키고 tail이 바로 뒤를 가리키며 따라온다.
		tail = NULL; // 그리고 cur가 앞으로 가면, prev가 현재포인터의 link를 tail을 가르키게하고 tail을 따라오게 함
		cur = h->first;
		while(cur->link != NULL)
		{
			tail = prev;
			prev = cur;
			cur = cur->link;
			prev->link = tail;
		} // 여기까지 프로그램 실행의 분기가 왔을 경우, prev는 list의 마지막 바로 앞 노드까지 와있는상태이다.
		tail = prev;    // 왜냐하면 cur가 먼저 link를 통해 한 노드 앞으로 가고 위의 반복분 탈출조건에 해당되어 반복이 종료되기 때문.
		prev = cur;
		prev->link = tail;  // 따라서 prev를 한번 더 앞으로 옮겨줌으로써 맨 마지막 노드까지 invert를 하게된다
		h->first = prev; // headnode를 prev를 가르킴으로써 역순으로 바꿈
	}
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
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}
// 제공된 함수

