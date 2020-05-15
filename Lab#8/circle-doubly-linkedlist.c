#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node
{
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode; // 이번 과제 헤드노드 구조체가 사라짐

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);
int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);
void printList(listNode* h);

int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("-------------최용석---------------------------------2017038102----------\n");
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

int initialize(listNode** h)
{

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 하제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999; // 헤드노드에는 data가 딱히 필요 없으므로 해당 값 처리인듯
	return 1;
}
// 제공된 함수

/* 메모리 해제 */
int freeList(listNode* h)
{
	if(h == NULL)
	{
		printf("현재 헤드노드가 존재하지 않습니다. z기능을 사용하고 난뒤 사용하십시오\n");
		return -1;
	}
	else
	{
		listNode* cur = h->rlink;
		listNode* prev = NULL;

		while(cur != NULL && cur != h)
		{
			prev = cur;
			cur = cur->rlink;
			free(prev);
		}
		free(cur);
	}
	return 0;
}
// 최종동작 확인

void printList(listNode* h)
{
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink; // 헤드 노드의 오른쪽 링크가 리스트의 첫번쨰 노드를 가르킴, 바꿔 말하면 왼쪽 링크가 마지막을 가르키고있음

	while(p != NULL && p != h) // 여기서 논리식이 왜 이렇게 된걸까 NULL포인터는 존재하지 않을텐데
	{
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);

	/* 값 출력 끝나고 주소출력 하는 부분 */
	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}
// 제공된 함수

/**
 * list�� key�� ���제 �몃뱶�섎굹瑜� 異붽�
 */
int insertLast(listNode* h, int key)
{
	if(h == NULL)
	{
		printf("현재 HeadNode가 정의되어있지 않습니다. z기능으로 초기화 이후 사용하세요.\n");
		return -1; // 에러처리
	}

	listNode* cur = h->rlink;
	listNode* prev = NULL;
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = NULL;
	node->rlink = NULL;

	if(h->llink == h && h->rlink == h) //헤드노드만 있는경우
	{
		h->llink = node;
		h->rlink = node;
		node->llink = h;
		node->rlink = h;
		return 1;
	}

	while(cur != NULL && cur != h) // 여러개의 노드가 있을 경우
	{
		prev = cur;
		cur = cur->rlink;
	}

	prev->rlink = node;
	node->llink = prev;
	node->rlink = h;
	h->llink = node;

	return 1;
}
// 최종동작 확인

/**
 * list�� 留덉�留� �몃뱶 ��젣
 */
int deleteLast(listNode* h)
{
	if(h == NULL)
	{
		printf("현재 HeadNode가 정의되어있지 않습니다. z기능을 통해 초기화 이후 사용하십시오.\n");
		return -1;
	}
	else if(h->llink == h && h->rlink == h)
	{
		printf("현재 HeadNode만 정의되어 있습니다. 삭제할 유효한 값이 존재하지 않습니다.\n");
		return -1;
	}
	else
	{
		listNode* cur = h->rlink;
		listNode* prev = NULL;

		while(cur != NULL && cur != h) // 마지막까지 이동 후 삭제
		{
			prev = cur;
			cur = cur->rlink;
		}
		h->llink = prev->llink;
		prev->llink->rlink = h;
		free(prev);
	}
	return 1;
}
// 최종동작 확인

/**
 * list 泥섏쓬�� key�� ���� �몃뱶�섎굹瑜� 異붽�
 */
int insertFirst(listNode* h, int key)
{

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = NULL;
	node->rlink = NULL;

	if(h == NULL)
	{
		printf("현재 HeadNode가 존재하지 않습니다. z기능을 사용하고 난 뒤에 사용하십시오.\n");
		return -1;
	}
	else if(h->llink == h && h->rlink == h) // 헤드노드만 있는 경우
	{
		h->llink = node;
		h->rlink = node;
		node->llink = h;
		node->rlink = h;
		return 1;
	}
	else
	{
		node->rlink = h->rlink;
		node->rlink->llink = node;
		node->llink = h;
		h->rlink = node;
	}
	return 1;
}
// 최종동작 확인

/**
 * list�� 泥ル쾲吏� �몃뱶 ��젣
 */
int deleteFirst(listNode* h)
{
	listNode* temp = NULL;

	if(h == NULL)
	{
		printf("현재 HeadNode가 존재하지 않습니다. z기능을 사용하고 난 뒤 다시 사용하세요.\n");
		return -1;
	}
	else if(h->llink == h && h->rlink == h)
	{
		printf("현재 HeadNode만 존재하고 유효한 값을 가지는 node가 존재하지 않습니다. node를 insert 한 이후 사용하세요.\n");
		return -1;
	}
	else
	{
		temp = h->rlink;
		h->rlink = h->rlink->rlink;
		h->rlink->llink = h;
		free(temp);
	}
	return 1;
}
//최종동작 확인

/**
 * 由ъ뒪�몄쓽 留곹겕瑜� ��닚�쇰줈 �� 諛곗튂
 */
