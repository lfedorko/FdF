/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfedorko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 18:40:31 by lfedorko          #+#    #+#             */
/*   Updated: 2017/04/22 18:40:34 by lfedorko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	push_bres2(t_struct *map, int i, int j)
{
	t_bres	*bres;

	bres = (t_bres *)malloc(sizeof(t_bres));
	if (i + 1 < map->h[0])
	{
		bres->x[0] = map->c[j][i].x;
		bres->x[1] = map->c[j][i + 1].x;
		bres->y[0] = map->c[j][i].y;
		bres->y[1] = map->c[j][i + 1].y;
		bresenham(map, bres, i, j);
	}
	if (j + 1 < map->h[1])
	{
		bres->x[0] = map->c[j][i].x;
		bres->x[1] = map->c[j + 1][i].x;
		bres->y[0] = map->c[j][i].y;
		bres->y[1] = map->c[j + 1][i].y;
		bresenham(map, bres, i, j);
	}
	free(bres);
}

void	push_bres1(t_struct *map)
{
	int		i;
	int		j;

	j = 0;
	while (j < map->h[1])
	{
		i = 0;
		while (i < map->h[0])
		{
			push_bres2(map, i, j);
			i++;
		}
		j++;
	}
}
