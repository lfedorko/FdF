#include "fdf.h"

int		key_exit(int keycode)
{

	mlx_clear_window(map->mlx, map->win);
	(keycode == 53) ? exit(0) : return(1);
	(keycode == 27) ? change_color(255,0,0,0) : 0
}

int   key_zoom(int keycode)
{



}



void  key_hook;
{
	mlx_hook(map->win, 2, 5, key_exit, map->mlx);


}