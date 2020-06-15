#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_SIZE		20

typedef struct Vertex
{  													
	int num; 										/*그래프가 가지는 data가 아닌 Identity*/
	struct Vertex* link;							/*다음의 인접 vertex를가르키는 링크(연결 리스트).*/
} Vertex;

typedef struct VertexHead
{ 													/*vlist 의 각각의 인덱스에 생성이 될 정점. 해당 정점의 구분은 vlist 의 index로 구분.*/
	Vertex* head;
} VertexHead;

typedef struct Graph
{ /*list of all vertices : vilst[맥스_버텍스]*/
	VertexHead* vlist;
} Graph;

/*스택과 큐, 필요할것 같습니다./*/
int vertnum = 0; 									/*vertex의 개수를 나타내기 위한 변수*/
int visitflag[MAX_VERTEX_SIZE]; 					/*방문여부를 나타내는 정수형 배열.*/ 

/*요구함수 Prototype*/
void createGraph(Graph** temp);						/* empty graph creation */
void destroyGraph(Graph* temp); 					/* deallocating all allocated memory */
void insertVertex(Graph* temp, int Vertex); 		/* vertex insertion */
void deleteVertex(Graph* temp, int Vertex); 		/* vertex deletion */
void insertEdge(Graph* temp, int u, int v); 		/* new edge creation between two vertices */
void deleteEdge(Graph* temp, int u, int v); 		/* edge removal */
void depthFS(Graph* temp, int Vetex);				/* depth firt search using stack */
void breadthFS(Graph* temp, int Vetex);				/* breadth first search using queue */
void printGraph(Graph* temp);						/* printing graph with vertices and edges */

/*개별함수 Prototype*/
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

/* 요구함수 Define */
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
/* 개별함수 Define */
void printMenu()
{
	printf("----------------------------------------------------------------\n");
	printf("                        Graph & Search                          \n");
	printf("----------------------------------------------------------------\n");
	printf("===========[2017038102]===================[최용석]==============\n");
	printf(" CreateGraph       = c           insertEdge      = e\n");
	printf(" destroyGraph      = d           deleteEdge      = g\n");
	printf(" insertVertex      = i           depthFS         = f\n");
	printf(" deleteVertex      = t           breadthFS       = s\n");
	printf(" printGraph        = p           Quit            = q\n");
	printf("----------------------------------------------------------------\n");
	printf("Command = ");
}
