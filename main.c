/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfedorko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 16:32:43 by lfedorko          #+#    #+#             */
/*   Updated: 2017/03/31 16:33:11 by lfedorko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int     main(int argc, char *argv[])
{
	int tmp_handw[2];
	t_struct *map;

	if (argc != 2)
	{
		write(1, "Usage : ./fdf <filename>\n", 25);
		return (0);
	}
	if (valid_map(argv[1], tmp_handw) == 0)
	{
		map = map_to_struct(argv[1], tmp_handw);
		draw(map);
	}
	return (0);
}