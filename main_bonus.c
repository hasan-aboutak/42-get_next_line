#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line_bonus.h"

int	main(void)
{
	int		fd1;
	int		fd2;
	char	*line;

	fd1 = open("file1.txt", O_RDONLY);
	fd2 = open("file2.txt", O_RDONLY);

	line = get_next_line(fd1);
	printf("fd1: %s", line);
	free(line);

	line = get_next_line(fd2);
	printf("fd2: %s", line);
	free(line);

	line = get_next_line(fd1);
	printf("fd1: %s", line);
	free(line);

	line = get_next_line(fd2);
	printf("fd2: %s", line);
	free(line);

	line = get_next_line(fd1);
	printf("fd1: %s", line);
	free(line);

	line = get_next_line(fd2);
	printf("fd2: %s", line);
	free(line);

	close(fd1);
	close(fd2);
}
