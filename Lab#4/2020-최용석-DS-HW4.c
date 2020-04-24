#include <stdio.h>
#include <stdlib.h> // malloc, free 를 사용하기 위한 헤더파일 include
#include <time.h> // 랜덤함수를 사용하기 위한 헤더파일 include
#include <math.h>

int** create_matrix(int row, int col);
int free_matrix(int **matrix, int row, int col);
void print_matrix(int **matrix, int row, int col);
int fill_data(int **matrix, int row, int col);
int addition_matrix(int **matrix_a, int **matrix_b, int **matrix_sum, int row, int col);
int subtraction_matrix(int **matrix_a, int **matrix_b, int **matrix_sub, int row, int col);
int transpose_matrix(int **matrix_a, int **matrix_t, int row, int col);
int multiply_matrix(int **matrix_a, int **matrix_b, int **matrix_axt, int row, int col); // lab#4 에서 명시된 함수들의 prototype
void show_menu(void); //메뉴를 보여주기 위한 함수 선언

int matrixA_flag = -1; // 행렬 A와 B가 임의의 값이 초기화 되지 않았는데 덧셈, 뺄셈 연산을 방지하기 위한 플래그 변수 선언
int matrixB_flag = -1;


int main()
{
	srand(time(NULL)); // 난수 사용을 위한 구문

	printf("------------[최용석]------------[2017038102]---------\n");
	int r, c, i; 					 // 행, 열의 값을 받을 변수와, 메뉴실행의 분기를위한 i 변수 선언
	int **matrix_A = NULL;		 // 각각의 동적할당 배열을 저장하기 위한 더블포인터 변수를 초기화 후 NULL 초기화
	int **matrix_B = NULL;
	int **matrix_sum = NULL;
	int **matrix_sub = NULL;
	int **matrix_axt = NULL;
	int **matrix_t = NULL;


	printf("만들고 싶은 2차원행렬의 행 크기값을 입력하세요 : ");  		// 행, 열의 크기를 사용자로부터 입력받음
	scanf("%d", &r);
	printf("\n만들고 싶은 2차원행렬의 열 크기값을 입력하세요 : ");
	scanf("%d", &c);

	matrix_A = create_matrix(r, c);   // 최초 2개의 2차원배열을 할당 후 반환되는 주소값을 각각의 변수에 저장(에러처리는 함수 내에 구현하였습니다.)
	matrix_B = create_matrix(r, c);

	do
	{
		show_menu();  // 숫자를 입력받아 기능을 실행
		scanf("%d", &i);

		switch(i)
		{
			case 1:
			{
				if(fill_data(matrix_A, r, c) == -1) // 함수의 비정상적 종료가 발생시 프로그램 종료.
					exit(1);
				else
				{
					printf("행렬 A\n");
					print_matrix(matrix_A, r, c);
					printf("\n");
					matrixA_flag *= -1; // 임의의 값으로 초기화 이후 전역변수 플래그 변경
				}

				if(fill_data(matrix_B, r, c) == -1)
					exit(1);
				else
				{
					printf("행렬 B\n");
					print_matrix(matrix_B, r, c);
					matrixB_flag *= -1; // 위의 명령어와 동일한 기능 수행
				}
				continue;
			}
			case 2:
			{
				if(matrixA_flag == -1 || matrixB_flag == -1) // 전역변수 flag를 사용하여 값이 할당됐는지, 이전에 할당된 값이 있는지 판단
					{
						printf("행렬 A와 B의 값이 초기화 되지 않았거나, 이미 한번 초기화 되었습니다. 1번기능을 사용한 이후 해당 기능을 사용하세요\n");
						continue;
					}

				matrix_sum = create_matrix(r, c); // 새로운 값이 할당됐으므로 새로운 2차원배열 동적할당

				if(addition_matrix(matrix_A,matrix_B,matrix_sum, r, c) == -1) // 해당 함수가 비정상종료 값을 반환시 프로그램 종료.
					exit(1);
				else
				{
					printf("행렬 A + B\n");
					print_matrix(matrix_sum, r, c); // 정상적으로 실행됐을 시 결과값 출력
				}
				continue;
			}
			case 3:
			{
				if(matrixA_flag == -1 || matrixB_flag == -1)  // case 2 와 동일한 에러처리
						{
							printf("행렬 A와 B의 값이 초기화 되지 않았거나, 이미 한번 초기화 되었습니다. 1번기능을 사용한 이후 해당 기능을 사용하세요\n");
							continue;
						}

				matrix_sub = create_matrix(r, c);

				if(subtraction_matrix(matrix_A,matrix_B, matrix_sub, r, c) == -1) //  해당 에러처리는 모든 분기의 case와 동일합니다. 아래 라인에서의 설명은 생략하겠습니다.
					exit(1);
				else
				{
					printf("행렬 A - B\n");
					print_matrix(matrix_sub, r, c);
				}
				continue;
			}
			case 4:
			{
				if(matrixA_flag == -1 || matrixB_flag == -1) // case 2 와 동일한 에러처리
					{
						printf("행렬 A와 B의 값을 먼저 초기화 한 이후 해당 기능을 사용하세요\n");
						continue;
					}

				matrix_t = create_matrix(c, r);

				if(transpose_matrix(matrix_A,matrix_t, r, c) == -1)
					exit(1);
				else
				{
					printf("행렬 A -> T\n");
					print_matrix(matrix_t, c, r);
				}
				continue;
			}
			case 5:
			{
				if(matrix_t == NULL) // 전치행렬이 없는데 곱연산을 하려는 경우의 에러처리
				{
					printf("전치행렬이 존재하지 않습니다. 먼저 전치행렬을 만들고 해당 기능을 선택하세요\n");
					continue;
				}
				else
				{
					matrix_axt = create_matrix(c, r);
					if(multiply_matrix(matrix_A,matrix_t, matrix_axt, r, c) == -1)
						exit(1);
					else
					{
						printf("행렬 A * T\n");
						print_matrix(matrix_axt, c, r);
					}
					continue;
				}
			}
			case 6:
			{
				if(free_matrix(matrix_A, r, c) == -1)
					exit(1);
				if(free_matrix(matrix_B, r, c) == -1)
					exit(1);
				if(free_matrix(matrix_sum, r, c) == -1)
					exit(1);
				if(	free_matrix(matrix_sub, r, c) == -1)
					exit(1);
				if(free_matrix(matrix_t, c, r) == -1)
					exit(1);
				if(free_matrix(matrix_axt, c, r) == -1) // 위의 함수들이 호출되면서 하나라도 에러가 발생하면 즉시 프로그램 종료.
					exit(1);
				printf("성공적으로 메모리 해제가 완료되었습니다!!\n"); //위의 구문을 전부 실행하고 에러가 없을 시 해당 문구 출력.
				continue;
			}
			case 7:
			{
				printf("프로그램 종료 메뉴를 선택하셨습니다. 프로그램을 종료합니다\n");
				exit(1);
			}
			default: // 1 ~ 7 이외의 값이 입력이 되었을 시 처리부분.
				printf("올바른 메뉴 번호를 입력하세요\n");
		}

	}while(i != 7); //입력되는 값이 7이 아닌 동안 무한반복 실행

	return 0;
}


