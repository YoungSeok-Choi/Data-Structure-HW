#include <stdio.h>
#include <stdlib.h>

/*�׷����� �ִ� ũ�� �� ���� �迭�� ���� �ʱ�ȭ.*/
#define MAX_VERTEX		20
#define TRUE	1
#define FALSE	0

typedef struct Vertex
{  													
	int num; 					/*�׷����� ������ ������ data�� �ƴ� Identity*/
	struct Vertex* link;		/*������ ���� vertex������Ű�� ��ũ(���� ����Ʈ).*/
} Vertex;

typedef struct VertexHead
{ 								/*vlist �� ������ �ε����� ������ �� ����. �ش� ������ ������ vlist �� index�� ����.*/
	Vertex* head;
} VertexHead;

typedef struct Graph
{ 								/*vlist ����Ű�� name*/					
	VertexHead* vlist;
} Graph;

/*DFS, BFS �˻��� ���� �ڷᱸ�� set up*/
/*For Stack */
typedef struct stacknode
{
	int data;
	struct stacknode* link;
}stacknode;

/*For Queue */
typedef struct Qnode
{
	int data;
	struct Qnode* link;
} Qnode;

typedef struct
{
	Qnode* front;
	Qnode* rear;
} FnR;

/*��Ÿ �ڷᱸ�� set up*/
stacknode* top;
int visitmark_DFS[MAX_VERTEX]; 						/*DFS�˻� �� �湮���θ� ��Ÿ���� �迭.*/ 
int visitmark_BFS[MAX_VERTEX];						/*BFS�˻� �� �湮���θ� ��Ÿ���� �迭.*/ 
int vflag[MAX_VERTEX];								/*�׷����� ���� ���� ���θ� ��Ÿ���� �迭*/

/*�䱸�Լ� Prototype*/
void createGraph(Graph** temp);						/* empty graph creation */
void destroyGraph(Graph* temp); 					/* deallocating all allocated memory */
int insertVertex(Graph* temp, int index); 			/* vertex insertion */
int deleteVertex(Graph* temp, int index); 			/* vertex deletion */
int insertEdge(Graph* temp, int u, int v); 			/* new edge creation between two vertices */
int deleteEdge(Graph* temp, int u, int v); 			/* edge removal */
void depthFS(Graph* temp, int V);					/* depth firt search using stack */
void breadthFS(Graph* temp, int V);					/* breadth first search using queue */
void printGraph(Graph* temp);						/* printing graph with vertices and edges */

/*�����Լ� Prototype*/
void printMenu();									/*�޴��� ����ϴ� �Լ�.*/
void Adj_listDelete(Vertex* h, int key);			/*�ϳ��� ������ ���� ������ �ٸ� ������ ���� ����Ʈ ���� �Լ�*/
int Adj_listSearch(Vertex* h, int key);				/*�ϳ��� ������ ���� ������ �ٸ� ������ ��������Ʈ ���� Ȯ�� �Լ�*/
void push(int num);									/*�������� ���� �ϳ��� ����*/
int pop();											/*���ÿ��� ���� �ϳ� ��������*/
FnR* createQ();										/*Q ���� �Լ�*/
int isempty(FnR* x);								/*�ش� Q�� ���� ���� Ȯ��*/
void enQ(FnR* x, int val);							/*�ϳ��� ������ ����*/
int deQ(FnR* x);									/*�ϳ��� ������ ��������*/


