#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// "size" is size of array.
int sum, size, avg,  min, max= 0;
int array[20];
int *pointer = array; // set init pointer

// declaration function
void *average(int *param);
void *minimum(int *param);
void *maximum(int *param);
void *str_arr_int2(char* input);

int main(int argc)
{
		char input[50];
		fgets(input, sizeof(input),stdin);
		str_arr_int2(input);
		
		// create thread section
		pthread_t tid1;
		pthread_create(&tid1,NULL, average, pointer);
		
		pthread_t tid2;
		pthread_create(&tid2,NULL, minimum, pointer);
		
		pthread_t tid3;
		pthread_create(&tid3,NULL, maximum, pointer);
		pthread_join(tid1, NULL);
		pthread_join(tid2, NULL);
		pthread_join(tid3, NULL);
		
		printf("\nsum = %d", sum);			
		printf("\naverage = %d", avg);
		printf("\nminimum = %d", min);
		printf("\nmaximum = %d", max);
		
	return 0;
}

void *average(int *param) // find average
{
	
	for(int i=0; i<size; i++)
	{
		sum += *param;
		param++;
	}
	avg = sum/size;
	pthread_exit(0);
}

void *minimum(int *param) // find minimum
{
	min = *param;
	for(int i=0; i<size; i++)
	{
		if(min > *param)
		{
			min = *param;
		}
		else
		{
			min = min;
		}
		param++;
	}
	pthread_exit(0);
}

void *maximum(int *param) // find maximum
{
	
	max = *param;
	for(int i=0; i<size; i++)
	{
		if(max < *param)
		{
			max = *param;
		}
		else
		{
			max = max;
		}
		param++;
	}
	pthread_exit(0);
}

void *str_arr_int2(char* input) // converted string input to a pointer int array.
{
	int num = 0;
	
	char *token = strtok(input, " "); // cutting space from input
	
    while (token != NULL)
    {
		sscanf(token, "%d", &num);
		
		// push element
        *pointer = num;
        
        // next element of input
        token = strtok(NULL, " ");
        pointer++; // next element of pointer
        size++;
    }
    
    pointer = array; // set address to init address of pointer
}
