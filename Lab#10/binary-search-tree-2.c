#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE	20
Node* stack[MAX_STACK_SIZE]; /*포인터 배열의 원소 하나당 하나의 key만 */
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE	20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */

/* 기존에 있던void printStack(); 함수는 사용하지 않으므로 삭제하였습니다.*/


int main()
{
	char command;
	int key;
	Node* head = NULL;

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf("---------[20173038102]--------------------[최용석]--------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command)
		 {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) 
{

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}
/*제공된 함수*/

void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}
/*제공된 함수*/

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)
{
	if(node == NULL) /*초기화만 이루어지고 노드가 없을떄의 처리*/
	{
		printf("Nothing to visit!!\n");
		return;
	}

	while(1) 
	{		
		for(; node; node = node->left) /*node가 NULL이 아닌동안 push하면서 왼쪽으로 이동*/
			push(node);
		node = pop(); /*for 반복문이 종료가 되었다는 것은  가장 왼쪽의 노드가 되었다는 것이므로 1개의 원소를 pop*/
		if(!node) break; /*pop 이 NULL이라면 전부 뺴낸 것이므로 무한반복문을 종료*/ 
		
		printf(" [%d] ", node->key); /*pop된 원소를 출력하고 오른쪽으로 이동*/ 
		node = node->right;
	}	
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{ 
	if(ptr == NULL) /* headnode만 존재할 경우의 예외처리*/ 
	{
		printf("Nothing to visit!!\n");
		return;
	}

	Node* lev; /*queue값을 임시로 저장할 포인터 변수 선언 및 queue의 front,rear 초기화*/
	front = -1;
	rear = -1;
	
	enQueue(ptr); /*처음으로 root node 를 enQ*/ 
	
	while(1)
	{
		lev = deQueue(); /*q 를 하나 꺼내서 임시변수에 대입*/ 
		if(lev == NULL) break; /*해당 if가 실행이 된다면 empty q 이므로 반복을 종료*/
		
		printf(" [%d] ", lev->key); /*그렇지 않으면 출력하면서 해당 node의 왼쪽, 오른쪽 node를 재귀적으로 호출하며 출력*/
		if(lev->left != NULL) enQueue(lev->left);
		if(lev->right != NULL) enQueue(lev->right);
	}
}

int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL)
	{
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) 
	{
		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}
/*제공된 함수*/

int deleteNode(Node* head, int key)
{ 

	if(head == NULL)
	{
		printf("Nothing to delete!\n");
		return -1;
	} 
	
	if(head->left == NULL)
	{
		printf("Nothing to delete!\n");
		return -1;
	}
	
	/*
	위의 2개의 if문은 z기능 실행 이전에 해당 함수를 실행하거나, 
	z기능만 실행하고 해당 함수를 실행했을때의 처리구문.	
	*/
	
	Node* cur, *parent, *temp;
	cur = head->left;
	parent = NULL;  
	/*순회를 위한 cur, cur의 부모노드를 가르키는 역할을 할 parent, 삭제할 위치의 포인터를 담을 temp*/
	
	while(cur != NULL && cur->key != key)
	{
		parent = cur;
		if(cur->key < key)
			cur = cur->right;
			
		else 
		    cur = cur->left;
	} /*tree 의 종단까지 순회하며 key를 검색*/
	
	if(cur == NULL) /*해당 if가 실행이 된다는 것은 tree에 찾을 값이 없다는뜻 */
	{
		printf("The key isn't in the BTS!!\n");
		return -1;
	}
	
	temp = cur; /*위의 if 가 실행이 안된다면 삭제할 위치를 찾은 것이므로, 해당 위치를 잠시 저장 */
	
	if(cur->left == NULL && cur->right == NULL)
	{
		if(parent->left)
		{
			if(cur->key == parent->left->key)
			{
			parent->left = NULL;
			return 0;
			}
		}
		parent->right = NULL;
		return 0;
	} /*해당 위치가 leafnode인 경우의 삭제처리 */
	
	else if(cur->left != NULL && cur->right != NULL)
	{/*삭제할 node의 child가 2개의 child를 가지고 있는 경우 */
		cur = cur->left; // 삭제할 노드에서 왼쪽으로 내려와서 
		if(cur->right == NULL)
		{/*오른쪽 노드가 없는 경우는 삭제할 node의 왼쪽 node가 가장 크다는 뜻 (해당 삭제 연산에서 
		오른쪽에서 가장작은, 왼쪽에서 가장 큰 node를 고르는 방법 중 후자를 선택하였습니다.)*/
			temp->key = cur->key;
			temp->left = cur->left;
			return 0;
		} /*해당 node를 삭제할 node의 자리로 옮기고 왼쪽 child가 가르키는 node를 한단계 위로 올리기 */
		
		while(1)
		{
			if(cur->right == NULL)
			{
				temp->key = cur->key;
				parent->right = cur->left;
				return 0;
			}
			else
			{
				parent = cur;
				cur = cur->right;
			} /*삭제 할 노드보다 더 큰 node (right child 가 존재한다면, 반복문을 돌며 탐색하며 찾을 경우 
			node 변경 */
		}
	}
	
	else
	{/*삭제할 node의 child가 1개의 childnode를 가지고 있는 경우 */
		if(cur->right != NULL)
		{/*1개의 child가 오른쪽일 경우*/
			if(parent->left->key == key) parent->left = cur->right; //오른쪽이고, 부모의 왼쪽에 붙어있는경우, 부모의 왼쪽에 오른쪽 node를 삽입 
			else parent->right = cur->right; // 왼쪽이고, 부모의 오른쪽에 붙어있는 경우의 처리 
			return 0;
		} 
		
		if(cur->left != NULL)
		{/*1개의 child가 왼쪽일 경우*/
			if(parent->left->key == key) parent->left = cur->left;
			else parent->right = cur->left;
			return 0; /*위의 조건문과 동일한 실행 */
		}
	}
}

void freeNode(Node* ptr)
{
	
	if(ptr) 
	{
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}
/*제공된 함수*/

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}
/*제공된 함수*/

Node* pop()
{
	if(top < 0) return NULL; /*해당 조건문이 실행된다면 stack이 비어있는 상태 */
	
	else return stack[top--];
}

void push(Node* aNode)
{
	if(top < MAX_STACK_SIZE - 1)
	{
		stack[++top] = aNode;
		return ;
	}
	else
	{
		printf("Stack is full!\n");
		return;
	}
	/*먼저 스택이 가득 찼는지 검사한 이후 여유공간이 있다면 추가 */
}

Node* deQueue()
{
	Node* temp = NULL;
	
	if(front == rear)
		return temp; 
	else
	{
		++front;
		temp = queue[front % MAX_QUEUE_SIZE];
		return temp;
	}
	/*해당 q에서 front와 rear가 같다면 NULL을 반환하고 그렇지 않다면 선형을 형성하며 q로부터 deQ*/
}

void enQueue(Node* aNode)
{
	if(rear == MAX_QUEUE_SIZE - 1)
		return;
	else
	{
		rear++;
		queue[rear % MAX_QUEUE_SIZE] = aNode;
	}
	/*선형을 형성하며 enQ*/
}




