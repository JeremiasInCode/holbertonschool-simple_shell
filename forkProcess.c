#include "shell.h"

/**
* forkProcess - Function that execute a child process.
* @command: path of param.
* @arguments: arguments of the command.
* Return: status of child process.
*/

int forkProcess(char *command, char **arguments)
{
	int status = 0;

	pid_t child = fork();

	if (child > 0)
	{
		wait(&status);
	}
	else if (child == 0)
	{
		execve(command, arguments, environ);
	}
	else
	{
		free_array(arguments);
		perror("Error:");
	}
	return (WEXITSTATUS(status));
}
