/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:36:24 by jbak              #+#    #+#             */
/*   Updated: 2022/11/25 14:36:25 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include <math.h>
# include <stdlib.h>

typedef struct s_info	t_info;
typedef struct s_char	t_char;
typedef struct s_map	t_map;
typedef struct s_cubd	t_cubd;

typedef struct s_caster
{
	double	camera;
	double	raydir_x;
	double	raydir_y;
	double	dist_wall_x;
	double	dist_wall_y;
	double	dist_unit_x;
	double	dist_unit_y;
	double	calib_dist;
	double	ray_hit;
	int		lineheight;
	int		drawstart;
	int		drawend;
	int		mapx;
	int		mapy;
	int		tex_x;
	int		stepx;
	int		stepy;
	int		side;
}	t_cast;

# define TEXWIDTH 64
# define TEXHEIGHT 64

//dist_wall == sideDist
//dist_unit == deltaDist
//calib_dist == perpWallDist
//ray_hit == wallX;

void	init_dist_wall(t_cast *cast, t_char *player, int mapx, int mapy);
void	init_before_cast(int x, t_cast *cast, t_char *player);
void	apply_to_buf(int **wall, t_cast *cast, t_info *info, int x);
void	calc(int **wall, t_info *info, t_char *player);
void	draw_minimap(t_cubd *cubd);

#endif
