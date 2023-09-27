/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 00:39:58 by jbak              #+#    #+#             */
/*   Updated: 2022/08/15 10:53:21 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "so_long.h"

static void	free_imgs(t_solong *sl)
{
	int	idx;
	int	jdx;

	if (sl->map.wall)
		mlx_destroy_image(sl->mlx.mlx, sl->map.wall);
	if (sl->map.tile)
		mlx_destroy_image(sl->mlx.mlx, sl->map.tile);
	if (sl->map.key)
		mlx_destroy_image(sl->mlx.mlx, sl->map.key);
	if (sl->map.exit)
		mlx_destroy_image(sl->mlx.mlx, sl->map.exit);
	idx = -1;
	while (++idx < 4)
	{
		jdx = -1;
		while (++jdx < 2 && sl->player.img[idx][jdx])
			mlx_destroy_image(sl->mlx.mlx, sl->player.img[idx][jdx]);
	}
	if (sl->player.closed)
		mlx_destroy_image(sl->mlx.mlx, sl->player.closed);
	idx = -1;
	while (++idx < 10 && sl->map.fonts[idx])
		mlx_destroy_image(sl->mlx.mlx, sl->map.fonts[idx]);
}

int	free_it(t_solong *sl)
{
	int	idx;

	if (sl == NULL)
		exit (1);
	idx = 0;
	while (sl->map.lines && sl->map.lines[idx])
	{
		free(sl->map.lines[idx]);
		sl->map.lines[idx++] = NULL;
	}
	if (sl->map.lines)
	{
		free(sl->map.lines);
		sl->map.lines = NULL;
	}
	free_imgs(sl);
	if (sl->mlx.mlx && sl->mlx.win)
		mlx_destroy_window(sl->mlx.mlx, sl->mlx.win);
	return (1);
}
