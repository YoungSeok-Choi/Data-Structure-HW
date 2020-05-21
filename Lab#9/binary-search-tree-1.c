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
void InnerfreeBST(Node* ptr);

/* you may add your own defined functions if necessary */

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
	if(ptr == NULL) return;

	inorderTraversal(ptr->left);
	printf("{%d} ", ptr->key);
	inorderTraversal(ptr->right);
}

void preorderTraversal(Node* ptr)
{
	if(ptr == NULL) return;

	printf("{%d} ", ptr->key);
	preorderTraversal(ptr->left);
	preorderTraversal(ptr->right);
}

void postorderTraversal(Node* ptr)
{
	if(ptr == NULL) return;

	postorderTraversal(ptr->left);
	postorderTraversal(ptr->right);
	printf("{%d} ", ptr->key);
}

int insert(Node* head, int key)
{
	Node* cur;
	Node* parent;
	Node* new;
	new = (Node*)malloc(sizeof(Node));
	new->key = key;
	new->left = NULL;
	new->right = NULL;

	if(head == NULL)
	{
		printf("HeadNode isn't initialized. please use the funtion'Z'...\n");
		return 0;
	}

	if(head->left == NULL)
	{
		head->left = new;
		return 0;
	}

	cur = head->left;

	while(cur != NULL)
	{
		parent = cur;

		if(cur->key > key)
			cur = cur->left;
		else if(cur->key < key)
			cur = cur->right;
		else
		{
			printf("The same node's already exist...\n");
			return 0;
		}
	}

	if(parent->key > key)
		parent->left = new;
	else
		parent->right = new;

	return 0;
}

int deleteLeafNode(Node* head, int key)
{
	if(head->left == NULL)
	{
		printf("Nothing to delete...\n");
		return 0;
	}

	Node* parent, *cur;
	parent = NULL;
	cur = head->left;

	if(cur->left == NULL && cur->right == NULL)
	{
		head->left = NULL;
		free(cur);
		return 0;
	}

	while(cur != NULL && cur->key != key)
	{
		parent = cur;
		if(cur->key > key)
			cur = cur->left;
		else
			cur = cur->right;
	}
	if(cur == NULL)
	{
		printf("The key isn't in tree.\n");
		return 0;
	}

	if (cur->left == NULL && cur->right == NULL)
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
	else printf("This node's not leafnode\n");

	return 0;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL)
		return NULL;

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
	}
	return NULL;
}

int freeBST(Node* head)
{
	InnerfreeBST(head->left);
	return 0;
}

void InnerfreeBST(Node* ptr)
{
	if(ptr == NULL) return;
	InnerfreeBST(ptr->left);
	InnerfreeBST(ptr->right);
	free(ptr);
}



