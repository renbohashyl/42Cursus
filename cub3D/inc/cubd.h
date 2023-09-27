/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubd.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:36:09 by jbak              #+#    #+#             */
/*   Updated: 2022/11/25 14:36:21 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBD_H
# define CUBD_H

# include <unistd.h>
# include <stdlib.h>

# include "initialize.h"

typedef struct s_info	t_info;
typedef struct s_char	t_char;

typedef struct s_cubd
{
	t_info	*info;
	t_char	*player;
	t_img	img;
	void	*mlx;
	void	*win;
	int		mini_flag;
	int		*wall[4];
}	t_cubd;

int		errmsg(const char *str, int flag);
int		main_loop(t_cubd *cubd);
int		key_press(int key, t_cubd *cubd);
void	fnc(t_cubd *cubd);

# define WIDTH 640
# define HEIGHT 480
# define PERR 0
# define CUST 1
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define ARR_L 123
# define ARR_R 124
# define ARR_D 125
# define ARR_U 126

#endif
