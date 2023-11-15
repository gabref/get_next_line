/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:39:06 by galves-f          #+#    #+#             */
/*   Updated: 2023/11/15 18:12:33 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	has_newline(int start, char *str)
{
	if (!str)
		return (0);
	while (str[start])
		if (str[start++] == '\n')
			return (1);
	return (0);
}

int	find_newline(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		if (str[i++] == '\n')
			return (--i);
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*strjoin(char *s1, char *s2, int s1_len, int s2_len)
{
	char	*newstr;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = malloc(sizeof(char));
		s1[0] = '\0';
	}
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	newstr = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (newstr == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		newstr[i++] = s1[j++];
	while (*s2)
		newstr[i++] = *s2++;
	newstr[i] = '\0';
	free(s1);
	return (newstr);
}

int	read_fd_add_cache(int fd, char **cache)
{
	int		rbytes;
	char	*buf;
	int		last_cache_len;

	buf = (char *)malloc(sizeof(char) + (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (0);
	rbytes = 1;
	last_cache_len = 0;
	while (rbytes > 0 && !has_newline(last_cache_len, *cache))
	{
		rbytes = read(fd, buf, BUFFER_SIZE);
		if (rbytes == -1)
			return (0);
		buf[rbytes] = '\0';
		last_cache_len = ft_strlen(*cache);
		*cache = strjoin(*cache, buf, last_cache_len, rbytes);
		if (*cache == NULL)
			return (0);
	}
	free(buf);
	return (1);
}

int	extract_line(char *cache, int cache_len, char **next_line)
{
	int	len;

	if (!cache)
		return (0);
	if (has_newline(0, cache))
		len = find_newline(cache) + 1;
	else
		len = cache_len;
	*next_line = malloc(sizeof(char) + (len + 1));
	if (*next_line == NULL)
		return (0);
	(*next_line)[len] = '\0';
	while (--len >= 0)
		(*next_line)[len] = cache[len];
	return (1);
}

int	clean_cache(char **cache, int cache_len)
{
	char	*temp;
	int		start;
	int		i;

	if (has_newline(0, *cache))
		start = find_newline(*cache) + 1;
	else
		start = cache_len;
	if ((cache_len - start + 1) == 0)
		return (1);
	temp = *cache;
	*cache = malloc(sizeof(char) * (cache_len - start + 1));
	if (*cache == NULL)
	{
		free(temp);
		return (0);
	}
	i = 0;
	while (temp[start])
		(*cache)[i++] = temp[start++];
	(*cache)[i] = '\0';
	free(temp);
	return (1);
}

char	*get_next_line(int fd)
{
	char		*next_line;
	static char	*cache;
	int			ok;
	int			cache_len;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, &next_line, 0) < 0)
		return (NULL);
	ok = read_fd_add_cache(fd, &cache);
	if (!ok)
		return (NULL);
	cache_len = ft_strlen(cache);
	ok = extract_line(cache, cache_len, &next_line);
	if (!ok)
		return (NULL);
	ok = clean_cache(&cache, cache_len);
	if (!ok)
		return (NULL);
	if (*next_line == '\0')
	{
		free(next_line);
		return (NULL);
	}
	return (next_line);
}
