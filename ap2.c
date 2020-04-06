#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("/n ----------- 학번 : 2017038102 -------------- 이름 : 최용석 ------------\n");
	int list[5];
	int *plist[5];  // 일반 배열과 포인터배열의 선언

	list[0] = 10;
	list[1] = 11; // 배열의 첫번째, 두번째 원소를 초기화

	plist[0] = (int*)malloc(sizeof(int)); // 여기서 할당은 받지만 아래에서 사용되지 않습니다. 왜 이 코드가 존재하는지는 잘 모르겠습니다.

	printf("list[0] \t= %d\n", list[0]); //배열의 첫번째 인덱스의 값 출력
	printf("address of list \t= %p\n", list);  // 배열의 이름은 그 자체로 주소이므로 해당 출력이 가능하다
	printf("address of list[0] \t= %p\n", &list[0]); // 앞의 &연산자와 뒤의[0]인덱스 기호가 붙어도 같은 주소가 출력된다
	printf("address of list + 0 \t= %p\n", list+0); // 주소연산자를 생략하고 포인터의 연산처럼 +n 을 사용하여 주소를 움직일 수 있다.
	printf("address of list + 1 \t= %p\n", list+1);
	printf("address of list + 2 \t= %p\n", list+2);
	printf("address of list + 3 \t= %p\n", list+3);
	printf("address of list + 4 \t= %p\n", list+4); // 해당 출력문 까지 배열의 이름을 가지고 인덱스를 선회하는것 처럼 사용할 수 있다.
	printf("address of list[4] \t= %p\n", &list[4]); // list+4 와 같은 기능을 하는 부분

	free(plist[0]); // 위에서 받았던 동적할당의 해제

	/*
	 * 배열의 이름은 곧 주소이고 해당 주소를 가지고 인덱스를 선회하는 것 처럼 사용이 가능한 점을 다시한번 복습하게 되었고,
	 * 동적할당을 받으면 반드시 해제를 해주어야 만이 미아 포인터 등을 방지하여 프로그램이 커질경우 생길 수 있는
	 * 메모리 누수를 방지할 수 있다는 것을 다시한번 알게 되었습니다.
	 */
	return 0;
}
