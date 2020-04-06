#include <stdio.h>

#define MAX_SIZE 100  /*매크로 정의부분이다, 예전 강의영상에서부터 예제에서는 매크로를
적절하게 사용하여 보기에도 좋고 프로그래머의 수고를 많이 덜어주는 좋은 예시를 많이 들어주셨는데
이 부분을 배워야겠다고 생각했다.*/

float sum(float [], int);  // 함수의 프로토타입 선언 및 전역변수, 배열등의 선언
float input[MAX_SIZE], answer;
int i;

void main()
{
	printf("\n --------- 학번 : 2017038102 ---------- 이름 : 최용석 \n");
	for(i=0; i < MAX_SIZE; i++)
		input[i] = i;  // for 문으로 0~99까지 1씩 증가하는 값이 배열의 인덱스에 차례로 초기화 될것이다.

	printf("address of input %p\n", input); //main함수 밖에서 선언된 배열의 주소

	answer = sum(input, MAX_SIZE); // 함수 호출 시에 중요시 봐야할 것이 input배열의 주소가 어떻게 저장이 되는지 잘 봐야할 것이다.
	printf("The sum is: %f\n", answer); // 0~99까지 더한값을 출력
}

float sum(float list[], int n)
{
	printf("value of list = %p\n", list);  //해당 변수가 input 배열의 주소를 담고 있고, 따라서 이 변수를 통해 배열을 참조할 수 있게 된것이다.
	printf("address of list = %p\n", &list); // list변수도 주소값을 담는 '변수' 이므로 독립적인 주소에 저장되어 있음을 확인할 수 있다.

	int i;
	float tempsum = 0;
	for(i=0; i < n; i++)
		tempsum += list[i]; // input 배열의 모든 인덱스를 더하여 return하는 부분
	return tempsum;
}
