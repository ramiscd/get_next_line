/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdamasce <rdamasce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 22:38:14 by rdamasce          #+#    #+#             */
/*   Updated: 2025/10/23 20:34:40 by rdamasce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
