/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:36:26 by jbak              #+#    #+#             */
/*   Updated: 2022/11/25 14:36:27 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubd.h"
#include "initialize.h"
#include "parsing.h"

void	player_initialize(t_char *player)
{
	player->pos_x -= 0.5;
	player->pos_y -= 0.5;
	player->mv_spd = 0.1;
	player->rot_spd = 0.05;
	if (player->direc == 'N')
	{
		player->dirx = -1;
		player->pn_y = 0.66;
	}
	else if (player->direc == 'S')
	{
		player->dirx = 1;
		player->pn_y = -0.66;
	}
	else if (player->direc == 'E')
	{
		player->diry = 1;
		player->pn_x = 0.66;
	}
	else if (player->direc == 'W')
	{
		player->diry = -1;
		player->pn_x = -0.66;
	}
}

void	fnc(t_cubd *cubd)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	color = cubd->info->fnc[0];
	while (y < HEIGHT / (2 + cubd->info->updn))
	{
		x = -1;
		while (++x < WIDTH)
			cubd->info->buf[y][x] = color;
		y++;
	}
	color = cubd->info->fnc[1];
	while (y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			cubd->info->buf[y][x] = color;
		y++;
	}
}

void	open_xpm(t_cubd *cubd, int *wall, char *path, t_img *img)
{
	int	y;
	int	x;

	img->img = mlx_xpm_file_to_image(cubd->mlx, path, &(img->w), &(img->h));
	if (!(img->img))
		return ;
	img->data = (int *)mlx_get_data_addr \
						(img->img, &(img->bpp), &(img->len), &(img->endian));
	if (!(img->data))
		return ;
	y = 0;
	while (y < img->h)
	{
		x = -1;
		while (++x < img->w)
			wall[img->w * y + x] = img->data[img->w * y + x];
		y++;
	}
	mlx_destroy_image(cubd->mlx, img->img);
}

void	load_image(t_cubd *cubd, t_info *info, t_img *img)
{
	open_xpm(cubd, cubd->wall[NO], info->direc[NO], img);
	open_xpm(cubd, cubd->wall[SO], info->direc[SO], img);
	open_xpm(cubd, cubd->wall[WE], info->direc[WE], img);
	open_xpm(cubd, cubd->wall[EA], info->direc[EA], img);
}

int	mlx_initialize(t_cubd *cubd, t_info *info)
{
	t_img	img;
	int		i;

	i = 0;
	cubd->mlx = mlx_init();
	while (i < 4)
	{
		cubd->wall[i] = ft_calloc(sizeof(int), IMG * IMG);
		if (!(cubd->wall[i]))
			exit(errmsg("malloc failed", CUST));
		i++;
	}
	load_image(cubd, info, &img);
	if (!(*(cubd->wall[NO])) || !(*(cubd->wall[SO])) || \
		!(*(cubd->wall[WE])) || !(*(cubd->wall[EA])))
		exit(errmsg("wall file open failed", CUST));
	cubd->win = mlx_new_window(cubd->mlx, WIDTH, HEIGHT, "jjbb's cub3d");
	cubd->img.img = mlx_new_image(cubd->mlx, WIDTH, HEIGHT);
	cubd->img.data = (int *)mlx_get_data_addr \
			(cubd->img.img, &cubd->img.bpp, &cubd->img.len, &cubd->img.endian);
	if (!(cubd->mlx) || !(cubd->win) || !(cubd->img.img))
		exit(errmsg("something went wrong, mlx init failed", CUST));
	return (0);
}