int** create_matrix(int row, int col)
{
	int **temp = NULL; //더블포인터 주소값으ㄹ 잠시 담아놓을 local 변수
	int i; //for문을 위한 변수 선언

	if(row <= 0 || col <= 0) // 행과 열값을 각각 0이하인 값인지 검사 후 해당되면 프로그램 강제종료.
	{
		printf("행과 열의 값중 0이하인 숫자는 입력할 수 없습니다. 프로그램을 종료합니다.\n");
		exit(1); // 해당 함수가 반환값이 주소값이기 때문에 해당 오류 발생시 return value 없이 해당함수 내에서 프로그램 종료
	}
	else
	{
		temp = (int **)malloc(sizeof(int *)* row); // 행,열의 값이 유효한 경우 해당 행의 크기만큼의 포인터 배열 선언
		for(i = 0; i < row; i++)
			*(temp + i) = (int *)malloc(sizeof(int)*col); // 해당 행에다 사용자가 입력한 열의 크기만큼 연속된 int형 저장공간 할당
	}

	if(temp == NULL) //temp변수의 그릇에 초기 저장하였던 NULL값이 여전히 존재하는 경우 오류 발생 통지 후 프로그램 종료
	{
		printf("입력한 크기의 행렬이 올바르게 만들어지지 않았습니다. 다시 실행해주시기 바랍니다.\n");
		exit(1);
	}
	else
		return temp; //정상적으로 할당이 되고 main함수의 더블포인터에 해당 주소값 반환
}

