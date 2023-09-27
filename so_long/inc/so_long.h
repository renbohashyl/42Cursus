/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:45:32 by jbak              #+#    #+#             */
/*   Updated: 2022/08/12 20:16:54 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "defs.h"

//init.c
void	init_it(t_solong *sl, char *filename);
void	*open_xpm(t_mlx *mlx, char *path, int size1, int size2);
void	put_in(t_solong *sl, void *img, int x, int y);

//valid_check.c
int		valid_check(t_solong *sl, char *path);

//so_long.c
void	errexit(char *str, int flag, t_solong *so_long);
void	normalexit(char *str, t_solong *so_long);

//freeit.c
int		free_it(t_solong *so_long);

//events.c
void	spreadmovecnt(t_solong *so_long);
int		key_pressed(int input, t_solong *so_long);

//getimgs.c
void	get_player_img(t_solong *sl);
void	get_font_img(t_solong *sl);

#endif
