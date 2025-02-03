/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:44:05 by kevisout          #+#    #+#             */
/*   Updated: 2024/12/27 12:03:15 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*append_char(char *str, char c, int len)
{
	char	*new_str;
	int		i;

	new_str = (char *)malloc(len + 2);
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i++] = c;
	new_str[i] = '\0';
	free(str);
	return (new_str);
}

static void	init_line_and_len(char **line, int *len)
{
	*line = NULL;
	*len = 0;
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int	bytes_read = 0;
	static int	index = 0;
	char		*line;
	int			len;

	init_line_and_len(&line, &len);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (index >= bytes_read)
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			index = 0;
			if (bytes_read <= 0)
				return (line);
		}
		while (index < bytes_read)
		{
			line = append_char(line, buffer[index], len++);
			if (buffer[index++] == '\n')
				return (line);
		}
	}
}
