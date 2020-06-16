#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX		20
#define TRUE	1
#define FALSE	0

typedef struct Vertex
{  													
	int num; 										/*�׷����� ������ data�� �ƴ� Identity*/
	struct Vertex* link;							/*������ ���� vertex������Ű�� ��ũ(���� ����Ʈ).*/
} Vertex;

typedef struct VertexHead
{ 													/*vlist �� ������ �ε����� ������ �� ����. �ش� ������ ������ vlist �� index�� ����.*/
	Vertex* head;
} VertexHead;

typedef struct Graph
{ /*list of all vertices : vilst[�ƽ�_���ؽ�]*/
	VertexHead* vlist;
} Graph;

/*���ð� ť, �ʿ��Ұ� �����ϴ�.*/
int vNum = 0;
int visitmark[MAX_VERTEX]; 					/*�湮���θ� ��Ÿ���� ������ �迭.*/ 
int vflag[MAX_VERTEX];

/*�䱸�Լ� Prototype*/
void createGraph(Graph** temp);						/* empty graph creation */
void destroyGraph(Graph* temp); 					/* deallocating all allocated memory */
int insertVertex(Graph* temp, int index); 			/* vertex insertion */
int deleteVertex(Graph* temp, int index); 			/* vertex deletion */
int insertEdge(Graph* temp, int u, int v); 			/* new edge creation between two vertices */
int deleteEdge(Graph* temp, int u, int v); 			/* edge removal */
void depthFS(Graph* temp, int Vetex);				/* depth firt search using stack */
void breadthFS(Graph* temp, int Vetex);				/* breadth first search using queue */
void printGraph(Graph* temp);						/* printing graph with vertices and edges */

/*�����Լ� Prototype*/
void printMenu();

int main()
{
	int index, edgeU, edgeV;
	char command;
	Graph* g = NULL;

	do
	{
		/*
			printf("----------------------------------------------------------------\n");
			printf("                        Graph & Search                          \n");
			printf("----------------------------------------------------------------\n");
			printf("===========[2017038102]===================[�ֿ뼮]==============\n");
			printf(" CreateGraph       = c           insertEdge      = e\n");
			printf(" destroyGraph      = d           deleteEdge      = g\n");
			printf(" insertVertex      = i           depthFS         = f\n");
			printf(" deleteVertex      = t           breadthFS       = s\n");
			printf(" printGraph        = p           Quit            = q\n");
			printf("----------------------------------------------------------------\n");
			printf("Command = ");		
		*/	
		
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
			{
				destroyGraph(g);
				break;
			}
			case 'i': case 'I':
			{
				printf("Your key(Vertex range = 0 ~ 19) : ");
				scanf("%d", &index);
				insertVertex(g, index);
				break;
			}
			case 't': case 'T':
			{
				/*printf("Your key : ");
				scanf("%d", &index);
				destroyGraph(g, index);*/
				break;
			}
			case 'p': case 'P':
			{
				printGraph(g);
				break;
			}
			case 'e': case 'E':
			{
				printf("\n(Vertex range = 0 ~ 19)");
				printf("\nVertex u : ");
				scanf("%d", &edgeU);
				printf("Vertex v : ");
				scanf("%d", &edgeV);
				insertEdge(g, edgeU, edgeV);
				break;
			}
			case 'g': case 'G':
			{

				break;
			}
			case 'f': case 'F':
			{

				break;
			}
			case 's': case 'S':
			{

				break;
			}
			case 'q': case 'Q':
			{
				
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
	int i;
	if (*temp != NULL)
	{
		//destroyGraph(*temp);
		printf("��� ������ �Ҵ����� �Ϸ�!\n");
		return;
	}
		
	*temp = (Graph*)malloc(sizeof(Graph)); //���� �׷��� ����ü  
	(*temp)->vlist = (VertexHead*)malloc(sizeof(VertexHead) * MAX_VERTEX); //�켱���� ������....���� ����. 
	
	for(i = 0;i < MAX_VERTEX; i++)
	{
		//(*temp)->vlist[i] = NULL; �ϴ� ���� �÷��׷� �սô�... 
		visitmark[i] = FALSE;
		vflag[i] = FALSE;
	}		
	return;
}
// �ϴ� �Ϸ�. 
void destroyGraph(Graph* temp)
{

}

int insertVertex(Graph* temp, int index)
{ 
	if(vflag[index] == TRUE)
	{
		printf("The Vertex is already exist\n");
		return 1;
	}
	
	if(index > 19 || index < 0)
	{
		printf("There's nothing to insert(you entered wrong index number)\n");
		return 1;
	}
	
	Vertex* cur = (Vertex*)malloc(sizeof(Vertex));

	temp->vlist[index].head = cur;
	cur->link = NULL;
	vflag[index] = TRUE;
	
	/*
	VertexHead cur1;
	Vertex *cur = (Vertex*)malloc(sizeof(Vertex));
	
	cur1 = temp->vlist[index];
	cur1 = cur;
	cur->link = NULL;
	vflag[index] = TRUE;
	*/
	return 0;
} // �ϴ� �н�. 

int insertEdge(Graph* temp, int u, int v)
{
	 if(vflag[u] == FALSE || vflag[v] == FALSE)
	 {
	 	printf("The vertex isn't exist in the graph\n");
	 	return 1;
	 }
	  else
	  {
	  	
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
	printf("���� �̻��մϴ�.. ���� ��Ȯ�� ���� �ȵȰ� �����ϴ�\n");
	return 1;
}

int deleteVertex(Graph* temp, int Vertex)
{

}

int deleteEdge(Graph* temp, int u, int v)
{

}

void depthFS(Graph* temp, int Vetex)
{

}

void breadthFS(Graph* temp, int Vetex)
{

}

void printGraph(Graph* temp)
{
	int i;
	Vertex* ptr;
	
	for(i = 0; i < MAX_VERTEX; i++)
	{
		ptr = temp->vlist[i].head;
		
		if(vflag[i] == FALSE)
			printf("\n %d ���� ������ ��������Ʈ : - ", i);
		else
		{
			printf("\n %d ���� ������ ��������Ʈ : ", i);
			while(ptr->link != NULL)
			{
				printf(" (%d, %d) ", i, ptr->link->num);
				ptr = ptr->link;
			}
			printf("\n");
		}
	}
}
/* �����Լ� Define */
void printMenu()
{
	printf("----------------------------------------------------------------\n");
	printf("                        Graph & Search                          \n");
	printf("----------------------------------------------------------------\n");
	printf("===========[2017038102]===================[�ֿ뼮]==============\n");
	printf(" CreateGraph       = c           insertEdge      = e\n");
	printf(" destroyGraph      = d           deleteEdge      = g\n");
	printf(" insertVertex      = i           depthFS         = f\n");
	printf(" deleteVertex      = t           breadthFS       = s\n");
	printf(" printGraph        = p           Quit            = q\n");
	printf("----------------------------------------------------------------\n");
	printf("Command = ");
}