int free_matrix(int **matrix, int row, int col)

{
	int i; //for문 동작을 위한 변수선언

			if(matrix == NULL) // 해당 행렬이 초기값 NULL을 가르키고 있는지 판단 후 해당되면 비정상종료값 출력
				{
					printf("해당 행렬이 할당되지 않은것 같습니다. 프로그램을 다시 실행시켜 주세요 .\n");
					return -1;
				}
			else
			{
				for(i = 0; i < row; i++)
					free(matrix[i]); // 이중포인터의 열의 첫번째 주소를 담고있는 메모리를 해제함으로써 선형적으로 할당받았던 2차원배열의 열 부분이 메모리 해제

				free(matrix); // 모든 행의 열 부분의 메모리를 해제가 완료되면 main 내에서 local로 선언된 부분에 저장되어있던 행을 가르키는 heap 공간을 할당해제
			}
	return 0;
}

void print_matrix(int **matrix, int row, int col)
{
	int i, j; // 2중 for문 동작을 위한 변수선언

		if(matrix == NULL) // 해당 행렬이 초기값 NULL을 가르키고 있는지 판단 후 해당되면 비정상종료값 출력
			{
				printf("해당 행렬이 할당되지 않은것 같습니다. 프로그램을 다시 실행시켜 주세요.\n");
				exit(1);
			}
		else // 해당 행렬의 원소들을 모두 출력
		{
			for(i = 0; i < row; i++)
			{
				for(j = 0; j < col; j++)
					printf("%7d", matrix[i][j]); // 정렬된 format으로 출력
				printf("\n");
			}
		}
}

int fill_data(int **matrix, int row, int col)
{
	int i, j;

	if(matrix == NULL)  // 해당 행렬이 초기값 NULL을 가르키고 있는지 판단 후 해당되면 비정상종료값 출력
		{
			printf("해당 행렬이 할당되지 않은것 같습니다. 프로그램을 다시 실행시켜 주세요.\n");
			return -1;
		}
	else // 유효한 값이 들어온다면 각각의 배열의 index 부분에 랜덤값을 할당.
	{
		for(i = 0; i < row; i++)
			for(j = 0; j < col; j++)
				matrix[i][j] = rand() % 20; //랜덤으로 생성된 값을 %20 연산을 함으로써 들어올 수 있는 값의 범위를 0 ~ 19로 지정
	}

	return 0;
}

int addition_matrix(int **matrix_a, int **matrix_b, int **matrix_sum, int row, int col)
{
	int i, j; // 2중 for문 동작을 위한 변수선언

			if(matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL)  // 해당 행렬이 초기값 NULL을 가르키고 있는지 판단 후 하나의 조건이라도 해당되면 비정상종료값 출력
				{
					printf("해당 행렬이 할당되지 않은것 같습니다. 프로그램을 다시 실행시켜 주세요.\n");
					return -1;
				}
			else // 위의 에러처리부분에서 해당이 되지 않는다면 행렬의 덧셈연산 수행
			{
				for(i = 0; i < row; i++)
					for(j = 0; j < col; j++)
						matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];
			}
	return 0;
}

