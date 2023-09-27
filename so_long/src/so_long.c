/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:51:41 by jbak              #+#    #+#             */
/*   Updated: 2022/08/12 20:16:52 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "so_long.h"

void	errexit(char *str, int flag, t_solong *so_long)
{
	if (flag == PERR)
		perror(str);
	if (flag == OTHER)
		write(2, str, ft_strlen(str));
	exit(free_it(so_long) | EXIT_FAILURE);
}

void	normalexit(char *str, t_solong *so_long)
{
	write(1, str, ft_strlen(str));
	exit(free_it(so_long) & EXIT_SUCCESS);
}

static int	red_cross(t_solong *so_long)
{
	exit(free_it(so_long) & EXIT_SUCCESS);
}

int	main(int argc, char **file)
{
	t_solong	so_long;

	if (argc != 2)
		errexit("usage : ./so_long [filename.ber]\n", OTHER, NULL);
	ft_memset(&so_long, 0, sizeof(t_solong));
	so_long.map.keycnt = valid_check(&so_long, file[1]);
	init_it(&so_long, file[1]);
	so_long.player.dir = RIGHT;
	mlx_hook(so_long.mlx.win, X_EVENT_PRESS_KEY, 0, key_pressed, &so_long);
	mlx_hook(so_long.mlx.win, X_EVENT_RED_CROSS, 0, red_cross, &so_long);
	spreadmovecnt(&so_long);
	mlx_loop(so_long.mlx.mlx);
	return (0);
}
