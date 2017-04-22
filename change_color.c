/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfedorko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 14:37:42 by lfedorko          #+#    #+#             */
/*   Updated: 2017/04/22 14:37:50 by lfedorko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_color(t_struct *map, int r, int g, int b)
{
	int	ij[2];
	int	l;

	ij[0] = 0;
	while (ij[0] < map->h[1])
	{
		ij[1] = 0;
		while (ij[1] < map->h[0])
		{
			l = 0;
			while (l < 4)
			{
				if (l == 0)
					map->c[ij[0]][ij[1]].color[l++] = r;
				else if (l == 1)
					map->c[ij[0]][ij[1]].color[l++] = g;
				else if (l == 2)
					map->c[ij[0]][ij[1]].color[l++] = b;
				else if (l == 3)
					map->c[ij[0]][ij[1]].color[l++] = 0;
			}
			ij[1]++;
		}
		ij[0]++;
	}
}