int subtraction_matrix(int **matrix_a, int **matrix_b, int **matrix_sub, int row, int col)
{
	int i, j; // 2중 for문 동작을 위한 변수선언

			if(matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL)  // 해당 행렬이 초기값 NULL을 가르키고 있는지 판단 후 한개의 조건이라도 해당되면 비정상종료값 출력
				{
					printf("해당 행렬이 할당되지 않은것 같습니다. 프로그램을 다시 실행시켜 주세요.\n");
					return -1;
				}
			else // 위의 조건문에서 넘어온다면 에러가 없으므로 정상적인 뺄셈연산 수행
			{
				for(i = 0; i < row; i++)
					for(j = 0; j < col; j++)
						matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j];
			}
	return 0;
}

int transpose_matrix(int **matrix_a, int **matrix_t, int row, int col)
{
	int i, j, temp; // 2중 for문 동작을 위한 변수선언 및 값 교환을 위해 임시 저장할 정수형 변수 추가선언

				if(matrix_a == NULL || matrix_t == NULL)  // 해당 행렬이 초기값 NULL을 가르키고 있는지 판단 후 해당되면 비정상종료값 출력
					{
						printf("해당 행렬이 할당되지 않은것 같습니다. 프로그램을 다시 실행시켜 주세요.\n");
						return -1;
					}
				else // if문에서 에러가 발견되지 않는다면 else구문 실행
				{
					for(i = 0; i < row; i++)
						for(j = 0; j < col; j++)
						{
							temp = matrix_a[i][j];
							matrix_t[j][i] = temp; // 안정성을 위해 temp를 선언한 후 temp 변수로부터 값을 전달받을수 있도록 처리
						}
				}
	return 0;
}

int multiply_matrix(int **matrix_a, int **matrix_t, int **matrix_axt, int row, int col)
{
	int i, j, temp; // 2중 for문 동작을 위한 변수선언 및 값 교환을 위해 임시 저장할 정수형 변수 추가선언

					if(matrix_a == NULL || matrix_t == NULL || matrix_axt == NULL)  // 해당 행렬이 초기값 NULL을 가르키고 있는지 판단 후 한개의 조건이라도 해당되면 비정상종료값 출력
						{
							printf("해당 행렬이 할당되지 않은것 같습니다. 프로그램을 다시 실행시켜 주세요.\n");
							return -1;
						}
					else
					{
						for(i = 0; i < row; i++)
							for(j = 0; j < col; j++)
							{
								temp = matrix_a[i][j] * matrix_t[j][i];
								matrix_axt[j][i] = temp; // 안정성을 위해 temp를 선언한 후 temp 변수로부터 값을 전달받을수 있도록 처리
							}
					}
		return 0;
}

void show_menu(void)
{
	printf("\n사용하고 싶은 기능을 선택하세요.\n");
	printf("1. 행렬A 와 B를 무작위의 숫자로 채워넣기\n");
	printf("2. 행렬 두개를 더하기 (A + B)\n");
	printf("3. 행렬 두개를 빼기 (A - B)\n");
	printf("4. 행렬 A를 전치행렬로 바꾸기 (A -> T)\n");
	printf("5. 행렬 A와 전치행렬을 곱하기 (A * T)\n");
	printf("6. 모든 행렬 메모리 해제하기\n");
	printf("7. 프로그램 끝내기\n");
	printf("어떤 기능을 사용하시겠습니까? :");
}

/*
 * 해당 프로그램을 작성해 보면서 2차원배열의 indexing개념과
 * 동적할당의 개념, 그리고 free하는 과정에서 발생하는 에러를
 * 처리하면서 메모리 space상에서의 stack 과 heap의 실질적인
 * 차이를 확인하였고 heap영역을 적절히 활용한다면 프로그램이
 * 매우 유동적으로 작동이 된다는 것을 이번 과제를 통해 잘 알게
 * 되었습니다. 또한 평소에 사용하기 힘들었던 더블포인터 -> 단일포인터 -> 실제 data변수
 * 간의 관계를 확실히 알아보는 시간이 되었던것 같습니다.*/
