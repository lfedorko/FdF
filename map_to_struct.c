/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfedorko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 17:25:45 by lfedorko          #+#    #+#             */
/*   Updated: 2017/04/10 17:25:47 by lfedorko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void show_coord(t_struct *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->h[1])
	{
		j = 0;
		while (j < map->h[0])
		{
			printf("[%f , %f, %f]", map->c[i][j].x, map->c[i][j].y, map->c[i][j].z);

			j++;
		}
		printf("\n");
		i++;
	}
}

static int	hextoint(char *a, unsigned int len)
{
	int		i;
	int		val;
	int		j;

	val = 0;
	i = 0;
	j = 0;
	while (j < 2)
	{
		a[j] = ft_toupper(a[j]);
		j++;
	}
	while (i < len)
	{
		if (a[i] <= '9')
			val += (a[i] - '0') * (1 << (4 * (len - i - 1)));
		else
			val += (a[i] - 55) * (1 << (4 * (len - i - 1)));
		i++;
	}
	return (val);
}

static void	parse_color(char *tmp, int i, int j, t_struct *map)
{
	char	*color;
	int		k;
	int		color_rgb;

	k = 0;
	color = ft_strnew(2);
	while ((*tmp != ' ' || *tmp != '\t') && *tmp && k < 4)
	{
		if (ft_strchr("0123456789ABCDEFabcdef", *tmp)
			&& ft_strchr("0123456789ABCDEFabcdef", *(tmp + 1)))
		{
			color = ft_strncpy(color, tmp, 2);
			color_rgb = hextoint(color, 2);
			if (color_rgb >= 0 && color_rgb <= 255)
				map->c[j][i].color[k++] = color_rgb;
		}
		else
		{
			free(color);
			return ;
		}
		tmp += 2;
	}
	free(color);
}

static char	*next_numb(t_struct *map, char *tmp, int i, int j)
{
	while (*tmp == ' ' || *tmp == '\t')
		tmp++;
	while (*tmp != ',' && *tmp != ' ' && *tmp)
		tmp++;
	if (*tmp == ',')
	{
		tmp++;
		if (!ft_strncmp(tmp, "0x", 2))
		{
			tmp = tmp + 2;
			parse_color(tmp, i, j, map);
		}
		tmp = ft_strchr(tmp, ' ');
	}
	return (tmp);
}

static void	fill_struct(t_struct *map, char *input_map)
{
	int		fd;
	char	*line;
	int		i;
	int		j;
	char	*tmp;

	j = 0;
	fd = open(input_map, O_RDONLY);
	while (get_next_line(fd, &line) > 0 && j < map->h[1])
	{
		tmp = line;
		i = 0;
		while (i < map->h[0])
		{
			map->c[j][i].x = i;
			map->c[j][i].y = j;
			map->c[j][i].z = (float)ft_atoi(tmp);
			tmp = next_numb(map, tmp, i, j);
			i++;
		}
		j++;
		free(line);
	}
	close(fd);
}

t_struct	*map_to_struct(char *input_map, int *tmp_handw)
{
	t_struct	*map;
	int			i;

	i = 0;
	map = (t_struct *)malloc(sizeof(t_struct));
	map->h[0] = tmp_handw[0];
	map->h[1] = tmp_handw[1];
	map->c = (t_point **)malloc((map->h[1] + 1) * sizeof(t_point *));
	map->c[map->h[1]] = NULL;
	while (i < map->h[1])
		map->c[i++] = (t_point *)malloc((map->h[0]) * sizeof(t_point));
	fill_struct(map, input_map);
	return (map);
}
