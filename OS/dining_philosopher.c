#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

//Function declarations
void *pickup_forks(void * philosopher_number);
void *return_forks(void * philosopher_number);
void test(int philosopher_number);
int left_neighbor(int philosopher_number);
int right_neighbor(int philosopher_number);
double think_eat_time(void);
void think(double think_time);
void eat(double eat_time);
double max_meals;
//Constants to be used in the program.
#define PHILOSOPHER_NUM 5
//#define MAX_MEALS 10
//#define MAX_THINK_EAT_SEC 10

//States of philosophers.
enum {THINKING, HUNGRY, EATING} state[PHILOSOPHER_NUM];

//Array to hold the thread identifiers.
pthread_t philos_thread_ids[PHILOSOPHER_NUM];

//Mutex lock.
pthread_mutex_t mutex;

//Condition variables.
pthread_cond_t cond_vars[PHILOSOPHER_NUM];

//Array to hold the number of meals eaten for each philosopher.
int meals_eaten[PHILOSOPHER_NUM];

int main(int argc, char *argv[])
{
    //Ensure correct number of command line arguments.
    if(argc != 2)
    {
        printf("Please ensure that the command line argument 'run_time' is passed.\n");
    }
    else
    {
        //Set command line argument value to variable run_time;
        max_meals = atof(argv[1]);

        //Initialize arrays.
        int i;
        for(i = 0; i < PHILOSOPHER_NUM; i++)
        {
            state[i] = THINKING;
            pthread_cond_init(&cond_vars[i], NULL);
            meals_eaten[i] = 0;
        }


        //Initialize the mutex lock.
        pthread_mutex_init(&mutex, NULL);




        //Create threads for the philosophers.
        for(i = 0; i < PHILOSOPHER_NUM; i++)
        {
            pthread_create(&philos_thread_ids[i], NULL, pickup_forks, (void *)i);
        }

        //Join the threads.
        for(i = 0; i < PHILOSOPHER_NUM; i++)
        {
            pthread_join(philos_thread_ids[i], NULL);
        }

        for(i = 0; i < PHILOSOPHER_NUM; i++)
        {
            printf("Philosopher %d: %d meals\n", i, meals_eaten[i]);
        }

    }

    return 0;
}

void *pickup_forks(void * philosopher_number)
{
    int loop_iterations = 0;
    int pnum = (int)philosopher_number;
    

    while(meals_eaten[pnum] < max_meals)
    {
        printf("Philosoper %d is thinking.\n", pnum);
        think(think_eat_time());

        pthread_mutex_lock(&mutex);
        state[pnum] = HUNGRY;
        test(pnum);

        while(state[pnum] != EATING)
        {
            pthread_cond_wait(&cond_vars[pnum], &mutex); // waiting until the condition is come.
        }
        pthread_mutex_unlock(&mutex);

		printf("%d", meals_eaten[pnum]);
        (meals_eaten[pnum])++;

        printf("Philosoper %d is eating meal %d.\n", pnum, meals_eaten[pnum]);
        eat(think_eat_time());

        return_forks((&philosopher_number));

        loop_iterations++;
    }
    printf("Philosoper %d full.\n",pnum);
}

void *return_forks(void * philosopher_number)
{
    pthread_mutex_lock(&mutex);
    int pnum = *(int *)philosopher_number;

    state[pnum] = THINKING;

    test(left_neighbor(pnum));
    test(right_neighbor(pnum));

    pthread_mutex_unlock(&mutex);
}
// counter clockwise***************
int left_neighbor(int philosopher_number)
{
    return ((philosopher_number + (PHILOSOPHER_NUM - 1)) % 5);
}

int right_neighbor(int philosopher_number)
{
    return ((philosopher_number + 1) % 5);
}
// ********************
void test(int philosopher_number)
{
    if((state[left_neighbor(philosopher_number)] != EATING) && 
        (state[philosopher_number] == HUNGRY) &&
        (state[right_neighbor(philosopher_number)] != EATING))
    {
        state[philosopher_number] = EATING;
        pthread_cond_signal(&cond_vars[philosopher_number]);
    }
}

double think_eat_time(void)
{
	return (rand()%3); // random time to think and eat time
}

void think(double think_time)
{
    sleep(think_time);
}

void eat(double eat_time)
{
    sleep(eat_time);
}
