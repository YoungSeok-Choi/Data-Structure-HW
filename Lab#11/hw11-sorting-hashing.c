/*
* hw5-sorting.c
*
*  Created on: May 22, 2019
*
*  Homework 5: Sorting & Hashing
*  Department of Computer Science at Chungbuk National University
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h> /*�迭�� ���� �������� �ʱ�ȭ�ϱ� ���� �������*/

#define MAX_ARRAY_SIZE                  13      /* prime number */
#define MAX_HASH_TABLE_SIZE     MAX_ARRAY_SIZE

/* �ʿ信 ���� �Լ� �߰� ���� */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function���� ���� */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a���� �� hash table�� �����. */
int hashing(int *a, int **ht);

/* hash table���� key�� ã�� hash table�� index return */
int search(int *ht, int key);


int main()
{
    char command;
    int *array = NULL;
    int *hashtable = NULL;
    int key = -1;
    int index = -1;

    srand(time(NULL));

    do{
        printf("----------------------------------------------------------------\n");
        printf("                        Sorting & Hashing                       \n");
        printf("----------------------------------------------------------------\n");
        printf("===========[2017038102]===================[�ֿ뼮]==============\n");
        printf(" Initialize       = z           Quit             = q\n");
        printf(" Selection Sort   = s           Insertion Sort   = i\n");
        printf(" Bubble Sort      = b           Shell Sort       = l\n");
        printf(" Quick Sort       = k           Print Array      = p\n");
        printf(" Hashing          = h           Search(for Hash) = e\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch(command)
		{
        case 'z': case 'Z':
            initialize(&array);
            break;
        case 'q': case 'Q':
            freeArray(array);
            break;
        case 's': case 'S':
            selectionSort(array);
            break;
    	case 'i': case 'I':
            insertionSort(array);
            break;
        case 'b': case 'B':
            bubbleSort(array);
            break;
        case 'l': case 'L':
            shellSort(array);
            break;
        case 'k': case 'K':
        	printf("Quick Sort: \n");
            printf("----------------------------------------------------------------\n");
            printArray(array);  /*���� �� �迭 ���*/
            quickSort(array, MAX_ARRAY_SIZE);
            printf("----------------------------------------------------------------\n");
            printArray(array);  /*���� ���� �迭���.*/ 

            break;

        case 'h': case 'H':
            printf("Hashing: \n");
            printf("----------------------------------------------------------------\n");
            printArray(array);
            hashing(array, &hashtable);
            printArray(hashtable);
            break;

        case 'e': case 'E':
            printf("Your Key = ");
            scanf("%d", &key);
            printArray(hashtable);
            index = search(hashtable, key);
            printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
            break;

        case 'p': case 'P':
            printArray(array);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
		}

    }while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{/*main �Լ� ���� ����Ǿ� �ִ�  array������ ������ ���� �����ϱ� ���� 2�������� �Ű�����.*/
	int i;
    int *temp = NULL;
	
    /* array�� NULL�� ��� �޸� �Ҵ� */
    if(*a == NULL)
	{
        temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
        *a = temp;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
    } 
	else /*������ �Ҵ�� �迭�� ������ �ܼ��� �ּҸ� ����.*/
        temp = *a;

        /* �������� �迭�� ������ ���� */
    for(i = 0; i < MAX_ARRAY_SIZE; i++)
        temp[i] = rand() % MAX_ARRAY_SIZE;

    return 0;
}

int freeArray(int *a)
{/*�ܼ��� �����Ҵ� �迭�̹Ƿ� �ݺ����� �� �ʿ���� �ٷ� �Ҵ�����.*/
    if(a != NULL)
        free(a);
	return 0;
}

void printArray(int *a)
{
	int i;
    if (a == NULL)/*����ó�� �κ�.*/
	{
        printf("nothing to print.\n");
        return;
    }
    /*�迭�� index�� print*/
    for(i = 0; i < MAX_ARRAY_SIZE; i++)
            printf("a[%02d] ", i);
        printf("\n");
    /*���� �迭�� ���� print*/    
    for(i = 0; i < MAX_ARRAY_SIZE; i++)
            printf("%5d ", a[i]);
        printf("\n");
}

int selectionSort(int *a)
{
    int min;
    int minindex;
    int i, j;

    printf("Selection Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a);
	/*���� �� �迭���(���� �����Լ����� ���� ����).*/
    for (i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        minindex = i;/*�迭�� ù��° ���Ҹ� �ּҰ��� ��ġ�� �����ϰ� �ϳ��� �÷����� ����.*/
    	min = a[i]; /*�ּҰ��� �ӽ÷� �����س���.*/
            for(j = i+1; j < MAX_ARRAY_SIZE; j++)
            {
                if (min > a[j])
                {/*�ݺ����� ���鼭 �� �������� �߰��ϸ� index �� value�� �ֽ�ȭ.*/
                    min = a[j];
                    minindex = j;
                }
            }
        a[minindex] = a[i]; /*i��° ���Ҹ� �ּҰ��� �ִ� ��ġ�� ���.*/
        a[i] = min; /*�ּҰ��� i��° ��ġ�� ����.*/ 
    }

    printf("----------------------------------------------------------------\n");
    printArray(a); /*���ĵ� �迭�� ����ϰ� return(���� �����Լ����� ���� ����).*/
    return 0;
}

int insertionSort(int *a)
{
    int i, j, t;

    printf("Insertion Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a);

    for(i = 1; i < MAX_ARRAY_SIZE; i++)
    {/*���������� ������ �ϳ��� �÷����� ����, index�� ���� �ӽ÷� ����.*/
        t = a[i];
        j = i;
        while (a[j-1] > t && j > 0)
        {/*while ���� �� �������� ã�Ұų�, index�� 0������ �� ������ �ݺ�*/
            a[j] = a[j-1];
            j--;
        }
        a[j] = t; /*�ݺ����� ������������ ���� for������ ���� ���� i�� ���� 0���� �̰ų�, 
		�ڽź��� ���� �� �ٷ� �ڿ� ��ġ�� ����.(J�� ��ġ�� ����)*/
    }

    printf("----------------------------------------------------------------\n");
    printArray(a);

    return 0;
}

int bubbleSort(int *a)
{
    int i, j, t;

    printf("Bubble Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a);

    for(i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        for (j = 1; j < MAX_ARRAY_SIZE; j++)
        {/*������ J�� 0���� �������� �� if���� J-1�� ������ �Ǿ� �迭�� ������
		   ������ ������ ������ �Ǵ� ������ for������ 1������ �����ϴ°����� ����.*/
            if (a[j-1] > a[j])
            {/*��ĭ�� ������ �����鼭 ū���� �߰������� swap�ϸ� �ִ밪�� ������ ����.*/
                t = a[j-1];
                a[j-1] = a[j];
                a[j] = t;
            }
        }
    }
	/*�ش� �ݺ����� ��� �Ϸ�ȴٸ� ������ ��������.*/
    printf("----------------------------------------------------------------\n");
    printArray(a);

    return 0;
}

int shellSort(int *a)
{
    int i, j, k, h, v;

    printf("Shell Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a);

    for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)
    {/*h�� ���� �迭�� ������ size �� ������ ������ �ٿ������� h�Ÿ���ŭ �ִ� ���ҵ��� ������.*/
        for (i = 0; i < h; i++)
        {/*�ش� �κ��� h�Ÿ��� �������� ����index�� ��ġ��  ����*/ 
            for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
            { /*�ش� �κ��� h�Ÿ��� �������� ūindex�� ��ġ��  ����*/
                v = a[j];
                k = j;
                    while (k > h-1 && a[k-h] > v)
                    {
                        a[k] = a[k-h];
                        k -= h;
                    }/*�ش� h�Ÿ���ŭ ���ؼ� �ٲپ� �����鼭 ����������h==1 �� �Ǿ��� �� ����������
					���·� �� ���Ŀ��� �ǵ��� �������� �� ���������� ������ ������ �� �ִ�.*/
                a[k] = v;
            }
        }
    }
    printf("----------------------------------------------------------------\n");
    printArray(a);

    return 0;
}

int quickSort(int *a, int n)
{
    int v, t;
    int i, j;

    if (n > 1)
    {
        v = a[n-1];/*�ش� �Լ�������  pivot ���� ���� ������ ���ҷ� ����.*/
        i = -1;
        j = n - 1;/*������ index��ȣ�� ����*/

        while(1)
    	{
        	while(a[++i] < v);/*���������Һ��� ū���� ���ö����� i�� ����*/
        	while(a[--j] > v);/*������ ���Һ��� �������� ���ö����� J�� ����*/

        	if (i >= j) break; /*i�� j�� �Ѿ�����ٸ� �ݺ����� break */
       		t = a[i];
        	a[i] = a[j];
        	a[j] = t; /*����  if���� ������� �ʴ´ٸ� pivot���� �������� ū���� ������ ����*/
    	}
    	 /*�ش� ���ɾ ����ȴٸ� if������ i�� j�� �Ѿ ���� ���̹Ƿ� i�� ������pivot��ġ�� 
		 �ٲ����ν� i��° index�������� ���ʿ��� ū����, ���ʿ��� �������� ���ĵǰ� ��.*/
    	t = a[i];
       	a[i] = a[n-1];
        a[n-1] = t;

        quickSort(a, i);/*i�� �������� ������ �ٽ� ����������� ������*/
        quickSort(a+i+1, n-i-1);/*i�� ���� �ε�����, a~i������ �ε�����ũ�⸸ŭ ���� size�� ��������� ȣ��*/
    }
        return 0;
}

int hashCode(int key)
{/*0~MAX_HASH_TABLE_SIZE-1 �� ���� retrun*/
  return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int i;
    int *hashtable = NULL;

        /* hash table�� NULL�� ��� �޸� �Ҵ� */
    if(*ht == NULL)
	{
        hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
        *ht = hashtable;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
    } 
	else
	{
        hashtable = *ht;        /* hash table�� NULL�� �ƴѰ��, table ��Ȱ��, reset to -1 */
    }

    for(i = 0; i < MAX_HASH_TABLE_SIZE; i++)
        	hashtable[i] = -1;

        /*
        for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
                printf("hashtable[%d] = %d\n", i, hashtable[i]);
        */
	/*����� �������� �ʱ�ȭ*/
    int key = -1;
    int hashcode = -1;
    int index = -1;
    
    for (i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        key = a[i];
        hashcode = hashCode(key);
                /*
                printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
                */
        if (hashtable[hashcode] == -1)/*�ش� ���̺��� slot�� �ϳ����� �� �� �ִ�.*/
            {/*�ش� ���̺��� ����ִٸ�.*/
                hashtable[hashcode] = key; /*���������� �Ҵ���.*/
            } 
			else/*�ش� �ؽ����̺��� ���� �ּҹ��� �����. cahining���� overflow�� ó������ ����.*/
			{
                index = hashcode;/*ã������ key�� code���� index��*/

                while(hashtable[index] != -1)
                    {/*�ش� �Լ������� Ư�� primenumber(13)�� ����ؼ� index ���� ���� �� �����ϴ� double hashing �� �̿��� 
					overflow�߻��� ó����.*/
                        index = (++index) % MAX_HASH_TABLE_SIZE;
                                /*
                                printf("index = %d\n", index);
                                */
                    }
                hashtable[index] = key; 
            }	/*����ִ� ������ ã���� ��� �����ϰ� return*/
    }
    return 0;
}

int search(int *ht, int key)
{/*���ڷ� ���� key�� �ش��ϴ� ���� ���� ���� */
    int index = hashCode(key);
	/*���� �ش�index�� �´� Ű���ִٸ� ���������� ��ȯ */
    if(ht[index] == key)
        return index;
	
    while(ht[++index] != key)
    {/*�������� ���ǹ��� ������ �����ʴ´ٸ� �浹 �� �����÷ο찡 �߻��� �ٸ� index �� ������ ���̹Ƿ�
	  Double Hashing�� ���� key�� ���������� Ž��*/
        index = index % MAX_HASH_TABLE_SIZE;
    }
	return index;
}/*�ش� return�� ����ȴٸ� ���� ã������. �ش� �Լ����� ���� ã�� ������ ����� ����ó���� ����*/