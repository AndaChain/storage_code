#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
	// show process before zombie
	printf("Before kill Zombie");
	system("./3_17 &");
	system("ps -l");
	
	// kill zombie
	sleep(3);
	system("kill - $(ps -l|grep -w Z|tr -s ' '|cut -d ' ' -f 5)");
	sleep(7);
	
	// show process after zombie
	printf("\n\nAfter kill Zombie");
	system("ps -l");
	return 0;
}
