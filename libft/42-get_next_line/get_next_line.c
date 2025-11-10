/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:06:10 by tbhuiyan          #+#    #+#             */
/*   Updated: 2025/07/12 00:36:45 by tbhuiyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	*read_line_gnl(int fd, char *stash, char *buffer)
{
	int	bytes_read;

	bytes_read = 1;
	while (!(ft_strchr_gnl(stash, '\n') && bytes_read > 0))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		stash = ft_strjoin_gnl(stash, buffer);
		if (!stash)
			return (NULL);
	}
	return (stash);
}

static char	*clean_line_gnl(char *line)
{
	char	*new_line;
	int		i;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0' || line[i + 1] == '\0')
		return (NULL);
	new_line = ft_substr_gnl(line, i + 1, ft_strlen_gnl(line) - i);
	if (!new_line)
	{
		free(new_line);
		return (NULL);
	}
	line[i + 1] = '\0';
	return (new_line);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*result;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (stash)
		{
			free(stash);
			stash = NULL;
		}
		return (NULL);
	}
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	result = read_line_gnl(fd, stash, buffer);
	free(buffer);
	if (!result)
		return (NULL);
	stash = clean_line_gnl(result);
	return (result);
}
