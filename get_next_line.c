/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 22:38:26 by rdamasce          #+#    #+#             */
/*   Updated: 2025/10/21 23:13:32 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *string)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = (char *) malloc(ft_strlen((char *)string) * sizeof(char) + 1);
	if (ptr == NULL)
	{
		return (NULL);
	}
	else
	{
		while (string[i] != '\0')
		{
			ptr[i] = string[i];
			i++;
		}
	}
	ptr[i] = '\0';
	return (ptr);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	size_src;

	i = 0;
	size_src = ft_strlen(src);
	if (!size)
		return (size_src);
	i = 0;
	while (i < (size - 1) && src[i])
	{
		dest[i] = src[i];
		i ++;
	}
	dest[i] = 0;
	return (size_src);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	size_t			max_len;

	if (start > ft_strlen(s))
	{
		return (ft_strdup(""));
	}
	max_len = ft_strlen(s) - start;
	if (len < max_len)
	{
		max_len = len;
	}
	str = (char *) malloc((max_len + 1) * sizeof(char));
	if (!str)
	{
		return (NULL);
	}
	ft_strlcpy(str, s + start, max_len + 1);
	return (str);
}

char	*ft_strchr(const char *string, int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	while (*string)
	{
		if ((unsigned char)*string == uc)
			return ((char *)string);
		string++;
	}
	if ((unsigned char)*string == uc)
		return ((char *)string);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		count1;
	int		count2;
	int		total;
	int		i;
	char	*join;

	count1 = ft_strlen(s1);
	count2 = ft_strlen(s2);
	total = count1 + count2;
	join = (char *)malloc((total + 1) * sizeof(char));
	if (!join)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		join[i] = s1[i];
		i++;
	}
	count2 = 0;
	while (s2[count2] != '\0')
		join[i++] = s2[count2++];
	join[i] = '\0';
	return (join);
}

char	*get_next_line(int fd)
{
	static char	*rest;             // guarda o conteúdo que sobrou da última chamada
	char		*file_content;     // conteúdo acumulado da leitura
	char		*buffer;           // leitura temporária
	char		*line;             // linha a retornar
	char		*newline_ptr;      // ponteiro para '\n'
	int			read_count;
	size_t		index;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	// inicia string vazia e buffer
	file_content = ft_strdup("");
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer || !file_content)
		return (NULL);

	// concatena o resto anterior, se existir
	if (rest)
	{
		char *temp = file_content;
		file_content = ft_strjoin(rest, file_content);
		free(temp);
		free(rest);
		rest = NULL;
	}

	// lê do arquivo até achar '\n' ou EOF
	read_count = 1;
	while (!ft_strchr(file_content, '\n') && read_count > 0)
	{
		read_count = read(fd, buffer, BUFFER_SIZE);
		if (read_count < 0)
		{
			free(buffer);
			free(file_content);
			return (NULL);
		}
		buffer[read_count] = '\0';
		char *temp = file_content;
		file_content = ft_strjoin(file_content, buffer);
		free(temp);
	}

	free(buffer);

	// fim do arquivo e nada pra retornar
	if (read_count == 0 && file_content[0] == '\0')
	{
		free(file_content);
		return (NULL);
	}

	// separa linha e resto
	newline_ptr = ft_strchr(file_content, '\n');
	if (newline_ptr)
	{
		index = newline_ptr - file_content;
		line = ft_substr(file_content, 0, index + 1);
		rest = ft_substr(file_content, index + 1, ft_strlen(file_content) - index - 1);
	}
	else
	{
		line = ft_strdup(file_content);
		rest = NULL;
	}

	free(file_content);
	if (!line || line[0] == '\0')
	{
		free(line);
		line = NULL;
	}
	return (line);
}

#include <fcntl.h>
int main(void)
{
	int fd;
	char *line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (perror("erro ao abrir arquivo"), 1);

	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}