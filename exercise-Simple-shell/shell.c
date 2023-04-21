#include "shell.h"
#define MAX_ARGS 300
#define BUFFER_SIZE 0
/**
 * main - replicate of a shell
 * Return: FALTA DETERMINAR LOS VALORES DE RETURN
 */
int main(void)
{
	size_t sizeBuffer = BUFFER_SIZE;
	char *command = NULL, *comandPathCopy = NULL, *bufferEntry = NULL;
	char **args = NULL;
	int status = 0, satty = isatty(STDOUT_FILENO);

	satty == 1 ? write(1, "$ ", 2) : 0;

	while (getline(&bufferEntry, &sizeBuffer, stdin) >= 0)
	{
		if (strlen(bufferEntry) == 1)
		{
			satty == 1 ? write(1, "$ ", 2) : 0;
			continue;
		}

		if (strcmp(bufferEntry, "exit\n") == 0)
			break;
		args = generate_args(bufferEntry);
		if (!args)
			return (2);
		if (strcmp(bufferEntry, "env\n") == 0)
			print_env();
		else
		{
			command = get_path(args[0]);
			if (command)
			{
				status = forkProcess(command, args);
				free(command);
			}
			else
				status = 2;
		}
		free(args);
		free(comandPathCopy);
		satty == 1 ? write(1, "$ ", 2) : 0;
	}
	free(bufferEntry);
	return (status);
}
