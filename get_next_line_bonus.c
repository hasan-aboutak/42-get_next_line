
#include "get_next_line_bonus.h"

char	*read_and_stash(int fd, char *stash)
{
	char	*buffer;
	int		bytes_read;
	char	*tmp;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		tmp = ft_strjoin(stash, buffer);
		free(stash);
		stash = tmp;
	}
	free(buffer);
	return (stash);
}

char	*extract_line(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	if (!stash || !stash[0])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*clean_stash(char *stash)
{
	char	*new_stash;
	int		i;
	int		j;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	new_stash = malloc((ft_strlen(stash) - i) * sizeof(char));
	if (!new_stash)
		return (NULL);
	i++;
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[FD_MAX];
	char		*line;

	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = read_and_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = extract_line(stash[fd]);
	stash[fd] = clean_stash(stash[fd]);
	return (line);
}

