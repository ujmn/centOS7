#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//#define _DEBUG_ 0
#define NUM 256

void CommandExec(char** argv)
{
	assert(argv);
	pid_t id = fork();
	if (id <  0)
	{
		return;
	}
	else if (id == 0)
	{
		int flag = -1;
		int i = 1;
		while (1)
		{
			if (NULL != argv[i] && (0 == strcmp(argv[i], ">") || 0 == strcmp(argv[i], ">>")))
			{
				flag = i;
				break;
			}
			else if (NULL == argv[i])
				break;
			++i;
		}

		if (0 == strcmp(argv[0], "cd"))
		{
			chdir(argv[1]);
			return;
		}	
		else if (flag > 0)
		{
			if (0 == strcmp(argv[flag], ">"))
			{
				int fd = open(argv[flag + 1], O_CREAT | O_TRUNC | O_WRONLY, 00600);
				dup2(fd, 1);
				argv[flag] = NULL;
			}
			else if (0 == strcmp(argv[flag], ">>"))
			{
				int fd = open(argv[flag + 1], O_CREAT | O_APPEND | O_WRONLY, 00600);
				dup2(fd, 1);
				argv[flag] = NULL;
			}
		}

		execvp(argv[0], argv);
	}
	else
	{
		wait(NULL);
	}
}

void MakeArgv(char* cmd, char** argv)
{
	assert(cmd);
	assert(argv);
	argv[0] = strtok(cmd, " ");
	int i = 1;
	while (1)
	{
		argv[i] = strtok(NULL, " ");
		if (argv[i] == NULL)
			break;
		++i;
	}
#ifdef _DEBUG_
	i = 0;
	while (argv[i])
	{
		printf("%s\n", argv[i]);
		++i;
	}
#endif
}

int main()
{
	char cmd[NUM];
	char* argv[32];
	while (1)
	{
		printf("[xxx@local ~]#");
		fgets(cmd, sizeof(cmd), stdin);
		cmd[strlen(cmd)-1] = 0;
		MakeArgv(cmd, argv);
		CommandExec(argv);
	}
	return 0;
}
