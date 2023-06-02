#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[], char **env)
{
	char *buffer;
	ssize_t bytes;
	size_t buffer_size = 0;
	pid_t pid;
	int status;
	char *command;
/*  unsigned int i;

	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
        i++;
	}
*/
	while(1)
	{
		printf("$$$ ");
		bytes = getline(&buffer, &buffer_size, stdin);
		command = strtok(buffer, "\n");

		if (bytes != 0)
		{
			pid = fork();

			if (pid == 0)
			{
				char *new_args[] = {argv[0], NULL};
				execve(command, new_args, env);

			}
			else if (pid > 0)
			{
				wait(&status);
			}
			else
			{
				printf("Error creating child process\n");
			}

		}

	}

	return (0);
}


