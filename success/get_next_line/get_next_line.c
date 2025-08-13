#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>


char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

size_t	ft_strlen_up(char *s, char c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != c)
		i++;
	return (i);
}

char	*ft_strdup_up(char *s1, char c)
{
	size_t	len;
	size_t	i;
	int		character;
	char	*s2;

	if (!s1 || *s1 == '\0')
		return (NULL);
	character = 0;
	if (c == '\0')
		character = 1;
	else if (c == '\n')
		character = 2;
	len = ft_strlen_up(s1, c) + character;
	s2 = (char *)malloc(sizeof(char) * len);
	if (s2 == NULL)
		return (NULL);
	i = 0;
	while (i < len - 1 && s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strjoin_up(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	len1;
	size_t	len2;
	char	*s;

	len1 = ft_strlen_up(s1, '\0');
	len2 = ft_strlen_up(s2, '\0');
	if (!s1 || !s2)
		return (NULL);
	s = (char *)malloc(len1 + len2 + 1);
	if (!s)
		return (NULL);
	i = 0;
	while (i < len1 && s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len2 && s2[j])
		s[i++] = s2[j++];
	s[i] = '\0';
	return (s);
}

char	*ft_fill_line(char *line, char *buffer, char **container, int new_line)
{
	char	*temporary;

	if (!line && new_line == 1)
		line = ft_strdup_up(buffer, '\n');
	else if (!line && new_line == 0)
		line = ft_strdup_up(buffer, '\0');
	else if (line)
	{
		temporary = ft_strjoin_up(line, buffer);
		free(line);
		line = ft_strdup_up(temporary, '\0');
		free(temporary);
	}
	if (new_line == 1)
		*container = ft_strdup_up(ft_strchr(buffer, '\n') + 1, '\0');
	if (ft_strchr(line, '\n') && *ft_strchr(line, '\n') + 1 != '\0')
	{
		temporary = ft_strdup_up(line, '\n');
		free(line);
		line = ft_strdup_up(temporary, '\n');
		free(temporary);
	}
	free(buffer);
	return (line);
}

char	*ft_read_line(char *line, char **container, int fd)
{
	char	*buffer;
	ssize_t	readed;

	while (1)
	{
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE) + 1);
		if (!buffer)
			return (NULL);
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed < 0)
		{
			free(buffer);
			free(line);
			return (NULL);
		}
		else if (readed == 0)
		{
			free(buffer);
			return (line);
		}
		buffer[readed] = '\0';
		if (ft_strchr(buffer, '\n'))
			return (ft_fill_line(line, buffer, &*container, 1));
		line = ft_fill_line(line, buffer, &*container, 0);
	}
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*container;
	char		*temporary;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (container && !ft_strchr(container, '\n'))
	{
		line = ft_strdup_up(container, '\0');
		free(container);
		container = NULL;
	}
	else if (container && ft_strchr(container, '\n'))
	{
		temporary = ft_strdup_up(container, '\0');
		free(container);
		container = ft_strdup_up(ft_strchr(temporary, '\n') + 1, '\0');
		line = ft_strdup_up(temporary, '\n');
		free(temporary);
		return (line);
	}
	return (ft_read_line(line, &container, fd));
}