/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 22:38:26 by rdamasce          #+#    #+#             */
/*   Updated: 2025/10/23 22:29:30 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/**
 * @brief Reads the file content until a newline or EOF is found.
 *
 * This function reads from the file descriptor `fd` into a temporary buffer,
 * appending the data to `file_content` until it finds a
 * newline character (`'\n'`) or reaches the end of the file.
 * It dynamically allocates memory as needed.
 *
 * @param fd The file descriptor to read from.
 * @param file_content A string containing previously read data (may be empty).
 * @return A pointer to the updated file_content string containing the read data,
 *         or NULL if an error occurs.
 */
static char	*ft_read_file(int fd, char *file_content)
{
	char	*buffer;
	char	*temp;
	int		read_count;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	read_count = 1;
	while (!ft_strchr(file_content, '\n') && read_count > 0)
	{
		read_count = read(fd, buffer, BUFFER_SIZE);
		if (read_count < 0)
			return (free(buffer), free(file_content), NULL);
		buffer[read_count] = '\0';
		temp = file_content;
		file_content = ft_strjoin(file_content, buffer);
		free(temp);
	}
	free(buffer);
	return (file_content);
}

/**
 * @brief Extracts the current line from the file content.
 *
 * This function searches for the first newline character in `file_content`
 * and copies everything up to (and including) that newline into a new string.
 * If no newline is found, it duplicates the entire `file_content`.
 *
 * @param file_content The full text read so far from the file.
 * @return A newly allocated string containing the next line,
 *         or NULL if no content is available.
 */
static char	*ft_extract_line(char *file_content)
{
	char	*line;
	char	*nl_ptr;
	size_t	index;

	if (!file_content || !*file_content)
		return (NULL);
	nl_ptr = ft_strchr(file_content, '\n');
	if (nl_ptr)
	{
		index = nl_ptr - file_content;
		line = ft_substr(file_content, 0, index + 1);
	}
	else
		line = ft_strdup(file_content);
	return (line);
}

/**
 * @brief Extracts the remaining part of the file after the first newline.
 *
 * After a line has been extracted, this function saves the leftover
 * text (everything after the newline) for the next call to get_next_line.
 * If there is no remaining text, it returns NULL.
 *
 * @param file_content The full text read from the file.
 * @return A newly allocated string containing the remaining text,
 *         or NULL if there is nothing left.
 */
static char	*ft_extract_rest(char *file_content)
{
	char	*rest;
	char	*nl_ptr;
	size_t	index;

	nl_ptr = ft_strchr(file_content, '\n');
	if (!nl_ptr)
		return (NULL);
	index = nl_ptr - file_content;
	rest = ft_substr(file_content, index + 1,
			ft_strlen(file_content) - index - 1);
	if (!*rest)
		return (free(rest), NULL);
	return (rest);
}

/**
 * @brief Reads and returns the next line from a file descriptor.
 *
 * This is the main function of the get_next_line project.
 * It reads from the file descriptor `fd` and returns one line at a time,
 * including the newline character if present.
 *
 * Between calls, it keeps track of leftover text using a static variable,
 * allowing it to continue reading from where it left off.
 *
 * @param fd The file descriptor to read from.
 * @return A string containing the next line, or NULL if EOF or an error occurs.
 */
char	*get_next_line(int fd)
{
	static char	*rest;
	char		*file_content;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	file_content = ft_strdup("");
	if (rest)
	{
		temp = file_content;
		file_content = ft_strjoin(rest, file_content);
		free(temp);
		free(rest);
		rest = NULL;
	}
	file_content = ft_read_file(fd, file_content);
	if (!file_content || !*file_content)
		return (free(file_content), NULL);
	line = ft_extract_line(file_content);
	rest = ft_extract_rest(file_content);
	return (free(file_content), line);
}

/* #include <fcntl.h>
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (perror("error to open the file"), 1);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
} */