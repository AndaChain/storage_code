#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>

#define MAX_THREAD 4

/*
 * 
 *  Not working code only skeleton of programm
 * 
*/


int r_ound = 0;
int test = 10;
bool arr_stu[MAX_THREAD];

void *isprime2(void *input);

typedef struct pointer{
	int *arr;
	int len;
}pointer;

pointer arr[sizeof(int)];

int main(void)
{
	int step = test/MAX_THREAD;
	if(test<MAX_THREAD)
	{
		step = test/MAX_THREAD;
	}
	else
	{
		step = MAX_THREAD;
	}
	pthread_t *tid;
	tid = (pthread_t *)malloc(MAX_THREAD * sizeof(pthread_t));
	
	while(test>0)
	{
			for(int i=2; i< MAX_THREAD; i++)
			{
				arr->len++;
				int a[2] = {i,};
				arr->arr=a;
				pthread_create(&tid[i],NULL, isprime2, (void *)arr);
			}
			for(int j=0; j<MAX_THREAD; j++)
			{
				pthread_join(tid[j], NULL);
			}
			test--;
	}
	return 0;
}

void *isprime2(void *input)
{
    // Declare the variables
    int a, b, i, j, flag;
 
    a= 0;
 
    b = 10;
 
 
    for (i = a; i <= b; i++) {

        if (i == 1 || i == 0)
            continue;
 
        flag = 1;
 
        for (j = 2; j <= i / 2; ++j) {
            if (i % j == 0) {
                flag = 0;
                break;
            }
        }
 
        if (flag == 1)
            printf("%d ", i);
    }
	pthread_exit(0);
}
