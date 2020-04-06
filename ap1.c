#include <stdio.h>
#include <stdlib.h>

int main()
{
	// ap1.c
	printf("\n --------- 학번 : 2017038102 ---------- 이름 : 최용석 \n");

	int list[5];  // 일반 배열의 선언
	int *plist[5] = {NULL, }; // 포인터변수의 배열을 선언 , 실제 값이 아닌 주소값을 담는 리스트

	plist[0] = (int*)malloc(sizeof(int)); //포인터배열의 첫번째인덱스의 값을 heap영역으로부터 할당

	list[0] = 1;
	list[1] = 100; //일반 배열의 값 대입

	*plist[0] = 200;  // 역참조를 사용해 heap 주소에 실제 data값 대입

	printf("value of list[0]       = %d\n", list[0]); //일반 배열 첫번째 인덱스의 값 출력
	printf("address of list[0]     = %p\n", &list[0]);
	printf("value of list          = %p\n", list);
	printf("address of list(&list) = %p\n", &list);  //위의 3개 프린트문에서 알 수 있듯이, 배열의 이름은 그 자체로 자신의 첫번째 인덱스를 가르키는 상수 포인터임을 알 수있다.


	printf("--------------------------------------------------------------\n\n");
	printf("value of list[1]       = %d\n", list[1]); //배열의 2번째인덱스의 값 출력
	printf("address of list[1]     = %p\n", &list[1]);  // 위의 첫번째인덱스의 주소에서 자료형 크기 하나만큼의 주소가 커짐을 볼수있다.
	printf("value of *(list+1)     = %d\n", *(list+1)); // list도 포인터이므로 역참조 연산을 할 수 있음.
	printf("address of list+1      = %p\n", list+1); // 포인터인 배열 이름에 연산을 함으로써 주소를 참조 할 수 있다.

	printf("--------------------------------------------------------------\n\n");

	printf("value of *plist[0]     = %d\n", *plist[0]);  // 포인터배열의 첫번째 인덱스가 가르키는 값의 실제 data출력(in heap area)
	printf("&plist[0]              = %p\n", &plist[0]);  // 아래의 3개 프린트문이 모두 같은 결과를 도출함을 알 수 있다.
	printf("&plist                 = %p\n", &plist);    // 주소연산자를 사용하던 그렇지 않던 배열의 이름은 상수의 성질을 갖는 주소라고 생각하면 이해가 간다.
	printf("plist                  = %p\n", plist);  // 실제 plist[0] 안에 들어있는 heap영역 주소의 값 , 포인터변수르를 모아놓은 배열이고 위에서 동적할당을 받았기 때문에 확인할 수 있다.
	printf("plist[0]               = %p\n", plist[0]);
	printf("plist[1]               = %p\n", plist[1]);
	printf("plist[2]               = %p\n", plist[2]);
	printf("plist[3]               = %p\n", plist[3]);
	printf("plist[4]               = %p\n", plist[4]); // 선언부분에서 NULL로 초기화 했으므로 nil값이 출력

	free(plist[0]); // 위의 동적할당을 해지

	/* 해당 프로그램을 작성하고 실행하면서 예전에 배웠던 배열과 포인터, 그리고 동적할당 의 개념까지 다시한번
	 	 돌아볼 수 있었던 시간이였습니다.
	 */

	return 0;
}