int main()
{	/*������ ��� ����� ���� �⺻���� ���� ����.*/
	int index, edgeU, edgeV, DFS, BFS;
	char command;
	Graph* g = NULL;
	
	do
	{	/*�Էµ� commamd�� ���� ������ ��� ����*/
		printMenu();
		scanf(" %c", &command);
		
		switch (command)
		{
			case 'c': case 'C':
			{
				createGraph(&g);
				break;
			}
			case 'd': case 'D':
			{	/*������ ������ �ش� ��� ���� ���� �ٽ� c��� ����ʿ�.*/
				destroyGraph(g);
				free(g);
				g = NULL; 
				break;
			}
			case 'i': case 'I':
			{	/* ������Ű�� ���� ��ġ�� ���� �Է� �� �ش� ��ġ�� ��������*/
				printf("[Vertex range] = 0 ~ 19]\n");
				printf("Your key : ");
				scanf("%d", &index);
				insertVertex(g, index);
				break;
			}
			case 't': case 'T':
			{	/*������Ű�� ���� ��ġ�� ���� �Է� �� �ش� ��ġ�� ���� ����.
				�ش��� ���� ���� �ٸ� ��ġ�� �ִ� �ش� ������ ������ �����鵵 
				��� �����Ǿ�� ��.(���� �Ϸ�)*/
				printf("[Vertex range] = 0 ~ 19]\n");
				printf("Your key : ");
				scanf("%d", &index);
				deleteVertex(g, index);
				break;
			}
			case 'p': case 'P':
			{
				printGraph(g);
				break;
			}
			case 'e': case 'E':
			{	/*������ ������Ű�� ���� ��ġ�� ���� ��ġ 2�� �Է� ���� ��, ���� ���� ���� �Ǵ� ����
				��ȿ�� ���� �����Ѵٸ� ���� ����. */
				printf("[Vertex range] = 0 ~ 19]\n");
				printf("Vertex u : ");
				scanf("%d", &edgeU);
				printf("Vertex v : ");
				scanf("%d", &edgeV);
				insertEdge(g, edgeU, edgeV);
				break;
			}
			case 'g': case 'G':
			{	/*������Ű�� ���� ��ġ�� ������ġ 2�� �Է¹��� ��, ���� �����ϴ��� �Ǵ� ���� ����.*/
				printf("[Vertex range] = 0 ~ 19]\n");
				printf("Vertex u : ");
				scanf("%d", &edgeU);
				printf("Vertex v : ");
				scanf("%d", &edgeV);
				deleteEdge(g, edgeU, edgeV);
				break;
			}
			case 'f': case 'F':
			{	/*DFS ����(�Ʒ� �Լ����� �󼼼���)*/
				printf("[Vertex range] = 0 ~ 19]\n");
				printf("Your key : ");
				scanf("%d", &DFS);
				depthFS(g, DFS);
				break;
			}
			case 's': case 'S':
			{	/*BFS ����(�Ʒ� �Լ����� �󼼼���)*/
				printf("[Vertex range] = 0 ~ 19]\n");
				printf("Your key : ");
				scanf("%d", &BFS);
				breadthFS(g, BFS);
				break;
			}
			case 'q': case 'Q':
			{
				if(g != NULL)
				{	/*���α׷� ���� ����� ��� ������ �׷����� �������� �ʾҴٸ� ���� ����
					���α׷� ����.*/
					destroyGraph(g);
					free(g); 
					printf("The program has been terminated");	
				}
				break;
			}
			default:
			{ 
				printf("\n       >>>>>   Concentration!!   <<<<<     \n");
				break;
			}
		}
	} while (command != 'q' && command != 'Q');
	
	return 0;
}

/* �䱸�Լ� Define */
void createGraph(Graph** temp)
{
	if (*temp != NULL)
	{	/*������ �׷����� �����ߴٸ� �ܼ� �ʱ�ȭ
		(main������ �׷��� �����ͱ��� �Ҵ����� ������,
		�ش��Լ� ���ο����� �ǽ����� ����.)*/
		destroyGraph(*temp);
		return;
	}
	
		int i;
		*temp = (Graph*)malloc(sizeof(Graph)); /*�׷����� ����Ű�� �޸� �Ҵ�*/
		(*temp)->vlist = (VertexHead*)malloc(sizeof(VertexHead) * MAX_VERTEX); /*���� ������ ����ų vlist �迭 �����Ҵ�*/
	
		for(i = 0;i < MAX_VERTEX; i++)
		{	/*�ش� vlist�� index�� �����迭�� ��� NULL �� FALSE�� �ʱ�ȭ*/
			(*temp)->vlist[i].head = NULL;
			visitmark_DFS[i] = FALSE;
			visitmark_BFS[i] = FALSE;
			vflag[i] = FALSE;
		}
				
	return;		
}
 