int invertList(listNode* h)
{
	listNode* prev;
	listNode* cur;
	listNode* tail;
	listNode* temp;
	listNode* temp1;

	if(h == NULL)
	{
		printf("현재 HeadNode가 존재하지 않습니다. z기능을 사용하고 난 뒤 다시 사용하세요.\n");
		return -1;
	}
	else if(h->llink == h && h->rlink == h)
	{
		printf("현재 HeadNode만 존재하고 유효한 값을 가지는 node가 존재하지 않습니다. node를 insert 한 이후 사용하세요.\n");
		return -1;
	}
	else
	{

		prev = NULL; // cur,prev가 같은 곳을 가르키고 tail이 바로 뒤를 가리키며 따라온다.
		tail = NULL; // 그리고 cur가 앞으로 가면, prev가 현재포인터의 link를 tail을 가르키게하고 tail을 따라오게 함
		cur = h->rlink;
		temp = h->rlink;

			while(cur != NULL && cur != h) // 리스트를 돌며 포인터를 뒤바꿈
			{
				tail = prev;
				prev = cur;
				cur = cur->rlink;
				prev->rlink = tail;
			}

		prev->rlink = tail;
		cur->rlink = tail;
		temp->rlink = h;
		h->llink = temp;
		h->rlink = prev;


		cur = h->rlink;
		prev = NULL;
		tail = NULL;
		temp = h->llink;

		while(cur != NULL && cur != h) // 나머지 llink의 invert 처리 부분
		{
			tail = prev;
			prev = cur;
			cur = cur->llink;
			prev->llink = tail;
		}
		h->rlink->llink = h;
		prev->llink = tail;
		cur->llink = prev;
	}
	return 0;
}


/* 由ъ뒪�몃� 寃��됲븯��, �낅젰諛쏆� key蹂대떎 �곌컪�� �섏삤�� �몃뱶 諛붾줈 �욎뿉 �쎌엯 */
int insertNode(listNode* h, int key)
{
	if(h == NULL)
	{
		printf("현재 HeadNode가 존재하지 않습니다. z기능을 사용하고 난 뒤 다시 사용하세요.\n");
		return -1;
	}

	listNode* node = (listNode*)malloc(sizeof(listNode));
	listNode* cur;
	listNode* prev;
	node->key = key;
	node->llink = NULL;
	node->rlink = NULL;
	cur = h->rlink;

	if(h->llink == h && h->rlink == h) //헤드노드밖에 없는경우
	{
		h->llink = node;
		h->rlink = node;
		node->llink = h;
		node->rlink = h;
		return 1;
	}

	if(cur->key > node->key) // 첫번째 노드보다 작을경우
	{
		h->rlink = node;
		node->rlink = cur;
		node->llink = h;
		cur->llink = node;
		return 1;
	}

		while(cur != NULL && cur != h && cur->key < node->key) // 조건이 유지돼는동안 포인터 이동
		{
			prev = cur;
			cur = cur->rlink;
		}

		if((cur != NULL && cur != h) && (cur->key > node->key)) // 리스트 중간에서의 삽입
		{
			node->rlink = prev->rlink;
			cur->llink = node;
			node->llink = prev;
			prev->rlink = node;
			return 0;
		}

		if((cur != NULL && cur == h) && (cur->key < node->key)) // 리스트 마지막에서의 삽입
		{
			prev->rlink = node;
			node->llink = prev;
			node->rlink = h;
			h->llink = node;
		}
	return 0;
}
// 최종동작 확인

/**
 * list�먯꽌 key�� ���� �몃뱶 ��젣
 */
int deleteNode(listNode* h, int key)
{
	if(h == NULL)
	{
		printf("현재 HeadNode가 존재하지 않습니다. z기능을 사용하고 난 뒤 다시 사용하세요.\n");
		return -1;
	}

	listNode* cur;
	listNode* prev = NULL;


	if(h->llink == h && h->rlink == h)
	{
		printf("현재 HeadNode 이외에 다른 유효한 값을 가지는 node 가 존재하지 않습니다. node insert 이후 사용하십시오.\n"); // 헤드노드도 존재하지 않거나 헤드노드만 존재하는경우
		return -1;
	}
	else if(h->rlink->key == key)
	{
		cur = h->rlink;
		h->rlink = h->rlink->rlink;
		h->rlink->llink = h;
		free(cur);
		return 1;
	}
	else
	{
		cur = h->rlink;

		while((cur != NULL) && (cur != h) && (cur->key != key)) // 마지막까지 돌면서 조건에 따라 삭제
		{
			prev = cur;
			cur = cur->rlink;
		}
		if(cur == h && cur->key == key)
		{
			h->llink = prev->llink;
			prev->llink->rlink = h;
			free(prev);
			return 1;
		}
		else if(cur->key == key)
		{
			prev->rlink = cur->rlink;
			prev->rlink->llink = prev;
			free(cur);
			return 1;
		}
		else
		{
			printf("입력한 값은 현재 list에 존재하지 않습니다.\n");
			return 1;
		}
	}
	return 0;
}
// 최종동작 확인
