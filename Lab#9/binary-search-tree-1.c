#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */
void InnerfreeBST(Node* ptr); /*freeBST 에서 실행될 recursive 노드제거 함수 선언*/

int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("-------2017038102-------------------------최용석--------------------\n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
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
	return 1;
}
// 제공된 함수

void inorderTraversal(Node* ptr)
{
	if(ptr == NULL) return; /*인자로 Headnode만 넘어왔을 경우의 처리*/

	/*트리에서 가장 왼쪽 노드까지 온 이후
	 * 맨 왼쪽의 노드에 도착했을 때 프린트 한 이후
	 * 맨 오른쪽 노드를 프린트하며 다시 위로 올라감*/

	inorderTraversal(ptr->left);
	printf("{%d} ", ptr->key);
	inorderTraversal(ptr->right);
}

void preorderTraversal(Node* ptr)
{
	if(ptr == NULL) return;

	/*순회하는 노드에 도착하자마자 프린트 하는 preorder
	 * 방식의 순회 및 출력 연산, 맨 왼쪽노드부터 출력해 나가면서
	 * 트리의 가장 왼쪽 리프노드에 도착했을 때 오른쪽을 출력하며 위로 올라감*/

	printf("{%d} ", ptr->key);
	preorderTraversal(ptr->left);
	preorderTraversal(ptr->right);
}

void postorderTraversal(Node* ptr)
{
	if(ptr == NULL) return;

	/*
	 * 가장 왼쪽의 리프노드까지 순회한 이후,
	 * 왼쪽과 오른쪽 까지 모두 출력한 이후에
	 * 부모노드로 올라가며 출력하는 postorder
	 * */
	postorderTraversal(ptr->left);
	postorderTraversal(ptr->right);
	printf("{%d} ", ptr->key);
}

int insert(Node* head, int key)
{
	/*
	 * 부모노드의 정보와 부모노드의 차일드 노드를 가르키는
	 * 포인터 변수 선언
	 * */

	Node* cur;
	Node* parent;
	Node* new;
	new = (Node*)malloc(sizeof(Node));
	new->key = key;
	new->left = NULL;
	new->right = NULL;

	if(head == NULL) /*헤드노드가 선언되지 않았을 경우 처리*/
	{
		printf("HeadNode isn't initialized. please use the funtion'Z'...\n");
		return 0;
	}

	if(head->left == NULL) /*헤드노드만 있을 경우의 삽입처리*/
	{
		head->left = new;
		return 0;
	}

	cur = head->left; /*현재 노드를 트리의 root노드를 가르키게 하고*/

	while(cur != NULL)
	{
		parent = cur;

		/*
		 * 부모가 child 노드를 따라가고 cur는 한단계 내려가게 함으로써
		 * traking을 가능하게 함
		 * */

		if(cur->key > key)
			cur = cur->left;
		else if(cur->key < key)
			cur = cur->right;
		else  /*위의 조건이 만족돼지 않으면 같은 값임을 뜻하므로 에러메시지출력 후 함수 종료*/
		{
			printf("The same node's already exist...\n");
			return 0;
		}
	}

	if(parent->key > key) /*현재 cur는 leafnode의 NULL을 포인트하고 있고, 그것의 한단계 위인
	parent 포인터가 리프노드이므로 parent와의 비교문을 실행*/
		parent->left = new;
	else
		parent->right = new;

	return 0;
}

int deleteLeafNode(Node* head, int key)
{
	if(head->left == NULL)  /*헤드노드만 존재할 경우의 에러처리*/
	{
		printf("Nothing to delete...\n");
		return 0;
	}

	Node* parent, *cur;
	parent = NULL;
	cur = head->left;

	/*삽입함수와 마찬가지로 cur가 한단계 앞에서 순회하고 parent가
	 * cur를 따라가도록 함
	 * */

	if(cur->left == NULL && cur->right == NULL) /*트리에 root노드만 존재할 경우의 처리부분*/
	{
		head->left = NULL;
		free(cur);
		return 0;
	}

	while(cur != NULL && cur->key != key) /*해당 반복문을 돌면서 값을 비교하며 이진탐색 실행*/
	{
		parent = cur;
		if(cur->key > key)
			cur = cur->left;
		else
			cur = cur->right;
	}
	if(cur == NULL) /*반복문이 끝나고 해당 문장이 실행된다면 트리 안에 삭제할 값이 없다는 뜻임*/
	{
		printf("The key isn't in tree.\n");
		return 0;
	}

	if (cur->left == NULL && cur->right == NULL) /*cur 변수가 NULL값을 담기 한단계 직전인 부분에서 반복문이 깨져서 나온다면
	리프노드이므로 부모노드가 cur를 왼쪽으로 가르키는지, 오른쪽으로 가르키는지 판단해서 해당 부분을 할당해제 하고 NULL값을 대입*/
	{
		if(parent != NULL)
		{
			if(parent->left == cur)
			{
				parent->left = NULL;
				free(cur);
				return 0;
			}
			else
			{
				parent->right = NULL;
				free(cur);
				return 0;
			}
		}
	}
	else printf("This node's not leafnode\n"); /*위의 &&로 연결된 if문이 실행이 되지 않는다면 트리의 중간임을 뜻하므로 에러메시지 출력 후 함수종료.*/

	return 0;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL) /*인자가 NULL을 가르키고 있다면 실행할 필요가 없으므로 NULL리턴*/
		return NULL;

	/*현재 노드의 key와 인자의key를 비교해서 이진탐색트리의 특성에 맞게
	 * 왼쪽, 오른쪽을 포인터 인자를 결정하고 찾은 값이면 포인터를 반환*/

	else if (ptr->key > key)
		return searchRecursive(ptr->left, key);

	else if(ptr->key == key)
		return ptr;

	else
		return searchRecursive(ptr->right, key);
}

Node* searchIterative(Node* head, int key)
{
	Node* temp = head->left;

	while(temp != NULL)
	{
		if(temp->key > key) temp = temp->left;
		else if(temp->key == key) return temp;
		else temp = temp->right;

		/*
		 * 반복문을 실행하면서 key와의 비교에 따라서 이진탐색 실행
		 * */

	}
	return NULL; /*반복문에서 return이 되지않는다면 해당 리턴문이 실행되며 값을 찾지 못하는 NULL을 반환*/
}

int freeBST(Node* head)
{
	/*
	 * 해당 함수 부분에서 따로 구현한 재귀함수를 호출하여
	 * 이진탐색트리의 할당해제를 구현.
	 * */

	InnerfreeBST(head->left);
	return 0;
}

/*
 * 따로 선언한 함수(freeBST에서 실행되는 재귀호출로 작동하는 트리 할당해제 함수)
 * */
void InnerfreeBST(Node* ptr)
{
	if(ptr == NULL) return; /*인자의 NULL을 처리하는 부분*/
	InnerfreeBST(ptr->left);
	InnerfreeBST(ptr->right); /*위에서의 순회 함수와 비슷한 원리로 순회하면서 노드들을 할당해제*/
	free(ptr);
}



