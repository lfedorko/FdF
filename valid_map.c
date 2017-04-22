/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfedorko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 18:32:06 by lfedorko          #+#    #+#             */
/*   Updated: 2017/04/01 18:32:16 by lfedorko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	sizefind(char *line)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] != ' ' && line[i] != '\t' && line[i])
			size++;
		while (line[i] != ' ' && line[i] != '\t' && line[i])
			i++;
	}
	return (size);
}

static int	valid_len(int fd, int *tmp_handw)
{
	char *line;

	if (get_next_line(fd, &line) <= 0)
		return (write(1, "No data find\n", 13));
	tmp_handw[1] = 1;
	tmp_handw[0] = sizefind(line);
	free(line);
	while (get_next_line(fd, &line) > 0)
	{
		if (sizefind(line) < tmp_handw[0])
		{
			free(line);
			close(fd);
			return (write(1, "Found wrong line length. Exiting.\n", 34));
		}
		tmp_handw[1]++;
		free(line);
	}
	close(fd);
	return (0);
}

int			valid_map(char *input_map, int *tmp_handw)
{
	int		fd;

	if ((fd = open(input_map, O_RDONLY)) < 0)
		return (write(1, "No file\n", 8));
	return (valid_len(fd, tmp_handw));
}
