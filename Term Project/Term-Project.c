#include <stdio.h>
#include <stdlib.h>

/*그래프의 최대 크기 및 전역 배열의 논리값 초기화.*/
#define MAX_VERTEX		20
#define TRUE	1
#define FALSE	0

typedef struct Vertex
{  													
	int num; 					/*그래프의 정정이 가지는 data가 아닌 Identity*/
	struct Vertex* link;		/*다음의 인접 vertex를가르키는 링크(연결 리스트).*/
} Vertex;

typedef struct VertexHead
{ 								/*vlist 의 각각의 인덱스에 생성이 될 정점. 해당 정점의 구분은 vlist 의 index로 구분.*/
	Vertex* head;
} VertexHead;

typedef struct Graph
{ 								/*vlist 가르키는 name*/					
	VertexHead* vlist;
} Graph;

/*DFS, BFS 검색을 위한 자료구조 set up*/
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

/*기타 자료구조 set up*/
stacknode* top;
int visitmark_DFS[MAX_VERTEX]; 						/*DFS검색 시 방문여부를 나타내는 배열.*/ 
int visitmark_BFS[MAX_VERTEX];						/*BFS검색 시 방문여부를 나타내는 배열.*/ 
int vflag[MAX_VERTEX];								/*그래프의 정점 존재 여부를 나타내는 배열*/

/*요구함수 Prototype*/
void createGraph(Graph** temp);						/* empty graph creation */
void destroyGraph(Graph* temp); 					/* deallocating all allocated memory */
int insertVertex(Graph* temp, int index); 			/* vertex insertion */
int deleteVertex(Graph* temp, int index); 			/* vertex deletion */
int insertEdge(Graph* temp, int u, int v); 			/* new edge creation between two vertices */
int deleteEdge(Graph* temp, int u, int v); 			/* edge removal */
void depthFS(Graph* temp, int V);					/* depth firt search using stack */
void breadthFS(Graph* temp, int V);					/* breadth first search using queue */
void printGraph(Graph* temp);						/* printing graph with vertices and edges */

/*개별함수 Prototype*/
void printMenu();									/*메뉴를 출력하는 함수.*/
void Adj_listDelete(Vertex* h, int key);			/*하나의 정점에 대해 연관된 다른 정점의 인접 리스트 삭제 함수*/
int Adj_listSearch(Vertex* h, int key);				/*하나의 정점에 대한 연관된 다른 정점의 인접리스트 존재 확인 함수*/
void push(int num);									/*스택으로 정수 하나를 삽입*/
int pop();											/*스택에서 정수 하나 가져오기*/
FnR* createQ();										/*Q 생성 함수*/
int isempty(FnR* x);								/*해당 Q의 공백 여부 확인*/
void enQ(FnR* x, int val);							/*하나의 정수를 삽입*/
int deQ(FnR* x);									/*하나의 정수를 가져오기*/


