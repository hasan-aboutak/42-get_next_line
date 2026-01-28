#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define FD_MAX 1024

char	*get_next_line(int fd);
char	*read_and_stash(int fd, char *stash);
char	*extract_line(char *stash);
char	*clean_stash(char *stash);
size_t	ft_strlen(char *s);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2);

#endif
