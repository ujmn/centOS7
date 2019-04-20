#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int i = 0;
	char bar[100];
	char label[5] = "|/-\\";
	printf("\e[30m");
	memset(bar, '\0', 100);
	for (; i<=100; ++i)
		{
			bar[i] = '#';
			printf("[%-100s][%d%%][%c]\r", bar, i, label[i%4]);
			fflush(stdout);
			usleep(100000);
		}
		printf("\e[0m");
		printf("\n");
	return 0;
}