void destroyGraph(Graph* temp)
{
	if(temp == NULL)
	{	/*����ó��*/
		printf("The graph hasn't been initialized, use the funtion 'C' \n");
		return ;
	}
	
	int i;
	Vertex* cur;
	Vertex* prev;
	
	for(i = 0; i < MAX_VERTEX; i++)
	{	/*for���� �ݺ��ϸ� �������� ���θ� ��Ÿ���� vflag�迭�� ���ο� ����
		������ �ǳʶٰų� �ش� ������ ������ ��ȸ�ϸ� �޸� ����*/
		cur = temp->vlist[i].head;
		
		if(vflag[i] == FALSE) continue;
		
		while (cur->link != NULL)
		{
			prev = cur;
			cur = cur->link;
			free(prev);
		}
		temp->vlist[i].head = NULL;
		vflag[i] = FALSE;
		visitmark_DFS[i] = FALSE;
		visitmark_BFS[i] = FALSE;
	} 
}

int insertVertex(Graph* temp, int index)
{ 
	if(temp == NULL)
	{	/*����ó��*/
		printf("The graph hasn't been initialized, use the funtion 'C' \n");
		return 1;
	}
	if(vflag[index] == TRUE)
	{	/*�̹� ������ �����ϴ°���� ó��*/
		printf("The Vertex is already exist\n");
		return 1;
	}
	if(index > 19 || index < 0)
	{	/*������ ����� �� �Է½� ����ó��*/
		printf("There's nothing to insert(you entered wrong vertex number)\n");
		return 1;
	}
	/*���� �ϳ� �����Ҵ� ���� �Է¹��� ������ ��ġ�� ���� �� �����迭 ����.*/
	Vertex* cur = (Vertex*)malloc(sizeof(Vertex));

	temp->vlist[index].head = cur;
	cur->link = NULL;
	vflag[index] = TRUE;
	
	return 0;
} 

int insertEdge(Graph* temp, int u, int v)
{
	if(temp == NULL)
	{
		printf("The graph hasn't been initialized, use the funtion 'C' \n");
		return 1;
	}
	if(u > 19 || u < 0)
	{	/*������ ����� �� �Է½� ����ó��*/
		printf("There's nothing to insert(you entered wrong vertex number)\n");
		return 1;
	}
	if(v > 19 || v < 0)
	{	/*������ ����� �� �Է½� ����ó��*/
		printf("There's nothing to insert(you entered wrong vertex number)\n");
		return 1;
	}
	if(vflag[u] == FALSE || vflag[v] == FALSE)
	{	/*������ �����ϴ��� Ȯ��.*/
	 	printf("The vertex isn't exist in the graph\n");
	 	return 1;
	}
	
	int tempU, tempV;
	Vertex* checkU  = temp->vlist[u].head;
	Vertex* checkV  = temp->vlist[v].head;
	
	tempU = Adj_listSearch(checkU, v);
	tempV = Adj_listSearch(checkV, u);
	/*�ΰ��� ���� ���̿� ������ �����ϴ��� Ȯ��*/
	if(tempU == 1 && tempV == 1)
	{
		printf("There's an edge between Vertex %d and %d\n", u, v);
		return 1;
	}
	/*���� ���ٸ�, ������ ������ ��������Ʈ�� ���� �������� ����*/
  	Vertex* newedgeU, *newedgeV;
  	Vertex* U  = temp->vlist[u].head;
  	Vertex* V  = temp->vlist[v].head;
	  	
  	newedgeU = (Vertex*)malloc(sizeof(Vertex));
  	newedgeU->num = u;
  	newedgeU->link = NULL;
	  	
  	newedgeV = (Vertex*)malloc(sizeof(Vertex));
  	newedgeV->num = v;
  	newedgeV->link = NULL;
	  	
  	while(U->link != NULL)		
  		U = U->link;
	U->link = newedgeV;
		
	while(V->link != NULL)		
  		V = V->link;
  	V->link = newedgeU;
  	
	return 0;	
}

