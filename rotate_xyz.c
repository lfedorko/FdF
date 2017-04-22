/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_xyz.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfedorko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 18:41:31 by lfedorko          #+#    #+#             */
/*   Updated: 2017/04/22 18:41:34 by lfedorko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(t_struct *map)
{
	int		i;
	int		j;
	float	y;
	float	z;
	float	a;

	j = 0;
	a = -1.05;
	while (j < map->h[1])
	{
		i = 0;
		while (i < map->h[0])
		{
			y = map->c[j][i].y;
			z = map->c[j][i].z;
			map->c[j][i].y = y * (float)cos(a) + z * (float)sin(a);
			map->c[j][i].z = (-y) * (float)sin(a) + z * (float)cos(a);
			i++;
		}
		j++;
	}
}

void	rotate_y(t_struct *map)
{
	int		i;
	int		j;
	float	x;
	float	z;
	float	b;

	j = 0;
	b = 0.1;
	while (j < map->h[1])
	{
		i = 0;
		while (i < map->h[0])
		{
			x = map->c[j][i].x;
			z = map->c[j][i].z;
			map->c[j][i].x = x * (float)cos(b) + z * (float)sin(b);
			map->c[j][i].z = (-x) * (float)sin(b) + z * (float)cos(b);
			i++;
		}
		j++;
	}
}

void	rotate_z(t_struct *map)
{
	int		i;
	int		j;
	float	y;
	float	x;
	float	c;

	c = 0.0;
	j = 0;
	while (j < map->h[1])
	{
		i = 0;
		while (i < map->h[0])
		{
			x = map->c[j][i].x;
			y = map->c[j][i].y;
			map->c[j][i].x = x * (float)cos(c) + y * (float)sin(c);
			map->c[j][i].z = (-x) * (float)sin(c) + y * (float)cos(c);
			i++;
		}
		j++;
	}
}
