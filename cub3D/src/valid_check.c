/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:36:30 by jbak              #+#    #+#             */
/*   Updated: 2022/11/25 14:36:31 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubd.h"
#include "parsing.h"
#include "libft.h"

int	freeinfo(t_info *info)
{
	int	i;

	i = -1;
	if (!info)
		return (1);
	while (++i < 4)
		if (info->direc[i])
			free((info->direc[i]));
	i = -1;
	while (info->lines && info->lines[++i])
		free(info->lines[i]);
	if (info->lines)
		free(info->lines);
	free(info);
	return (0);
}

int	player_check(char **lines, t_char *player)
{
	int	y;
	int	x;
	int	errchk;

	y = -1;
	errchk = 0;
	while (lines[++y])
	{
		x = -1;
		while (lines[y][++x])
		{
			if (lines[y][x] == 'N' || lines[y][x] == 'E' || \
				lines[y][x] == 'S' || lines[y][x] == 'W')
			{
				player->direc = lines[y][x];
				player->pos_x = x + 1;
				player->pos_y = y + 1;
				lines[y][x] = '0';
				errchk++;
			}
		}
	}
	return (errchk);
}

int	wall_check(char **lines)
{
	int	y;
	int	x;
	int	errchk;

	errchk = 0;
	y = 0;
	while (lines[y])
	{
		x = 0;
		while (lines[y][x])
		{
			if (lines[y][x] != '1' && lines[y][x] != '0')
				errchk = check_open_wall(lines, y, x);
			if (errchk == 0)
				break ;
			x++;
		}
		y++;
	}
	return (0);
}

int	valid_check(t_info *info, t_char *player)
{
	if (wall_check(info->lines))
	{
		freeinfo(info);
		return (-2);
	}
	if (player_check(info->lines, player) != 1)
	{
		free(player);
		return (-1);
	}
	if (check_right_border(info->lines, (info->height - 1)))
		exit(errmsg("right border error", CUST));
	return (0);
}