int deleteVertex(Graph* temp, int index)
{	
	if(temp == NULL)
	{
		printf("The graph hasn't been initialized, use the funtion 'C' \n");
		return 1;
	}
	if(vflag[index] == FALSE)
	{
		printf("There's nothing to delete(you entered wrong vertex number)\n");
		return 1;
	}
	if(index > 19 || index < 0)
	{	/*������ ����� �� �Է½� ����ó��*/
		printf("There's nothing to delete(you entered wrong vertex number)\n");
		return 1;
	}
	
	Vertex* cur;
	Vertex* prev;
	Vertex* ptr;
	int i = 0;

	for(i = 0;i < MAX_VERTEX; i++)
	{
		ptr = temp->vlist[i].head;
		if(vflag[i] == FALSE || i == index)  /*�ش� i�� ������ ���ų�, �����ؾ��� ��ġ�� �´ٸ� �ǳʶٱ�*/
			continue;
		else
			Adj_listDelete(ptr, index);
	}// ������ ������ ���õ� �ٸ� ������ ���� ����Ʈ�� �����ϴ� ����. 
	
	cur = temp->vlist[index].head;
	while (cur->link != NULL)
	{	/*����ڷκ��� �Է¹��� ��ġ�� ������ �����ϴ� ����, �������� �����迭 ����*/
		prev = cur;
		cur = cur->link;
		free(prev);
	}
	vflag[index] = FALSE;
	
	return 0;
}

int deleteEdge(Graph* temp, int u, int v)
{
	if(temp == NULL)
	{
		printf("The graph hasn't been initialized, use the funtion 'C' \n");
		return 1;
	}
	if(u > 19 || u < 0)
	{	/*������ ����� �� �Է½� ����ó��*/
		printf("There's nothing to delete(you entered wrong vertex number)\n");
		return 1;
	}
	if(v > 19 || v < 0)
	{	/*������ ����� �� �Է½� ����ó��*/
		printf("There's nothing to delete(you entered wrong vertex number)\n");
		return 1;
	}
	if(vflag[u] == FALSE || vflag[v] == FALSE)
	{	/*������ �����ϴ��� Ȯ��.*/
	 	printf("The vertex isn't exist in the graph\n");
	 	return 1;
	}
	
	int tempU, tempV;
	Vertex* checkU  = temp->vlist[u].head;
	Vertex* checkV  = temp->vlist[v].head;
	
	tempU = Adj_listSearch(checkU, v);
	tempV = Adj_listSearch(checkV, u);
	
	if(tempU == 0 || tempV == 0)
	{	/*�ش� ������ ���� ����Ʈ�� ���Ǵ� ������ ���Ḯ��Ʈ�� �ִ��� Ȯ�� �� �ϳ��� �������� ����ó��*/
		printf("There's Nothing to delete between vertex %d and %d\n", u, v);
		return 1;
	}
	/*�Է� u, v�� ���� ��������Ʈ ���� ����, �ش� �������� ������ ������� ��.*/
	Adj_listDelete(checkU, v);
	Adj_listDelete(checkV, u);
	
	return 0;
}

void depthFS(Graph* temp, int V)
{
	if(temp == NULL)
	{
		printf("The graph hasn't been initialized, use the funtion 'C' \n");
		return ;
	}
	if(V > 19 || V < 0)
	{	/*������ ����� �� �Է½� ����ó��*/
		printf("There's nothing to search(you entered wrong vertex number)\n");
		return ;
	}
	if(temp->vlist[V].head == NULL)
	{	/*�Է¹��� �׷����� �׷����� �ʱ�ȭ �Ǿ��ִ»����� ó��*/
		printf("The vertex hasn't been initialized, use the funtion 'I' \n");
		return ;
	}
	/*�Է¹��� �� ���� ���� ���� ����*/
	int i;
	/*�ٸ� ������ �������� ��Ž�� �� ��츦 ���� �湮�迭 ���� �ʱ�ȭ.*/
	for(i=0; i<MAX_VERTEX; i++)
		visitmark_DFS[i] = FALSE;
	
	Vertex* ver;
	top = NULL;
	push(V);
	visitmark_DFS[V] = TRUE;
	printf(" %d", V);
	
	while(top != NULL)
	{	/*�Է¹��� ��ġ�� �������� ��������Ʈ�� ��ȸ�ϸ� �湮�� ������ ��� �ǳʶٰ�,
		 ������ ������ ���� ������ ���ÿ� push���� ������ �� ������(�����ϴ� ��� ������ ���) ���̿켱��ȸ �ݺ� */
		ver = temp->vlist[V].head->link;
		while(ver != NULL)
		{  
			if(visitmark_DFS[ver->num] == FALSE)
			{ 
				push(ver->num);
				visitmark_DFS[ver->num] = TRUE;
				printf(" %d", ver->num);
				V = ver->num;
				ver = temp->vlist[V].head->link; //
			
			}
			else ver = ver->link;
		}
		V = pop();
	}
	printf("\n");
}

