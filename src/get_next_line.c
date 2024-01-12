/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:39:06 by galves-f          #+#    #+#             */
/*   Updated: 2024/01/11 19:24:54 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	read_and_add_cache(int fd, t_cache **cache)
{
	char	buffer[BUFFER_SIZE + 1];
	int		nbytes;
	char	*cur;

	nbytes = read(fd, buffer, BUFFER_SIZE);
	buffer[nbytes] = '\0';
	if (nbytes == -1)
		return (0);
	while (nbytes != 0 && !ft_strchr(buffer, '\n'))
	{
		cur = (*cache)->str;
		(*cache)->str = ft_strjoin(cur, buffer);
		(*cache)->len += nbytes;
		free(cur);
		nbytes = read(fd, buffer, BUFFER_SIZE);
		if (nbytes == -1)
			return (0);
		buffer[nbytes] = '\0';
	}
	return (1);
}

char	*clean_cache_and_get_line(t_cache **cache)
{
	char	*newline;
	char	*cur;
	int		i;

	if ((*cache)->str == NULL || (*cache)->str[0] == '\0')
		return (NULL);
	i = 0;
	while ((*cache)->str[i] != '\n' && (*cache)->str[i] != '\0')
		i++;
	newline = ft_substr((*cache)->str, 0, i);
	cur = (*cache)->str;
	(*cache)->str = ft_substr((*cache)->str, i + 1, (*cache)->len - i);
	(*cache)->len -= i;
	free(cur);
	return (newline);
}

void	init_cache(t_cache **cache)
{
	if (*cache == NULL)
	{
		printf("initialize\n");
		*cache = (t_cache *)malloc(sizeof(t_cache));
		(*cache)->str = ft_strdup("");
		(*cache)->len = 0;
	}
}

int	clean_cache(t_cache **cache)
{
	if ((*cache)->len == 0)
	{
		printf("clean\n");
		free((*cache)->str);
		free(*cache);
		*cache = NULL;
		return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static t_cache	*cache;
	int				ok;
	char			*newline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	init_cache(&cache);
	ok = read_and_add_cache(fd, &cache);
	if (!ok)
		return (NULL);
	newline = clean_cache_and_get_line(&cache);
	if (!newline)
	{
		clean_cache(&cache);
		return (NULL);
	}
	return (newline);
}
