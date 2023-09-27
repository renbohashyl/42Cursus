/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:36:27 by jbak              #+#    #+#             */
/*   Updated: 2022/11/25 14:36:27 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubd.h"
#include "raycast.h"
#include "parsing.h"

int	move_left_right_left(t_cubd *cubd, int input)
{
	t_char	*pl;

	pl = cubd->player;
	if (input == KEY_A)
	{
		if (cubd->info->lines [(int)(pl->pos_y)] \
			[(int)(pl->pos_x + (-pl->pn_x * pl->mv_spd))] == '0')
			pl->pos_x += -pl->pn_x * pl->mv_spd;
		if (cubd->info->lines [(int)(pl->pos_y + (-pl->pn_y * pl->mv_spd))] \
			[(int)(pl->pos_x)] == '0')
			pl->pos_y += -pl->pn_y * pl->mv_spd;
	}
	if (input == KEY_D)
	{
		if (cubd->info->lines [(int)(pl->pos_y)] \
			[(int)(pl->pos_x + (pl->pn_x * pl->mv_spd))] == '0')
			pl->pos_x += pl->pn_x * pl->mv_spd;
		if (cubd->info->lines [(int)(pl->pos_y + (pl->pn_y * pl->mv_spd))] \
			[(int)(pl->pos_x)] == '0')
			pl->pos_y += pl->pn_y * pl->mv_spd;
	}
	return (0);
}

int	move_forward_backward(t_cubd *cubd, int input)
{
	t_char	*pl;

	pl = cubd->player;
	if (input == KEY_W)
	{
		if (cubd->info->lines [(int)(pl->pos_y)] \
			[(int)(pl->pos_x + (pl->dirx * pl->mv_spd))] == '0')
			pl->pos_x += pl->dirx * pl->mv_spd;
		if (cubd->info->lines [(int)(pl->pos_y + (pl->diry * pl->mv_spd))] \
			[(int)(pl->pos_x)] == '0')
			pl->pos_y += pl->diry * pl->mv_spd;
	}
	if (input == KEY_S)
	{
		if (cubd->info->lines [(int)(pl->pos_y)] \
			[(int)(pl->pos_x - pl->dirx * pl->mv_spd)] == '0')
			pl->pos_x -= pl->dirx * pl->mv_spd;
		if (cubd->info->lines [(int)(pl->pos_y - pl->diry * pl->mv_spd)] \
			[(int)(pl->pos_x)] == '0')
			pl->pos_y -= pl->diry * pl->mv_spd;
	}
	return (0);
}

int	rotate(t_cubd *cubd, int i)
{
	double	olddirx;
	double	oldpnx;
	t_char	*pl;

	pl = cubd->player;
	olddirx = pl->dirx;
	oldpnx = pl->pn_x;
	if (i == 124)
	{
		pl->dirx = pl->dirx * cos(-pl->rot_spd) - pl->diry * sin(-pl->rot_spd);
		pl->diry = olddirx * sin(-pl->rot_spd) + pl->diry * cos(-pl->rot_spd);
		pl->pn_x = pl->pn_x * cos(-pl->rot_spd) - pl->pn_y * sin(-pl->rot_spd);
		pl->pn_y = oldpnx * sin(-pl->rot_spd) + pl->pn_y * cos(-pl->rot_spd);
	}
	if (i == 123)
	{
		pl->dirx = pl->dirx * cos(pl->rot_spd) - pl->diry * sin(pl->rot_spd);
		pl->diry = olddirx * sin(pl->rot_spd) + pl->diry * cos(pl->rot_spd);
		pl->pn_x = pl->pn_x * cos(pl->rot_spd) - pl->pn_y * sin(pl->rot_spd);
		pl->pn_y = oldpnx * sin(pl->rot_spd) + pl->pn_y * cos(pl->rot_spd);
	}
	return (0);
}

int	updown_funk(t_cubd *cubd, int i)
{
	if (i == ARR_U)
	{
		if (cubd->info->updn > -0.95)
			cubd->info->updn -= 0.05;
	}
	if (i == ARR_D)
	{
		if (cubd->info->updn < 0.95)
			cubd->info->updn += 0.05;
	}
	return (0);
}

int	key_press(int i, t_cubd *cubd)
{
	if (i == KEY_W || i == KEY_S)
		move_forward_backward(cubd, i);
	if (i == KEY_A || i == KEY_D)
		move_left_right_left(cubd, i);
	if (i == ARR_L || i == ARR_R)
		rotate(cubd, i);
	if (i == ARR_U || i == ARR_D)
		updown_funk(cubd, i);
	if (i == 53)
		exit(0);
	if (i == 3)
		cubd->mini_flag = cubd->mini_flag ^ 1;
	mlx_clear_window(cubd->mlx, cubd->win);
	main_loop(cubd);
	return (0);
}
