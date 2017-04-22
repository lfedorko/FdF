/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenhem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfedorko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 17:27:31 by lfedorko          #+#    #+#             */
/*   Updated: 2017/04/10 17:27:32 by lfedorko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	push_color_b(t_struct *map, float x, float y, int *bres)
{
	int	k;
	int	pos;
	int	s;
	int l;

	s = map->size;
	pos = (x + s / 2) * 4 + (y + s / 2) * map->s_l;
	if (pos >= 0 && pos < s * s * 4)
	{
		k = 2;
		l = 0;
		while (k > -1)
		{
			map->a_px[pos + l] = map->c[bres[1]][bres[0]].color[k];
			k--;
			l++;
		}
	}
}

static void	bresenham2(t_struct *map, t_bres *bres)
{
	while ((int)bres->x1 < bres->end)
	{
		bres->x1++;
		if (bres->d < 0)
			bres->d = bres->d + 2 * bres->dy;
		else
		{
			bres->y1 = bres->y1 + 1;
			bres->d = bres->d + 2 * (bres->dy - bres->dx);
		}
		if ((bres->x1 > -map->size / 2) && (bres->x1 < map->size / 2)
			&& (bres->y1 < map->size / 2) && (bres->y1 > -map->size / 2))
		push_color_b(map, bres->x1, bres->y1, bres->p);
	}
}

static void	bresenham1(t_struct *map, t_bres *bres)
{
	if (bres->y[0] > bres->y[1])
	{
		bres->x1 = bres->x[1];
		bres->y1 = bres->y[1];
		bres->end = bres->y[0];
	}
	else
	{
		bres->x1 = bres->x[0];
		bres->y1 = bres->y[0];
		bres->end = bres->y[1];
	}
	while ((int)bres->y1 < bres->end)
	{
		bres->y1++;
		if (bres->x1 > -map->size / 2 && bres->x1 < map->size / 2
			&& bres->y1 < map->size / 2 && bres->y1 > -map->size / 2)
		push_color_b(map, bres->x1, bres->y1, bres->p);
	}
}

void		bresenham(t_struct *map, t_bres *bres, int i, int j)
{
	bres->p[0] = i;
	bres->p[1] = j;
	bres->dx = fabs((bres->x[1] - bres->x[0]));
	bres->dy = fabs((bres->y[1] - bres->y[0]));
	bres->d = 2 * bres->dy - bres->dx;
	if (bres->x[0] > bres->x[1])
	{
		bres->x1 = bres->x[1];
		bres->y1 = bres->y[1];
		bres->end = bres->x[0];
		bresenham2(map, bres);
	}
	else if (bres->x[0] == bres->x[1])
		bresenham1(map, bres);
	else
	{
		bres->x1 = bres->x[0];
		bres->y1 = bres->y[0];
		bres->end = bres->x[1];
		bresenham2(map, bres);
	}
}
