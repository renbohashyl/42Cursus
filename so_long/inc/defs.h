/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 18:38:44 by jbak              #+#    #+#             */
/*   Updated: 2022/08/12 18:40:39 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

# define PERR 0
# define OTHER 1
# define IMGS 64
# define X_EVENT_PRESS_KEY 2
# define X_EVENT_RED_CROSS 17
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_UP 126
# define KEY_LEFT 123
# define KEY_DOWN 125
# define KEY_RIGHT 124
# define KEY_ESC 53
# define UP 0
# define LEFT 1
# define DOWN 2
# define RIGHT 3
# define ON 1
# define OFF 0

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
}	t_mlx;

typedef struct s_map
{
	void	*wall;
	void	*tile;
	void	*key;
	void	*exit;
	void	*fonts[10];
	void	*enemy;
	char	**lines;
	int		keycnt;
	int		wid;
	int		hei;
}	t_map;

typedef struct s_player
{
	void	*img[4][4];
	void	*closed;
	int		dir;
	int		keycnt;
	int		moved;
	int		x;
	int		y;
}	t_player;

typedef struct s_solong
{
	t_mlx		mlx;
	t_map		map;
	t_player	player;
	int			ene_x;
	int			ene_y;
	int			ene_chk;
	int			cflag;
}	t_solong;

#endif