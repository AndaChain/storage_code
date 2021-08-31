/*
 * REF: https://www.alltestanswers.com/operating-systems-fundamentals-assignment-2/
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
pid_t pid;
	
	pid = fork();
	
	if (pid == 0)
	{
		printf("CHILD pid: %d\n", getpid());
		exit(0);
	}
	else if (pid > 0)
	{
		// No waiting
		printf("PARENT pid: %d\n", getpid());
		sleep(10);
	}
	else
	{
		printf("Failed to fork!\n");
		return -1;
	}

	return 0;
	
}
