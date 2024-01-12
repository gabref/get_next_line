/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:16:08 by galves-f          #+#    #+#             */
/*   Updated: 2024/01/11 16:16:02 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
		if (*s++ == (char)c)
			return ((char *)--s);
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*newstr;
	int		size;
	int		i;

	size = ft_strlen(s);
	newstr = (char *)malloc(sizeof(char) * (size + 1));
	if (newstr == NULL)
		return (0);
	i = 0;
	while (*s)
		newstr[i++] = *s++;
	newstr[i] = '\0';
	return (newstr);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] && i < (size - 1))
		*dst++ = src[i++];
	*dst = '\0';
	return (ft_strlen(src));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*newstr;
	int		size_substring;
	int		original_size;

	if (s == NULL)
		return (NULL);
	original_size = ft_strlen(s);
	if (start >= (unsigned int)original_size)
		return (ft_strdup(""));
	size_substring = original_size - start;
	if (len > (unsigned int)size_substring)
		len = size_substring;
	newstr = (char *)malloc(sizeof(char) * len + 1);
	if (newstr == NULL)
		return (NULL);
	ft_strlcpy(newstr, s + start, len + 1);
	return (newstr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size1;
	int		size2;
	char	*newstr;
	int		i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	newstr = (char *)malloc(sizeof(char) + (size1 + size2 + 1));
	if (newstr == NULL)
		return (NULL);
	i = 0;
	while (*s1)
		newstr[i++] = *s1++;
	while (*s2)
		newstr[i++] = *s2++;
	newstr[i] = '\0';
	return (newstr);
}
