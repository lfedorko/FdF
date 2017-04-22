/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfedorko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 17:25:29 by lfedorko          #+#    #+#             */
/*   Updated: 2017/04/10 17:25:31 by lfedorko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	push_color(t_struct *map, int i, int j)
{
	int k;
	int pos;
	int s;
	int l;

	s = map->size;
	pos = ((int)map->c[j][i].x  + s / 2) * 4 + ((int)map->c[j][i].y + s / 2) * map->s_l;
	if (pos >= 0 && pos < s * s * 4)
	{
		k = 2;
		l = 0;
		while (k > -1)
		{
			map->a_px[pos + l] = map->c[j][i].color[k];
			k--;
			l++;
		}
		if (map->c[j][i].color[3])
			map->a_px[pos + 3] = map->c[j][i].color[3];
	}
}

static void	push_address(t_struct *map)
{
	int i;
	int j;
	int s;

	j = 0;
	s = map->size;
	while (j < map->h[1])
	{
		i = 0;
		while (i < map->h[0])
		{		
			if (map->c[j][i].x > -s / 2 && map->c[j][i].x < s/2
				&& map->c[j][i].y < s / 2 && map->c[j][i].y > - s / 2)
				push_color(map, i , j);
			i++;
		}
		j++;
	}
//	mlx_string_put(map->mlx, map->win, 50, 50, 0xFFFFFFF, "azazazaza");
	mlx_put_image_to_window(map->mlx, map->win, map->n_i, 0, 0);
}

static void	centre_coord(t_struct *map)
{

	int i; 
	int j;

	j = 0;
	while (j < map->h[1])
	{
		i = 0;
		while (i < map->h[0])
		{
			map->c[j][i].x -= map->h[0] / 2;
			map->c[j][i].x *= 50;
			map->c[j][i].y -= map->h[1] / 2;
			map->c[j][i].y *= 50;
 			i++;
		}
		j++;
	}
	show_coord(map);
}

void		draw(t_struct *map)
{
	int i;
	int j;

	j = 0;
	centre_coord(map);
	map->size = 1000;
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, map->size, map->size, "FdF");
	map->n_i = mlx_new_image(map->mlx, map->size, map->size);
	map->a_px = mlx_get_data_addr(map->n_i, &(map->b), &(map->s_l), &(map->e));
	mlx_hook(map->win, 2, 5, key_exit, map->mlx);
//	rotate_y(map);
	rotate_x(map);
//	printf("%d  %d %d %d\n", 	map->b, map->s_l, map->e, j);
	push_address(map);
	free(map->a_px);
	free(map); 
	mlx_loop(map->mlx);
}