void breadthFS(Graph* temp, int V)
{
	if(temp == NULL)
	{
		printf("The graph hasn't been initialized, use the funtion 'C' \n");
		return ;
	}
	if(V > 19 || V < 0)
	{	/*������ ����� �� �Է½� ����ó��*/
		printf("There's nothing to search(you entered wrong vertex number)\n");
		return ;
	}
	if(temp->vlist[V].head == NULL)
	{	/*�Է¹��� �׷����� �׷����� �ʱ�ȭ �Ǿ��ִ»����� ó��*/
		printf("The vertex hasn't been initialized, use the funtion 'I' \n");
		return ;
	}
	
	int i;
	/*�ٸ� ������ �������� ��Ž�� �� ��츦 ���� �湮�迭 ���� �ʱ�ȭ.*/
	for(i=0; i<MAX_VERTEX; i++)
		visitmark_BFS[i] = FALSE;
	
	/*���� �Է¹��� ��ġ�� �������� ��ȸ ����.*/
	Vertex* ver;
	FnR* Q;
	Q = createQ();
	visitmark_BFS[V] = TRUE;
	printf(" %d", V);
	enQ(Q, V);
	
	while(! isempty(Q))
	{	/*���̿켱��ȸ�� ����������, �Է¹��� ��ġ�� �������� ��������Ʈ�� ��ȸ�ϸ� �湮�� ������ ��� �ǳʶٰ�,
		 ������ ������ ���� ������ ���ÿ� enQueue���� Q�� �� ������(�����ϴ� ��� ������ ���) ���̿켱��ȸ �ݺ�*/
		V = deQ(Q);
		ver = temp->vlist[V].head;
		ver = ver->link;
		while(ver != NULL)
		{
			if(visitmark_BFS[ver->num] == FALSE)
			{
				visitmark_BFS[ver->num] = TRUE;
				printf(" %d", ver->num);
				enQ(Q, ver->num);
			}
			ver = ver->link;
		}	
	}
	printf("\n");
}

void printGraph(Graph* temp)
{
	if(temp == NULL)
	{
		printf("Nothing to print\n");
		return;
	}
	
	int i;
	Vertex* ptr;
	printf("\n--------------------------------- [Instruction] ------------------------------------");
	printf("\n--------- [none : no vertex] | [only Head : Vertex exist but, has no edge] ---------");
	printf("\n------------------------------------------------------------------------------------");
	printf("\n--------------- [Format] ------------> (Vertex : u, Vertex v) <---------------------");
	printf("\n------------------------------------------------------------------------------------");
	
	for(i = 0; i < MAX_VERTEX; i++)
	{	/*�ִ� �׷��� ũ�⸸ŭ ��ȸ�ϸ� ��常 �ִ���, ��嵵 ������, ������ �ִٸ� ��� ������ ���*/
		ptr = temp->vlist[i].head;
		
		if(vflag[i] == FALSE)
			printf("\n adj_list of Vretex %d : none ", i);
		else if(ptr->link == NULL)
			printf("\n adj_list of Vretex %d : only Head ", i);
		else
		{
			printf("\n adj_list of Vretex %d : ", i);
			while(ptr->link != NULL)
			{
				printf(" (%d, %d) ", i, ptr->link->num);
				ptr = ptr->link;
			}
		}
	}
	printf("\n");
}

