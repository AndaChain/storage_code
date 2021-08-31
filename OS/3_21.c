#include <stdio.h>
#include <unistd.h>

int main()
{
	// defind
	int num;
	pid_t pid;
	
	printf("Enter your number, but positive number: ");
	scanf("%d", &num);
	
	// check error number
	if(num <= 0)
	{
		printf("Error! Enter positive number, please");
		return -1;
	}
	else
	{
			printf("Correct!\n\n");

			// fork
			pid = fork();
			
			if(pid == 0)
			{
				// Child
				printf("CHILD: %d\n",getpid());
				while(1)
				{
					printf("%d,",num);
					if(num%2 == 0)
					{
						num = num/2;
					}
					else
					{
						num = 3*num+1;
					}
					if(num == 1)
					{
						printf("%d\n",num);
						break;
					}
				}
				exit(0);
				
				
			}
			else if (pid > 0)
			{
				// Parent
				wait(NULL);
				printf("PARENT pid: %d\n", getpid());
				
				
			}
			else
			{
				// Failed
				printf("Failed to fork!\n");
				return -1;
			}
	}
	return 0;
}
