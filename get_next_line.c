/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: side-oli <side-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 11:09:15 by side-oli          #+#    #+#             */
/*   Updated: 2026/05/05 16:56:06 by side-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free_and_join(char *stash, char *buffer)
{
	char	*temp;

	if (!stash)
	{
		stash = malloc(1);
		stash[0] = '\0';
	}
	temp = ft_strjoin(stash, buffer);
	free(stash);
	return (temp);
}

char	*get_line(char	*stash)
{
	size_t	ctr;
	char	*tmp;
	char	*line;

	ctr = 0;
	while (stash[ctr] && stash[ctr] != '\n')
		ctr++;
	line = malloc(ctr + 2);
	tmp = line;
	while (*stash)
	{
		if (*stash == '\n')
			break ;
		*line++ = *stash++;
	}
	if (*stash == '\n')
		*line++ = '\n';
	*line = '\0';
	return (tmp);
}

char	*cut_stash(char *stash)
{
	size_t	i;
	char	*str;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	str = malloc((ft_strlen(stash) - i));
	if (!str)
		return (NULL);
	if (stash[i])
		ft_strlcpy(str, &stash[i + 1], (ft_strlen(stash) - i));
	else
	{
		free(stash);
		return (NULL);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	char		*line;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(stash);
			stash = NULL;
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stash = ft_free_and_join(stash, buffer);
	}
	if (!stash || !*stash)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	free(buffer);
	line = get_line(stash);
	stash = cut_stash(stash);
	return (line);
}
