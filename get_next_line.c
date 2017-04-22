/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfedorko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 14:16:25 by lfedorko          #+#    #+#             */
/*   Updated: 2017/01/23 16:35:55 by lfedorko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		check_buffer(char *buffer, char **line)
{
	static char	*add_buffer;
	char		*new_buffer;
	int			i;
	int			one;

	i = 0;
	one = 1;
	new_buffer = ft_strjoin(add_buffer, buffer);
	ft_strdel(&add_buffer);
	if (new_buffer[i] == '\0')
		return (0);
	while (new_buffer[i] != '\0' && new_buffer[i] != '\n')
		i++;
	if (new_buffer[i] == '\n' ||
		(new_buffer[i] == '\0' && buffer[0] == '\0' && ((one = 0) || 1)))
	{
		(*line) = ft_strncpy(ft_strnew(i + 1), new_buffer, i);
		add_buffer = ft_strdup(new_buffer + i + one);
		ft_strdel(&new_buffer);
		return (1);
	}
	add_buffer = ft_strdup(new_buffer);
	ft_strdel(&new_buffer);
	return (2);
}

int				get_next_line(const int fd, char **line)
{
	char	buffer[BUFF_SIZE + 1];
	int		i;
	int		count;

	if (BUFF_SIZE <= 0 || fd < 0)
		return (-1);
	i = read(fd, buffer, BUFF_SIZE);
	if (i < 0)
		return (-1);
	buffer[i] = '\0';
	count = check_buffer(buffer, *(&line));
	while (count == 2)
	{
		i = read(fd, buffer, BUFF_SIZE);
		buffer[i] = '\0';
		count = check_buffer(buffer, *(&line));
	}
	if (count == 1)
		return (1);
	return (0);
}
