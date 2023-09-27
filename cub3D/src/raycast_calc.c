/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_calc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:36:28 by jbak              #+#    #+#             */
/*   Updated: 2022/11/25 14:36:29 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "cubd.h"
#include "parsing.h"
#include "libft.h"

int	decide_a_side(int evidence, int lawyer)
{
	if (evidence == -1)
		return (0 + lawyer);
	if (evidence == 1)
		return (1 + lawyer);
	return (0);
}

void	casting(t_cast *cast, t_info *info)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (cast->dist_wall_x < cast->dist_wall_y)
		{
			cast->dist_wall_x += cast->dist_unit_x;
			cast->mapx += cast->stepx;
			cast->side = decide_a_side(cast->stepx, 0);
		}
		else
		{
			cast->dist_wall_y += cast->dist_unit_y;
			cast->mapy += cast->stepy;
			cast->side = decide_a_side(cast->stepy, 2);
		}
		if (info->lines[cast->mapy][cast->mapx] == '1')
			hit = 1;
	}
}

int	calculate_for_texture(t_cast *cast, t_char *player, double updn)
{
	int	tex_x;

	cast->lineheight = (int)((HEIGHT) / cast->calib_dist);
	cast->drawstart = -(cast->lineheight) / (2) + HEIGHT / (2 + updn);
	cast->drawend = cast->lineheight / (2) + HEIGHT / (2 + updn);
	if (cast->drawstart < 0)
		cast->drawstart = 0;
	if (cast->drawend >= HEIGHT)
		cast->drawend = HEIGHT - 1;
	if (cast->side <= 1)
		cast->ray_hit = player->pos_y + cast->calib_dist * cast->raydir_y;
	else
		cast->ray_hit = player->pos_x + cast->calib_dist * cast->raydir_x;
	cast->ray_hit -= floor(cast->ray_hit);
	tex_x = (int)(cast->ray_hit * (double)TEXWIDTH);
	if (cast->side <= 1 && cast->raydir_x > 0)
		tex_x = TEXWIDTH - tex_x - 1;
	if (cast->side >= 2 && cast->raydir_y < 0)
		tex_x = TEXWIDTH - tex_x - 1;
	return (tex_x);
}

void	calc(int **wall, t_info *info, t_char *player)
{
	int		x;
	t_cast	cast;

	x = -1;
	ft_bzero(&cast, sizeof(t_cast));
	x = 0;
	while (x < WIDTH)
	{
		init_before_cast(x, &cast, player);
		casting(&cast, info);
		if (cast.side <= 1)
			cast.calib_dist = (cast.mapx - player->pos_x + \
								(1 - cast.stepx) / 2) / cast.raydir_x;
		else
			cast.calib_dist = (cast.mapy - player->pos_y + \
								(1 - cast.stepy) / 2) / cast.raydir_y;
		cast.tex_x = calculate_for_texture(&cast, player, info->updn);
		apply_to_buf(wall, &cast, info, x);
		x++;
	}
}