/* �����Լ� Define */
void printMenu()
{	/* �޴� ����ϴ� �Լ�.*/
	printf("----------------------------------------------------------------\n");
	printf("                        Graph & Search                          \n");
	printf("----------------------------------------------------------------\n");
	printf("------------ [2017038102] --------------- [�ֿ뼮] -------------\n");
	printf(" CreateGraph       = C           insertEdge      = E\n");
	printf(" destroyGraph      = D           deleteEdge      = G\n");
	printf(" insertVertex      = I           D First Search  = F\n");
	printf(" deleteVertex      = T           B First Search  = S\n");
	printf(" printGraph        = P           Quit            = Q\n");
	printf("----------------------------------------------------------------\n");
	printf("Command = ");
}

void Adj_listDelete(Vertex* h, int key)
{	/*����Ʈ ��ȸ�ϸ� key�� ������ ���Ḯ��Ʈ(����) ����.*/
	Vertex* cur;
	Vertex* prev; 
	
	cur = h; // ù��° ��带 ����Ŵ

	while(cur->link != NULL && cur->num != key) // NULL�� �ƴѵ��� ����Ʈ ��ȸ
	{
		prev = cur;
		cur = cur->link;
	}
	
	if(cur->num == key && cur->link != NULL) // �ڿ� ��ũ�� �ִٴ� ��; 
	{
		prev->link = cur->link;
		free(cur);
	}
	else if(cur->num == key && cur->link ==NULL)// ������ ��尡 ���� �ڿ� �����ϴ� �ǹ�. 
	{
		prev->link = NULL;
		free(cur);
	} 
	return;
}

int Adj_listSearch(Vertex* h, int key)
{	/*����Ʈ ��ȸ�ϸ� key(����) �˻��ϸ� ������ ��� ������ ��ȯ.*/
	Vertex* cur;
	cur = h;
	
	while(cur->link != NULL && cur->num != key)
		cur = cur->link;
		
	if(cur->num == key) return 1;
	else return 0;
}

void push(int num)
{	/*������ Ǫ�� ��� �Ѱ��� �����Ҵ� �ް�, �������� �������� top�� �ش� ���� ����Ŵ.*/
	stacknode* temp = (stacknode*)malloc(sizeof(stacknode));
	temp->data = num;
	temp->link = top;
	top = temp;
}

int pop()
{	/*�������� �����͸� ����Ű�� �ӽú��� ���� ����, top�� ��ġ�� ���� �����͸� ��ȯ �� top������ ����.*/
	int val;
	stacknode* temp = top;
	
	if(top == NULL)	return 0;
	
	else
	{
		val = temp->data;
		top = temp->link;
		free(temp);
		return val;
	}
}

FnR* createQ()
{	/*Q�� ��,�� �� �ʱ� �����ϴ� �Լ�.*/
	FnR* temp;
	temp = (FnR*)malloc(sizeof(FnR));
	temp->front = NULL;
	temp->rear = NULL;
	return temp;	
}

int isempty(FnR* x)
{	/*����ִ��� Ȯ�ι� ���� ���� ������ ��ȯ.*/
	if(x->front == NULL) return 1;
	else return 0;
}

void enQ(FnR* x, int val)
{	/*�Է¹��� ���� ������ �������� �ش� Q��忡 �� �ʱ�ȭ ���� Q�� ����.*/
	Qnode* newnode = (Qnode*)malloc(sizeof(Qnode));
	newnode->data = val;
	newnode->link = NULL;
	
	if(x->front == NULL)
	{
		x->front = newnode;
		x->rear = newnode;
	}
	else
	{
		x->rear->link = newnode;
		x->rear = newnode;
	}
}

int deQ(FnR* x)
{	/*Q���� ���� ����ִ��� Ȯ�� ���� ���� �ִٸ� �� ��ȯ ���� front ������ ����.*/
	Qnode* Q = x->front;
	int A;
	if(isempty(x)) return 0;
	else
	{
		A = Q->data;
		x->front = x->front->link;
		if(x->front == NULL)
			x->rear = NULL;
		free(Q);
		return A;		
	}
}






