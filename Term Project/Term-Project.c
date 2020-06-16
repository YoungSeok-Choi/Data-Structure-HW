#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX		20
#define TRUE	1
#define FALSE	0

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

/*스택과 큐, 필요할것 같습니다.*/
int vNum = 0;
int visitmark[MAX_VERTEX]; 					/*방문여부를 나타내는 정수형 배열.*/ 
int vflag[MAX_VERTEX];

/*요구함수 Prototype*/
void createGraph(Graph** temp);						/* empty graph creation */
void destroyGraph(Graph* temp); 					/* deallocating all allocated memory */
int insertVertex(Graph* temp, int index); 			/* vertex insertion */
int deleteVertex(Graph* temp, int index); 			/* vertex deletion */
int insertEdge(Graph* temp, int u, int v); 			/* new edge creation between two vertices */
int deleteEdge(Graph* temp, int u, int v); 			/* edge removal */
void depthFS(Graph* temp, int Vetex);				/* depth firt search using stack */
void breadthFS(Graph* temp, int Vetex);				/* breadth first search using queue */
void printGraph(Graph* temp);						/* printing graph with vertices and edges */

/*개별함수 Prototype*/
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
			printf("===========[2017038102]===================[최용석]==============\n");
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

/* 요구함수 Define */
void createGraph(Graph** temp)
{
	int i;
	if (*temp != NULL)
	{
		//destroyGraph(*temp);
		printf("모든 데이터 할당해제 완료!\n");
		return;
	}
		
	*temp = (Graph*)malloc(sizeof(Graph)); //먼저 그래프 구조체  
	(*temp)->vlist = (VertexHead*)malloc(sizeof(VertexHead) * MAX_VERTEX); //우선순위 문제음....세상에 만상에. 
	
	for(i = 0;i < MAX_VERTEX; i++)
	{
		//(*temp)->vlist[i] = NULL; 일단 뺴고 플래그로 합시다... 
		visitmark[i] = FALSE;
		vflag[i] = FALSE;
	}		
	return;
}
// 일단 완료. 
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
} // 일단 패스. 

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
	printf("뭔가 이상합니다.. 엣지 정확히 삽입 안된것 같습니다\n");
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
			printf("\n %d 번의 정점의 인접리스트 : - ", i);
		else
		{
			printf("\n %d 번의 정점의 인접리스트 : ", i);
			while(ptr->link != NULL)
			{
				printf(" (%d, %d) ", i, ptr->link->num);
				ptr = ptr->link;
			}
			printf("\n");
		}
	}
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
