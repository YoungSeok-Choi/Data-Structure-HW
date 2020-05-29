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
Node* stack[MAX_STACK_SIZE]; /*������ �迭�� ���� �ϳ��� �ϳ��� key�� */
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

/* ������ �ִ�void printStack(); �Լ��� ������� �����Ƿ� �����Ͽ����ϴ�.*/


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
		printf("---------[20173038102]--------------------[�ֿ뼮]--------------\n");
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
/*������ �Լ�*/

void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}
/*������ �Լ�*/

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)
{
	if(node == NULL) /*�ʱ�ȭ�� �̷������ ��尡 �������� ó��*/
	{
		printf("Nothing to visit!!\n");
		return;
	}

	while(1) 
	{		
		for(; node; node = node->left) /*node�� NULL�� �ƴѵ��� push�ϸ鼭 �������� �̵�*/
			push(node);
		node = pop(); /*for �ݺ����� ���ᰡ �Ǿ��ٴ� ����  ���� ������ ��尡 �Ǿ��ٴ� ���̹Ƿ� 1���� ���Ҹ� pop*/
		if(!node) break; /*pop �� NULL�̶�� ���� ���� ���̹Ƿ� ���ѹݺ����� ����*/ 
		
		printf(" [%d] ", node->key); /*pop�� ���Ҹ� ����ϰ� ���������� �̵�*/ 
		node = node->right;
	}	
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{ 
	if(ptr == NULL) /* headnode�� ������ ����� ����ó��*/ 
	{
		printf("Nothing to visit!!\n");
		return;
	}

	Node* lev; /*queue���� �ӽ÷� ������ ������ ���� ���� �� queue�� front,rear �ʱ�ȭ*/
	front = -1;
	rear = -1;
	
	enQueue(ptr); /*ó������ root node �� enQ*/ 
	
	while(1)
	{
		lev = deQueue(); /*q �� �ϳ� ������ �ӽú����� ����*/ 
		if(lev == NULL) break; /*�ش� if�� ������ �ȴٸ� empty q �̹Ƿ� �ݺ��� ����*/
		
		printf(" [%d] ", lev->key); /*�׷��� ������ ����ϸ鼭 �ش� node�� ����, ������ node�� ��������� ȣ���ϸ� ���*/
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
/*������ �Լ�*/

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
	���� 2���� if���� z��� ���� ������ �ش� �Լ��� �����ϰų�, 
	z��ɸ� �����ϰ� �ش� �Լ��� ������������ ó������.	
	*/
	
	Node* cur, *parent, *temp;
	cur = head->left;
	parent = NULL;  
	/*��ȸ�� ���� cur, cur�� �θ��带 ����Ű�� ������ �� parent, ������ ��ġ�� �����͸� ���� temp*/
	
	while(cur != NULL && cur->key != key)
	{
		parent = cur;
		if(cur->key < key)
			cur = cur->right;
			
		else 
		    cur = cur->left;
	} /*tree �� ���ܱ��� ��ȸ�ϸ� key�� �˻�*/
	
	if(cur == NULL) /*�ش� if�� ������ �ȴٴ� ���� tree�� ã�� ���� ���ٴ¶� */
	{
		printf("The key isn't in the BTS!!\n");
		return -1;
	}
	
	temp = cur; /*���� if �� ������ �ȵȴٸ� ������ ��ġ�� ã�� ���̹Ƿ�, �ش� ��ġ�� ��� ���� */
	
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
	} /*�ش� ��ġ�� leafnode�� ����� ����ó�� */
	
	else if(cur->left != NULL && cur->right != NULL)
	{/*������ node�� child�� 2���� child�� ������ �ִ� ��� */
		cur = cur->left; // ������ ��忡�� �������� �����ͼ� 
		if(cur->right == NULL)
		{/*������ ��尡 ���� ���� ������ node�� ���� node�� ���� ũ�ٴ� �� (�ش� ���� ���꿡�� 
		�����ʿ��� ��������, ���ʿ��� ���� ū node�� ���� ��� �� ���ڸ� �����Ͽ����ϴ�.)*/
			temp->key = cur->key;
			temp->left = cur->left;
			return 0;
		} /*�ش� node�� ������ node�� �ڸ��� �ű�� ���� child�� ����Ű�� node�� �Ѵܰ� ���� �ø��� */
		
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
			} /*���� �� ��庸�� �� ū node (right child �� �����Ѵٸ�, �ݺ����� ���� Ž���ϸ� ã�� ��� 
			node ���� */
		}
	}
	
	else
	{/*������ node�� child�� 1���� childnode�� ������ �ִ� ��� */
		if(cur->right != NULL)
		{/*1���� child�� �������� ���*/
			if(parent->left->key == key) parent->left = cur->right; //�������̰�, �θ��� ���ʿ� �پ��ִ°��, �θ��� ���ʿ� ������ node�� ���� 
			else parent->right = cur->right; // �����̰�, �θ��� �����ʿ� �پ��ִ� ����� ó�� 
			return 0;
		} 
		
		if(cur->left != NULL)
		{/*1���� child�� ������ ���*/
			if(parent->left->key == key) parent->left = cur->left;
			else parent->right = cur->left;
			return 0; /*���� ���ǹ��� ������ ���� */
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
/*������ �Լ�*/

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
/*������ �Լ�*/

Node* pop()
{
	if(top < 0) return NULL; /*�ش� ���ǹ��� ����ȴٸ� stack�� ����ִ� ���� */
	
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
	/*���� ������ ���� á���� �˻��� ���� ���������� �ִٸ� �߰� */
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
	/*�ش� q���� front�� rear�� ���ٸ� NULL�� ��ȯ�ϰ� �׷��� �ʴٸ� ������ �����ϸ� q�κ��� deQ*/
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
	/*������ �����ϸ� enQ*/
}




