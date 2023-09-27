/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_calc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:36:30 by jbak              #+#    #+#             */
/*   Updated: 2022/11/25 14:36:30 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "cubd.h"
#include "parsing.h"

void	draw_square(t_cubd *cubd, int x, int y, int color)
{
	int	i;
	int	j;

	i = x;
	while (x <= i && i < x + 6)
	{
		j = y;
		while (y <= j && j < y + 6)
		{
			cubd->img.data[j * WIDTH + i] = color;
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_cubd *cubd)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			x = (int)(j * cubd->info->width / WIDTH);
			y = (int)(i * cubd->info->height / HEIGHT);
			if (cubd->info->lines[y][x] == '0')
				draw_square(cubd, 8 * x, 8 * y, 0x000000);
			else if (cubd->info->lines[y][x] == '1')
				draw_square(cubd, 8 * x, 8 * y, 0xFFFFFF);
			if (x == (int)cubd->player->pos_x && y == (int)cubd->player->pos_y)
				draw_square(cubd, 8 * x, 8 * y, 0xFF0000);
			j++;
		}
		i++;
	}
}

void	init_dist_wall(t_cast *cast, t_char *player, int mapx, int mapy)
{
	if (cast->raydir_x < 0)
	{
		cast->stepx = -1;
		cast->dist_wall_x = (player->pos_x - mapx) * cast->dist_unit_x;
	}
	else
	{
		cast->stepx = 1;
		cast->dist_wall_x = (mapx + 1.0 - player->pos_x) * cast->dist_unit_x;
	}
	if (cast->raydir_y < 0)
	{
		cast->stepy = -1;
		cast->dist_wall_y = (player->pos_y - mapy) * cast->dist_unit_y;
	}
	else
	{
		cast->stepy = 1;
		cast->dist_wall_y = (mapy + 1.0 - player->pos_y) * cast->dist_unit_y;
	}
}

void	init_before_cast(int x, t_cast *cast, t_char *player)
{
	cast->camera = (2 * x) / (double)WIDTH - 1;
	cast->raydir_x = player->dirx + player->pn_x * cast->camera;
	cast->raydir_y = player->diry + player->pn_y * cast->camera;
	cast->dist_unit_x = fabs(1 / cast->raydir_x);
	cast->dist_unit_y = fabs(1 / cast->raydir_y);
	cast->mapx = player->pos_x;
	cast->mapy = player->pos_y;
	init_dist_wall(cast, player, cast->mapx, cast->mapy);
}

void	apply_to_buf(int **wall, t_cast *cast, t_info *info, int x)
{
	double	step;
	double	tex_pos;
	int		tex_y;
	int		y;

	step = (1.0) * TEXHEIGHT / (cast->lineheight);
	tex_pos = (cast->drawstart - HEIGHT / (2 + info->updn) \
			+ cast->lineheight / (2 + info->updn)) * step;
	y = cast->drawstart;
	while (y < cast->drawend)
	{
		tex_y = (int)(tex_pos) & ((TEXHEIGHT) - 1);
		tex_pos += step;
		info->buf[y][x] = wall[cast->side][TEXHEIGHT * tex_y + cast->tex_x];
		y++;
	}
}
