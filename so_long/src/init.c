/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 18:03:01 by jbak              #+#    #+#             */
/*   Updated: 2022/08/12 20:07:58 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "so_long.h"

void	*open_xpm(t_mlx *mlx, char *path, int size1, int size2)
{
	return (mlx_xpm_file_to_image(mlx->mlx, path, &size1, &size2));
}

void	put_in(t_solong *sl, void *img, int x, int y)
{
	mlx_put_image_to_window(sl->mlx.mlx, sl->mlx.win, img, x * IMGS, y * IMGS);
}

static void	get_enemy(t_solong *sl, int x, int y)
{
	if (sl->map.lines[y][x] == 'X')
	{
		put_in(sl, sl->map.enemy, x, y);
		sl->ene_x = x;
		sl->ene_y = y;
		sl->ene_chk = ON;
	}
}

static void	spreadimg(t_solong *sl)
{
	int	x;
	int	y;

	y = -1;
	while (++y < sl->map.hei)
	{
		x = -1;
		while (++x < sl->map.wid)
		{
			put_in(sl->mlx.mlx, sl->map.tile, x, y);
			if (sl->map.lines[y][x] == '1')
				put_in(sl, sl->map.wall, x, y);
			else if (sl->map.lines[y][x] == 'E')
				put_in(sl, sl->map.exit, x, y);
			else if (sl->map.lines[y][x] == 'C')
				put_in(sl, sl->map.key, x, y);
			else if (sl->map.lines[y][x] == 'P')
			{
				put_in(sl, sl->player.img[2][0], x, y);
				sl->player.x = x;
				sl->player.y = y;
			}
			get_enemy(sl, x, y);
		}
	}
}

void	init_it(t_solong *sl, char *filename)
{
	sl->mlx.mlx = mlx_init();
	sl->mlx.win = mlx_new_window(sl->mlx.mlx, sl->map.wid * IMGS, \
	(sl->map.hei * IMGS), filename);
	sl->mlx.img = mlx_new_image(sl->mlx.mlx, sl->map.wid * IMGS, \
	(sl->map.hei * IMGS));
	sl->mlx.addr = mlx_get_data_addr(sl->mlx.img, &sl->mlx.bpp, \
	&sl->mlx.len, &sl->mlx.endian);
	sl->map.tile = open_xpm(&sl->mlx, "./imgs/tile.xpm", IMGS, IMGS);
	sl->map.wall = open_xpm(&sl->mlx, "./imgs/wall.xpm", IMGS, IMGS);
	sl->map.exit = open_xpm(&sl->mlx, "./imgs/exit.xpm", IMGS, IMGS);
	sl->map.key = open_xpm(&sl->mlx, "./imgs/collect.xpm", IMGS, IMGS);
	sl->map.enemy = open_xpm(&sl->mlx, "./imgs/enemy.xpm", IMGS, IMGS);
	get_player_img(sl);
	get_font_img(sl);
	spreadimg(sl);
}
