/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 00:52:13 by jbak              #+#    #+#             */
/*   Updated: 2022/08/15 11:08:40 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "so_long.h"

static void	check_position(t_solong *sl)
{
	if (sl->map.lines[sl->player.y][sl->player.x] == 'E')
	{
		if (sl->player.keycnt == sl->map.keycnt)
			normalexit("SUCCESS!\n", sl);
	}
	else if (sl->map.lines[sl->player.y][sl->player.x] == 'C')
	{
		(sl->player.keycnt)++;
		sl->map.lines[sl->player.y][sl->player.x] = '0';
		put_in(sl->mlx.mlx, sl->map.tile, \
				sl->player.x, sl->player.y);
		put_in(sl->mlx.mlx, \
			sl->player.img[sl->player.dir][sl->player.moved % 4], \
			sl->player.x, sl->player.y);
	}
	else if (sl->map.lines[sl->player.y][sl->player.x] == 'X')
		normalexit("you died\n", sl);
}

static void	moving(t_solong *sl, int dir, int new_x, int new_y)
{
	if (sl->map.lines[new_y][new_x] != '1' && \
		sl->map.lines[new_y][new_x] != 'E')
	{
		sl->player.x = new_x;
		sl->player.y = new_y;
	}
	else if (sl->map.lines[new_y][new_x] == 'E')
	{
		if (sl->player.keycnt == sl->map.keycnt)
		{
			sl->player.x = new_x;
			sl->player.y = new_y;
		}
	}
	check_position(sl);
	sl->player.dir = dir;
	put_in(sl->mlx.mlx, sl->player.img[dir][sl->player.moved % 4], \
	sl->player.x, sl->player.y);
}

void	spreadmovecnt(t_solong *sl)
{
	int			idx;

	idx = -1;
	while (++idx < sl->map.wid)
		put_in(sl->mlx.mlx, sl->map.wall, idx, 0);
	mlx_put_image_to_window(sl->mlx.mlx, sl->mlx.win, \
	sl->map.fonts[sl->player.moved / 100], 24, 17);
	mlx_put_image_to_window(sl->mlx.mlx, sl->mlx.win, \
	sl->map.fonts[(sl->player.moved / 10) % 10], 32, 17);
	mlx_put_image_to_window(sl->mlx.mlx, sl->mlx.win, \
	sl->map.fonts[sl->player.moved % 10], 40, 17);
}

static void	enemy_chasing(t_solong *sl)
{
	put_in(sl->mlx.mlx, sl->map.tile, sl->ene_x, sl->ene_y);
	if (sl->cflag == ON)
	{
		sl->map.lines[sl->ene_y][sl->ene_x] = 'C';
		put_in(sl->mlx.mlx, sl->map.key, sl->ene_x, sl->ene_y);
		sl->cflag = OFF;
	}
	else
		sl->map.lines[sl->ene_y][sl->ene_x] = '0';
	if (sl->player.moved % 2 == 0)
	{
		if (sl->ene_x < sl->player.x)
			sl->ene_x++;
		else if (sl->ene_x > sl->player.x)
			sl->ene_x--;
		else if (sl->ene_y < sl->player.y)
			sl->ene_y++;
		else if (sl->ene_y > sl->player.y)
			sl->ene_y--;
	}
	put_in(sl->mlx.mlx, sl->map.enemy, sl->ene_x, sl->ene_y);
	if (sl->map.lines[sl->ene_y][sl->ene_x] == 'C')
		sl->cflag = ON;
	sl->map.lines[sl->ene_y][sl->ene_x] = 'X';
}

int	key_pressed(int input, t_solong *sl)
{
	if (input == KEY_ESC)
		exit(free_it(sl));
	if (input == KEY_W || input == KEY_UP || input == KEY_A || \
		input == KEY_LEFT || input == KEY_S || input == KEY_DOWN || \
		input == KEY_D || input == KEY_RIGHT)
	{
		(sl->player.moved)++;
		put_in(sl->mlx.mlx, sl->map.tile, sl->player.x, sl->player.y);
		sl->map.lines[sl->player.y][sl->player.x] = '0';
		if (input == KEY_W || input == KEY_UP)
			moving(sl, 0, sl->player.x, sl->player.y - 1);
		else if (input == KEY_A || input == KEY_LEFT)
			moving(sl, 1, sl->player.x - 1, sl->player.y);
		else if (input == KEY_S || input == KEY_DOWN)
			moving(sl, 2, sl->player.x, sl->player.y + 1);
		else if (input == KEY_D || input == KEY_RIGHT)
			moving(sl, 3, sl->player.x + 1, sl->player.y);
		sl->map.lines[sl->player.y][sl->player.x] = 'P';
		if (sl->ene_chk == ON)
			enemy_chasing(sl);
		check_position(sl);
		spreadmovecnt(sl);
	}
	return (0);
}
