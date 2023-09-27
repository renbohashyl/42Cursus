/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:36:25 by jbak              #+#    #+#             */
/*   Updated: 2022/11/25 14:36:26 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubd.h"
#include "raycast.h"
#include "parsing.h"
#include "libft.h"

int	errmsg(const char *str, int flag)
{
	if (flag == PERR)
		perror(str);
	else if (flag == CUST)
	{
		write(STDERR_FILENO, "Error : ", 8);
		write(STDERR_FILENO, str, ft_strlen(str));
		write(STDERR_FILENO, "\n", 1);
	}
	return (1);
}

void	draw(t_cubd *cubd)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			cubd->img.data[y * WIDTH + x] = cubd->info->buf[y][x];
		y++;
	}
	if (cubd->mini_flag == 1)
		draw_minimap(cubd);
	mlx_put_image_to_window(cubd->mlx, cubd->win, cubd->img.img, 0, 0);
}

int	main_loop(t_cubd *cubd)
{
	int	x;
	int	y;

	fnc(cubd);
	calc(cubd->wall, cubd->info, cubd->player);
	draw(cubd);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			cubd->info->buf[y][x] = 0;
			x++;
		}
		y++;
	}
	return (0);
}

int	normal_exit(t_cubd *cubd)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		free(cubd->wall[i]);
		free(cubd->info->direc[i]);
	}
	i = -1;
	while (cubd->info->lines[++i])
		free(cubd->info->lines[i]);
	free(cubd->info->lines);
	i = -1;
	while (++i < HEIGHT)
		free(cubd->info->buf[i]);
	free(cubd->info->buf);
	free(cubd->info);
	free(cubd->player);
	mlx_destroy_image(cubd->mlx, cubd->img.img);
	mlx_destroy_window(cubd->mlx, cubd->win);
	exit(EXIT_SUCCESS);
}

int	main(const int ac, const char **av)
{
	t_cubd	cubd;
	int		x;

	ft_bzero(&cubd, sizeof(t_cubd));
	if (ac != 2)
		return (errmsg("you need to check argument number", CUST));
	cubd.info = parse(av[1]);
	if (cubd.info == NULL)
		return (EXIT_FAILURE);
	cubd.info->buf = malloc(sizeof(int *) * HEIGHT);
	x = -1;
	while (++x < HEIGHT)
		cubd.info->buf[x] = malloc(sizeof(int) * WIDTH);
	cubd.player = ft_calloc(sizeof(t_char), 1);
	if (valid_check(cubd.info, cubd.player))
		return (errmsg("Map file corrupted, misconfiguration", CUST));
	mlx_initialize(&cubd, cubd.info);
	player_initialize(cubd.player);
	mlx_loop_hook(cubd.mlx, &main_loop, &cubd);
	mlx_hook(cubd.win, 2, 0, &key_press, &cubd);
	mlx_hook(cubd.win, 17, 0, &normal_exit, &cubd);
	mlx_loop(cubd.mlx);
	return (0);
}
