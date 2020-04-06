#include <stdio.h>

struct student1{
	char lastName;
	int studentID;
	char grade;
};

typedef struct{
	char lastName;
	int studentID;
	char grade;
} student2;

int main()
{
	printf("------------ 학번 : 2017038102 ------------- 이름 : 최용석 ----------------\n");
	struct student1 st1 = {'A', 100, 'A'};

	printf("st1.lastName = %c\n ", st1.lastName);
	printf("st1.studentID = %d\n ", st1.studentID);
	printf("st1.grade = %c\n ", st1.grade);

	student2 st2 = {'B', 200, 'B'};

	printf("\nst2.lastName = %c\n ", st2.lastName);
	printf("st2.studentID = %d\n ", st2.studentID);
	printf("st2.grade = %c\n ", st2.grade);

	student2 st3;

	st3 = st2; //이전의 컴파일러들은 구조체끼리의 대입연산을 허용하지 않았지만 gcc에서는 가능하다

	printf("\nst3.lastName = %c\n ", st3.lastName);
	printf("st3.studentID = %d\n ", st3.studentID);
	printf("st3.grade = %c\n ", st3.grade);

	// == 테스트해보기;
	/*
	if(st3==st2)
		printf("equal\n");
	else
		printf("not equal\n");
	 */
	/*
	 * 위의 구조체와 대입연산, 그리고 == 연산을 통해 알수 있었던 점은 처음의 선언부분에서
	 * struct 키워드를 뺸 st1은 컴파일 에러가 발생하는 것을 알 수 있엇고 이를 생략하도록
	 * 할 수 있는것이 typedef 키워드임을 알 수 있었다.
	 * 또한 예전에 멤버연산자를 사용해서 대입하거나 비교할 수 있는 연산이 대입연산 정도는 바로
	 * 구조체 멤버를 참조하지 않고 구조체 통째로 대입할수 있다는 것을 새로 알게 되었다.
	 * */
	return 0;
}
