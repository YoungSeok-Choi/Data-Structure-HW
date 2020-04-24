#include <stdio.h>

void print1(int *ptr, int rows); /*함수의 프로토타입 선언, 매개변수 목록 중에서 배열을 참조한다고 해서 배열을 나타내지 않아도
인자로 받으려는 배열의 자료형과 같은 포인터 형이면 문제없이 배열을 참조할 수 있다.*/

int main()
{
	printf("\n --------- 학번 : 2017038102 ---------- 이름 : 최용석 \n");
	int one[] = {0, 1, 2, 3, 4};

	printf("one       = %p\n", one);
	printf("&one      = %p\n", &one);
	printf("&one[0]   = %p\n", &one[0]);  // 배열의 첫번째 인덱스의 주소를 출력 one, &one, &one[0] 모두 동일하다.
	printf("\n");

	print1(&one[0], 5); //함수의 호출, 배열의 주소가 넘어감으로서 스택의 다른곳에서 선언된 ptr이 배열을 가르키게 된다.

	return 0;
}

void print1(int *ptr, int rows)
{
	int i;
	printf("address \t        contents\n");
	for(i=0; i < rows; i++)
		printf("%p \t  %5d\n", ptr + i, *(ptr + i)); // 배열의 주소값이 자료형의 크기(4byte)만큼 늘어나는것을 알 수 있다.
	printf("\n");
}
