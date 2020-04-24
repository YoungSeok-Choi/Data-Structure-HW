#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

typedef enum{
	lparen = 0,
	rparen = 9,
	times = 7,
	divide = 6,
	plus = 5,
	minus = 4,
	operand = 1
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];
char postfixExp[MAX_EXPRESSION_SIZE];
char postfixStack[MAX_STACK_SIZE]; //포스트픽스로 변환시 사용할 스택
int evalStack[MAX_STACK_SIZE]; //  계산시 사용할 스택

int postfixStackTop = -1;
int evalStackTop = -1;

int evalResult = 0;

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x;
}

char postfixPop()
{
    char x;
    if(postfixStackTop == -1)
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--];
    }
    return x;
}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x;
}

int evalPop()
{
    if(evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--];
}

void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);
}

precedence getToken(char symbol)
{
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}

}

precedence getPriority(char x)
{
	return getToken(x);
}

//문자 하나를 전달받아, 포스트픽스에 츄가
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기우ㅣ한 포인터 */
	char *exp = infixExp;
	char x, X, y; //왼쪽부터 피연산자, 오른쪽괄호가 아닌 연산자, 오른쪽 연산자 를 담기위한 일시적인 변수
	char *ptr = NULL; // 모두 안전하게 초기화
	char * ptr1 = NULL;
	char *ptr2= NULL;

	ptr = &x; // 해당 변수들을 가르키도록 설정
	ptr1 = &X;
	ptr2 = &y;

	/* exp증가시키면서 문자 읽고 포스트픽스로 변경 */
		while(*exp != '\0')
		{
			x = *exp;
			precedence token;  // 토큰을 읽어들이기 위한 변수
			token = getToken(x);

			if(token == operand)
				charCat(ptr);
			else if(token == rparen) //읽어들인 토큰이 ')'기호라면
				{
					while( postfixStack[postfixStackTop] != lparen ) // '(' 기호를 만나기 전까지 반복하며 연산자들을 pop 그리고 '(' 기호를 만나면 출력하지 않고 무시
					{
						y = postfixPop();
						token = getToken(y);
						if(token == lparen)
							continue;
						else
							charCat(ptr2);
					}
				}
			else
				postfixPush(x); // 오른쪽 괄호가 아닌 일반 연산자라면 바로 스택에 푸쉬
			exp++;
		}
		do  // 위에서의 반복문이 종료가 되고 연산자들만 들어있는 스택의 데이터들을 후위연산자 문자열 배열에 입력
		{
			X = postfixPop();
			charCat(ptr1);
		}while(X != '\0');
}
void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);
	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");
}

void reset()
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';

	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation()
{
	/* postfixExp, evalStack 을 이용한 계산 */

}


int main()
{
	char command;

	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf("===========================2017038102============최용석==============\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 0;
}


/* 이번 과제를 통해 스택과 연산자 우선순위, 그리고 여러가지 유용한 함수에 대해
 * 알 수 있었습니다. 제출기간 내에 완전히 구현은 하지 못했지만 나중에라도 학습을
 * 위해 구현해보도록 할 것입니다.*/
