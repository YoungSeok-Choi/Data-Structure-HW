#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_SIZE		20

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

/*���ð� ť, �ʿ��Ұ� �����ϴ�./*/
int vertnum = 0; 									/*vertex�� ������ ��Ÿ���� ���� ����*/
int visitflag[MAX_VERTEX_SIZE]; 					/*�湮���θ� ��Ÿ���� ������ �迭.*/ 

/*�䱸�Լ� Prototype*/
void createGraph(Graph** temp);						/* empty graph creation */
void destroyGraph(Graph* temp); 					/* deallocating all allocated memory */
void insertVertex(Graph* temp, int Vertex); 		/* vertex insertion */
void deleteVertex(Graph* temp, int Vertex); 		/* vertex deletion */
void insertEdge(Graph* temp, int u, int v); 		/* new edge creation between two vertices */
void deleteEdge(Graph* temp, int u, int v); 		/* edge removal */
void depthFS(Graph* temp, int Vetex);				/* depth firt search using stack */
void breadthFS(Graph* temp, int Vetex);				/* breadth first search using queue */
void printGraph(Graph* temp);						/* printing graph with vertices and edges */

/*�����Լ� Prototype*/
void printMenu();

int main()
{
	int command, ver;
	Graph* g = NULL;

	printMenu();
	scanf("%d", &command);

	do
	{
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
				printf("Your key : ");
				scanf("%d", &ver);
				insertVertex(g, ver);
				break;
			}
			case 't': case 'T':
			{
				printf("Your key : ");
				scanf("%d", &ver);
				destroyGraph(g, ver);
				break;
			}
			case 'p': case 'P':
			{

				break;
			}
			case 'e': case 'E':
			{

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
	if (temp != NULL)
		destroyGraph(temp);

	*temp = (Graph*)malloc(sizeof(VertexHead) * MAX_VERTEX_SIZE);
}

void destroyGraph(Graph* temp)
{

}

void insertVertex(Graph* temp, int Vertex)
{

}

void insertEdge(Graph* temp, int u, int v)
{

}


void deleteVertex(Graph* temp, int Vertex)
{

}

void deleteEdge(Graph* temp, int u, int v)
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
