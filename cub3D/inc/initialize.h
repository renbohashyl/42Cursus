/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:36:21 by jbak              #+#    #+#             */
/*   Updated: 2022/11/25 14:36:22 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INITIALIZE_H
# define INITIALIZE_H

# include "mlx.h"
# include "libft.h"

typedef struct s_info	t_info;
typedef struct s_cubd	t_cubd;
typedef struct s_char	t_char;

typedef struct s_img
{
	void	*img;
	int		*data;
	int		len;
	int		bpp;
	int		endian;
	int		w;
	int		h;
}	t_img;

typedef enum e_wall_direction
{
	NO,
	SO,
	WE,
	EA
}	t_wall_dir;

# define IMG 64

void	player_initialize(t_char *player);
int		mlx_initialize(t_cubd *cubd, t_info *info);

#endif
