/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:36:23 by jbak              #+#    #+#             */
/*   Updated: 2022/11/25 14:36:24 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_info
{
	char	*direc[4];
	char	**lines;
	int		fnc[2];
	int		width;
	int		height;
	int		**buf;
	double	updn;
}	t_info;

typedef struct s_char
{
	double	pos_x;
	double	pos_y;
	char	direc;
	double	dirx;
	double	diry;
	double	pn_x;
	double	pn_y;
	double	mv_spd;
	double	rot_spd;
}	t_char;

typedef struct s_temp
{
	int		state;
	int		idx;
	int		check;
	char	*gnl;
}	t_temp;

# define R 0
# define G 1
# define B 2

//parsing.c
t_info	*parse(const char *filename);

//valid_check.c
int		valid_check(t_info *info, t_char *player);
int		freeinfo(t_info *info);

//valid_check_utils.c
int		get_color(char *nbr_line, int *arr);
int		check_open_wall(char **lines, int y, int x);
int		check_right_border(char **lines, int height);

#endif
