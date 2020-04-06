#include <stdio.h>

struct student {
	char lastName[13]; //13바이트
	int studentID;     // 4바이트
	short grade;       // 2바이트 이기 때문에 해당 구조체는 19바이트를 예상해볼 수 있지만
};

int main()
{
	printf("------------ 학번 : 2017038102 ------------- 이름 : 최용석 ----------------\n");
	struct student pst;

	printf("size of student = %d\n", sizeof(struct student));
	printf("size of int = %d\n", sizeof(int));
	printf("size of short = %d\n", sizeof(short));
	return 0;

	/*
	 * 막상 출력해보면 24바이트가 출력됨을 알 수 있다. gcc는 패딩을 사용하여 4byte단위로 data를 읽을 수 있도록 하는데
	 * 이것은 아마 CPU가 data를 빨리 읽어들이기 위함으로 이런 구조를 사용하는 것이다.
	 * 따라서 컴파일러에 따라 패딩을 지원하는지 안하는지 미리 알아볼 필요가 있다는 것도 알게 되었다.
	 * */
}