int main()
{	/*각각의 기능 사용을 위한 기본적인 변수 선언.*/
	int index, edgeU, edgeV, DFS, BFS;
	char command;
	Graph* g = NULL;
	
	do
	{	/*입력된 commamd에 따라 각각의 기능 실행*/
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
			{	/*완전한 삭제로 해당 기능 실행 이후 다시 c기능 사용필요.*/
				destroyGraph(g);
				free(g);
				g = NULL; 
				break;
			}
			case 'i': case 'I':
			{	/* 생성시키고 싶은 위치의 정수 입력 후 해당 위치에 정점생성*/
				printf("[Vertex range] = 0 ~ 19]\n");
				printf("Your key : ");
				scanf("%d", &index);
				insertVertex(g, index);
				break;
			}
			case 't': case 'T':
			{	/*삭제시키고 싶은 위치의 정수 입력 후 해당 위치의 정점 삭제.
				해당기능 실행 이후 다른 위치에 있는 해당 정점과 연관된 간선들도 
				모두 삭제되어야 함.(구현 완료)*/
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
			{	/*간선을 생성시키고 싶은 위치의 정점 위치 2개 입력 받은 뒤, 정점 존재 여부 판단 이후
				유효한 정점 존재한다면 간선 생성. */
				printf("[Vertex range] = 0 ~ 19]\n");
				printf("Vertex u : ");
				scanf("%d", &edgeU);
				printf("Vertex v : ");
				scanf("%d", &edgeV);
				insertEdge(g, edgeU, edgeV);
				break;
			}
			case 'g': case 'G':
			{	/*삭제시키고 싶은 위치의 정점위치 2개 입력받은 뒤, 실제 존재하는지 판단 이후 삭제.*/
				printf("[Vertex range] = 0 ~ 19]\n");
				printf("Vertex u : ");
				scanf("%d", &edgeU);
				printf("Vertex v : ");
				scanf("%d", &edgeV);
				deleteEdge(g, edgeU, edgeV);
				break;
			}
			case 'f': case 'F':
			{	/*DFS 실행(아래 함수에서 상세설명)*/
				printf("[Vertex range] = 0 ~ 19]\n");
				printf("Your key : ");
				scanf("%d", &DFS);
				depthFS(g, DFS);
				break;
			}
			case 's': case 'S':
			{	/*BFS 실행(아래 함수에서 상세설명)*/
				printf("[Vertex range] = 0 ~ 19]\n");
				printf("Your key : ");
				scanf("%d", &BFS);
				breadthFS(g, BFS);
				break;
			}
			case 'q': case 'Q':
			{
				if(g != NULL)
				{	/*프로그램 종료 명령의 경우 기존의 그래프가 삭제되지 않았다면 삭제 이후
					프로그램 종료.*/
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

/* 요구함수 Define */
void createGraph(Graph** temp)
{
	if (*temp != NULL)
	{	/*기존에 그래프가 존재했다면 단순 초기화
		(main에서는 그래프 포인터까지 할당해제 했지만,
		해당함수 내부에서는 실시하지 않음.)*/
		destroyGraph(*temp);
		return;
	}
	
		int i;
		*temp = (Graph*)malloc(sizeof(Graph)); /*그래프를 가르키는 메모리 할당*/
		(*temp)->vlist = (VertexHead*)malloc(sizeof(VertexHead) * MAX_VERTEX); /*위의 변수가 가르킬 vlist 배열 동적할당*/
	
		for(i = 0;i < MAX_VERTEX; i++)
		{	/*해당 vlist의 index와 전역배열을 모두 NULL 및 FALSE로 초기화*/
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
	{	/*예외처리*/
		printf("The graph hasn't been initialized, use the funtion 'C' \n");
		return ;
	}
	
	int i;
	Vertex* cur;
	Vertex* prev;
	
	for(i = 0; i < MAX_VERTEX; i++)
	{	/*for문을 반복하며 정점생성 여부를 나타내는 vflag배열의 여부에 따라
		삭제를 건너뛰거나 해당 정점의 끝까지 순회하며 메모리 해제*/
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
	{	/*예외처리*/
		printf("The graph hasn't been initialized, use the funtion 'C' \n");
		return 1;
	}
	if(vflag[index] == TRUE)
	{	/*이미 정점이 존재하는경우의 처리*/
		printf("The Vertex is already exist\n");
		return 1;
	}
	if(index > 19 || index < 0)
	{	/*범위에 벗어나는 값 입력시 예외처리*/
		printf("There's nothing to insert(you entered wrong vertex number)\n");
		return 1;
	}
	/*정점 하나 동적할당 이후 입력받은 정수의 위치에 삽입 및 전역배열 수정.*/
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
	{	/*범위에 벗어나는 값 입력시 예외처리*/
		printf("There's nothing to insert(you entered wrong vertex number)\n");
		return 1;
	}
	if(v > 19 || v < 0)
	{	/*범위에 벗어나는 값 입력시 예외처리*/
		printf("There's nothing to insert(you entered wrong vertex number)\n");
		return 1;
	}
	if(vflag[u] == FALSE || vflag[v] == FALSE)
	{	/*정점이 존재하는지 확인.*/
	 	printf("The vertex isn't exist in the graph\n");
	 	return 1;
	}
	
	int tempU, tempV;
	Vertex* checkU  = temp->vlist[u].head;
	Vertex* checkV  = temp->vlist[v].head;
	
	tempU = Adj_listSearch(checkU, v);
	tempV = Adj_listSearch(checkV, u);
	/*두개의 정점 사이에 간선이 존재하는지 확인*/
	if(tempU == 1 && tempV == 1)
	{
		printf("There's an edge between Vertex %d and %d\n", u, v);
		return 1;
	}
	/*간선 없다면, 각각의 정점의 인접리스트에 가장 마지막에 삽입*/
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
	{	/*범위에 벗어나는 값 입력시 예외처리*/
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
		if(vflag[i] == FALSE || i == index)  /*해당 i에 정점이 없거나, 삭제해야할 위치가 온다면 건너뛰기*/
			continue;
		else
			Adj_listDelete(ptr, index);
	}// 삭제할 정점과 관련된 다른 정점의 연결 리스트를 삭제하는 연산. 
	
	cur = temp->vlist[index].head;
	while (cur->link != NULL)
	{	/*사용자로부터 입력받은 위치의 정점을 삭제하는 연산, 연산이후 전역배열 수정*/
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
	{	/*범위에 벗어나는 값 입력시 예외처리*/
		printf("There's nothing to delete(you entered wrong vertex number)\n");
		return 1;
	}
	if(v > 19 || v < 0)
	{	/*범위에 벗어나는 값 입력시 예외처리*/
		printf("There's nothing to delete(you entered wrong vertex number)\n");
		return 1;
	}
	if(vflag[u] == FALSE || vflag[v] == FALSE)
	{	/*정점이 존재하는지 확인.*/
	 	printf("The vertex isn't exist in the graph\n");
	 	return 1;
	}
	
	int tempU, tempV;
	Vertex* checkU  = temp->vlist[u].head;
	Vertex* checkV  = temp->vlist[v].head;
	
	tempU = Adj_listSearch(checkU, v);
	tempV = Adj_listSearch(checkV, u);
	
	if(tempU == 0 || tempV == 0)
	{	/*해당 정점의 인접 리스트의 상대되는 정점의 연결리스트가 있는지 확인 후 하나라도 없을때의 예외처리*/
		printf("There's Nothing to delete between vertex %d and %d\n", u, v);
		return 1;
	}
	/*입력 u, v에 대한 인접리스트 삭제 연산, 해당 연산으로 간선이 사라지게 됨.*/
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
	{	/*범위에 벗어나는 값 입력시 예외처리*/
		printf("There's nothing to search(you entered wrong vertex number)\n");
		return ;
	}
	if(temp->vlist[V].head == NULL)
	{	/*입력받은 그래프가 그래프만 초기화 되어있는상태의 처리*/
		printf("The vertex hasn't been initialized, use the funtion 'I' \n");
		return ;
	}
	/*입력받은 값 가장 먼저 연산 시작*/
	int i;
	/*다른 정점을 기준으로 재탐색 할 경우를 위한 방문배열 사전 초기화.*/
	for(i=0; i<MAX_VERTEX; i++)
		visitmark_DFS[i] = FALSE;
	
	Vertex* ver;
	top = NULL;
	push(V);
	visitmark_DFS[V] = TRUE;
	printf(" %d", V);
	
	while(top != NULL)
	{	/*입력받은 위치의 간선부터 인접리스트를 순회하며 방문한 정점의 경우 건너뛰고,
		 인접한 정점이 없을 때까지 스택에 push이후 스택이 빌 때까지(존재하는 모든 정점을 방분) 깊이우선순회 반복 */
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
	{	/*범위에 벗어나는 값 입력시 예외처리*/
		printf("There's nothing to search(you entered wrong vertex number)\n");
		return ;
	}
	if(temp->vlist[V].head == NULL)
	{	/*입력받은 그래프가 그래프만 초기화 되어있는상태의 처리*/
		printf("The vertex hasn't been initialized, use the funtion 'I' \n");
		return ;
	}
	
	int i;
	/*다른 정점을 기준으로 재탐색 할 경우를 위한 방문배열 사전 초기화.*/
	for(i=0; i<MAX_VERTEX; i++)
		visitmark_BFS[i] = FALSE;
	
	/*최초 입력받은 위치의 정점부터 순회 시작.*/
	Vertex* ver;
	FnR* Q;
	Q = createQ();
	visitmark_BFS[V] = TRUE;
	printf(" %d", V);
	enQ(Q, V);
	
	while(! isempty(Q))
	{	/*깊이우선순회와 마찬가지로, 입력받은 위치의 간선부터 인접리스트를 순회하며 방문한 정점의 경우 건너뛰고,
		 인접한 정점이 없을 때까지 스택에 enQueue이후 Q가 빌 때까지(존재하는 모든 정점을 방분) 넓이우선순회 반복*/
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
	{	/*최대 그래프 크기만큼 순회하며 헤드만 있는지, 헤드도 없는지, 간선이 있다면 모든 간선을 출력*/
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

/* 개별함수 Define */
void printMenu()
{	/* 메뉴 출력하는 함수.*/
	printf("----------------------------------------------------------------\n");
	printf("                        Graph & Search                          \n");
	printf("----------------------------------------------------------------\n");
	printf("------------ [2017038102] --------------- [최용석] -------------\n");
	printf(" CreateGraph       = C           insertEdge      = E\n");
	printf(" destroyGraph      = D           deleteEdge      = G\n");
	printf(" insertVertex      = I           D First Search  = F\n");
	printf(" deleteVertex      = T           B First Search  = S\n");
	printf(" printGraph        = P           Quit            = Q\n");
	printf("----------------------------------------------------------------\n");
	printf("Command = ");
}

void Adj_listDelete(Vertex* h, int key)
{	/*리스트 순회하며 key와 연관된 연결리스트(간선) 삭제.*/
	Vertex* cur;
	Vertex* prev; 
	
	cur = h; // 첫번째 노드를 가르킴

	while(cur->link != NULL && cur->num != key) // NULL이 아닌동안 리스트 순회
	{
		prev = cur;
		cur = cur->link;
	}
	
	if(cur->num == key && cur->link != NULL) // 뒤에 링크가 있다는 뜻; 
	{
		prev->link = cur->link;
		free(cur);
	}
	else if(cur->num == key && cur->link ==NULL)// 삭제할 노드가 가장 뒤에 존재하는 의미. 
	{
		prev->link = NULL;
		free(cur);
	} 
	return;
}

int Adj_listSearch(Vertex* h, int key)
{	/*리스트 순회하며 key(간선) 검색하며 각각의 경우 정수값 반환.*/
	Vertex* cur;
	cur = h;
	
	while(cur->link != NULL && cur->num != key)
		cur = cur->link;
		
	if(cur->num == key) return 1;
	else return 0;
}

void push(int num)
{	/*스택의 푸쉬 노드 한개를 동적할당 받고, 전역변수 포인터의 top을 해당 노드로 가르킴.*/
	stacknode* temp = (stacknode*)malloc(sizeof(stacknode));
	temp->data = num;
	temp->link = top;
	top = temp;
}

int pop()
{	/*전역변수 포인터를 가르키는 임시변수 생성 이후, top의 위치의 정수 데이터를 반환 및 top포인터 수정.*/
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
{	/*Q의 앞,뒤 를 초기 생성하는 함수.*/
	FnR* temp;
	temp = (FnR*)malloc(sizeof(FnR));
	temp->front = NULL;
	temp->rear = NULL;
	return temp;	
}

int isempty(FnR* x)
{	/*비어있는지 확인및 대항 정수 데이터 반환.*/
	if(x->front == NULL) return 1;
	else return 0;
}

void enQ(FnR* x, int val)
{	/*입력받은 정수 값으로 동적받은 해당 Q노드에 값 초기화 이후 Q에 삽입.*/
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
{	/*Q에서 먼저 비어있는지 확인 이후 값이 있다면 값 반환 이후 front 포인터 수정.*/
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






