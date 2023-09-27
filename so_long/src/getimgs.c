/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getimgs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 04:20:03 by jbak              #+#    #+#             */
/*   Updated: 2022/08/12 18:40:55 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"

void	get_player_img(t_solong *sl)
{
	sl->player.img[0][0] = open_xpm(&sl->mlx, "imgs/pl/up0.xpm", IMGS, IMGS);
	sl->player.img[0][1] = open_xpm(&sl->mlx, "imgs/pl/up1.xpm", IMGS, IMGS);
	sl->player.img[0][2] = open_xpm(&sl->mlx, "imgs/pl/up2.xpm", IMGS, IMGS);
	sl->player.img[0][3] = open_xpm(&sl->mlx, "imgs/pl/up3.xpm", IMGS, IMGS);
	sl->player.img[1][0] = open_xpm(&sl->mlx, "imgs/pl/left0.xpm", IMGS, IMGS);
	sl->player.img[1][1] = open_xpm(&sl->mlx, "imgs/pl/left1.xpm", IMGS, IMGS);
	sl->player.img[1][2] = open_xpm(&sl->mlx, "imgs/pl/left2.xpm", IMGS, IMGS);
	sl->player.img[1][3] = open_xpm(&sl->mlx, "imgs/pl/left3.xpm", IMGS, IMGS);
	sl->player.img[2][0] = open_xpm(&sl->mlx, "imgs/pl/down0.xpm", IMGS, IMGS);
	sl->player.img[2][1] = open_xpm(&sl->mlx, "imgs/pl/down1.xpm", IMGS, IMGS);
	sl->player.img[2][2] = open_xpm(&sl->mlx, "imgs/pl/down2.xpm", IMGS, IMGS);
	sl->player.img[2][3] = open_xpm(&sl->mlx, "imgs/pl/down3.xpm", IMGS, IMGS);
	sl->player.img[3][0] = open_xpm(&sl->mlx, "imgs/pl/right0.xpm", IMGS, IMGS);
	sl->player.img[3][1] = open_xpm(&sl->mlx, "imgs/pl/right1.xpm", IMGS, IMGS);
	sl->player.img[3][2] = open_xpm(&sl->mlx, "imgs/pl/right2.xpm", IMGS, IMGS);
	sl->player.img[3][3] = open_xpm(&sl->mlx, "imgs/pl/right3.xpm", IMGS, IMGS);
}

void	get_font_img(t_solong *sl)
{
	sl->map.fonts[0] = open_xpm(&sl->mlx, "imgs/fonts/0.xpm", 8, 15);
	sl->map.fonts[1] = open_xpm(&sl->mlx, "imgs/fonts/1.xpm", 8, 15);
	sl->map.fonts[2] = open_xpm(&sl->mlx, "imgs/fonts/2.xpm", 8, 15);
	sl->map.fonts[3] = open_xpm(&sl->mlx, "imgs/fonts/3.xpm", 8, 15);
	sl->map.fonts[4] = open_xpm(&sl->mlx, "imgs/fonts/4.xpm", 8, 15);
	sl->map.fonts[5] = open_xpm(&sl->mlx, "imgs/fonts/5.xpm", 8, 15);
	sl->map.fonts[6] = open_xpm(&sl->mlx, "imgs/fonts/6.xpm", 8, 15);
	sl->map.fonts[7] = open_xpm(&sl->mlx, "imgs/fonts/7.xpm", 8, 15);
	sl->map.fonts[8] = open_xpm(&sl->mlx, "imgs/fonts/8.xpm", 8, 15);
	sl->map.fonts[9] = open_xpm(&sl->mlx, "imgs/fonts/9.xpm", 8, 15);
}
