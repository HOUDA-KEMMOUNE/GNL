#include "get_next_line.h"

char	*ft_strjoin(char *line, char c)
{
	char	*result;
	int		i;

	i = 0;
	if (line == NULL)
	{
		result = malloc(2);
		result[0] = c;
		result[1] = '\0';
		return (result);
	}
	while (line[i])
		i++;
	result = malloc(i + 2);
	i = 0;
	while (line[i])
	{
		result[i] = line[i];
		i++;
	}
	result[i] = c;
	result[i + 1] = '\0';
	free (line);
	return (result);
}

char	*get_next_line(int fd)
{
	static int	index;
	static int	readed;
	static char	buffer[BUFFER_SIZE];
	char		c;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (index >= readed)
		{
			index = 0;
			readed = read(fd, buffer, BUFFER_SIZE);
			if (readed <= 0)
				break ;
		}
		c = buffer[index];
		index++;
		line = ft_strjoin(line, c);
		if (!line || c == '\n')
			break ;
	}
	return (line);
}

int	main()
{
	int		fd;
	char	*line;
	int		i;

	fd = open("file.txt", O_RDWR);
	i = 0;
	while (i <= 10)
	{
		line = get_next_line(fd);
		printf("line[%d] --> %s", i, line);
		i++;
	}
	printf("\n");
}