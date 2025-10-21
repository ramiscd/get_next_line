/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 22:38:26 by rdamasce          #+#    #+#             */
/*   Updated: 2025/10/20 23:12:46 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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

int main()
{
	int fd; // Aonde será armazenado o numero do file descriptor.
	int i; // armazena index do arquivo que vamos iterar
	char* file_content = (char*)calloc(100, sizeof(char));
	int total = 0;

	fd = open("test.txt", O_RDONLY);
	
	if (fd < 0) {
		perror("erro ao abrir arquivo");
		exit(1);
	}
	printf("arquivo aberto com sucesso, fd=%i \n", fd);

	/*	while (fd)
	{
		read(fd, file_content, 8);
		printf("conteudo: %s", file_content);
	} */

	i = 0;
	// primeira chamada
	i = read(fd, file_content + total, 8);
	total += i;
	printf("conteudo 1ª chamada: %s \n", file_content);

	
	//Obter ponteiro do resto
	char *n1_ptr = ft_strchr(file_content, '\n');
	printf("caractere do conteudo ft_strchr: %s \n", n1_ptr);

	// se o conteudo tiver uma quebra de linha preciso copiar o "resto" do conteudo para uma variavel temporaria, se nao, continuar iteracao.
	int size = ft_strlen(file_content);
	printf("O tamanho da string depois da primeira iteracao: %i\n", size);

	unsigned int index = n1_ptr - file_content;
	printf("indice: %i \n", index);

	// passar conteudo do resto
	char *rest = ft_substr(file_content, index, size);
	printf("contrudo do resto: %s \n", rest);

	

	// segunda chamada
/* 	i = read(fd, file_content + total, 2);
	total += i;
	printf("conteudo 1ª chamada: %s \n:", file_content); */
}