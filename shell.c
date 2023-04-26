#include "shell.h"

/**
 * main - replicate of a shell.
 * @argc: number of params.
 * @argv: array with values of paramams.
 * Return: return exit status of last program.
*/

int main(int argc __attribute__((unused)), char *argv[])
{
	size_t sizeBuffer = 0;
	char *command = NULL, *bufferEntry = NULL, **args = NULL;
	int status = 0, satty = isatty(STDOUT_FILENO), count = 0;
	struct stat buffer;

	satty == 1 ? write(1, "$ ", 2) : 0;
	while (getline(&bufferEntry, &sizeBuffer, stdin) >= 0)
	{
		count += 1;
		if (strlen(bufferEntry) == 1)
		{
			satty == 1 ? write(1, "$ ", 2) : 0;
			continue;
		}
		args = generate_args(bufferEntry);
		if (strcmp(args[0], "exit") == 0)
		{
			if (bufferEntry && args[0])
				free(args[0]), free(args);
			exit(status);
		}
		if (strcmp(args[0], "env") == 0)
		{
			print_env();
			status = 0;
			return (status);
		}
		if (args && args[0])
		{
			/*If is rute absolute, ejecute this, if is only command, goes to the other*/
			if (stat(args[0], &buffer) == 0)
				command = args[0], status = forkProcess(command, args);
			else if (stat(args[0], &buffer) == -1)
			{
				command = get_path(args[0]);
				if (command)
				{
					status = forkProcess(command, args), free(command);
					(status == -1) ? status = 2 : 0; /* si forkProcess falla, status es 2 */
				}
				else
					printErr(count, argv[0], bufferEntry), status = 127;
			}
		}
		free(args), satty == 1 ? write(1, "$ ", 2) : 0;
	}
	free(bufferEntry);
	return (status);
}
