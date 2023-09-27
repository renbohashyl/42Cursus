/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:45:14 by jbak              #+#    #+#             */
/*   Updated: 2022/08/12 20:07:56 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "so_long.h"

static void	get_info(t_solong *sl, char *path)
{
	int		fd;
	char	*temp;

	temp = NULL;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		errexit(path, PERR, sl);
	temp = get_next_line(fd);
	while (temp)
	{
		sl->map.wid = (int)ft_strlen(temp);
		free(temp);
		temp = get_next_line(fd);
		if (temp && sl->map.wid != (int)ft_strlen(temp))
			errexit("This is not rectangle. try something else\n", OTHER, sl);
		(sl->map.hei)++;
	}
	close(fd);
}

static int	element_count(char **lines, char del)
{
	int	idx;
	int	jdx;
	int	cnt;

	cnt = 0;
	idx = -1;
	while (lines[++idx])
	{
		jdx = -1;
		while (lines[idx][++jdx])
			if (lines[idx][jdx] == del)
				cnt++;
	}
	return (cnt);
}

static int	check_elements(t_solong *sl)
{
	int	cflag;

	cflag = element_count(sl->map.lines, 'C');
	if (!cflag)
		errexit("Error! there is no collectible(s)!\n", OTHER, sl);
	if (!element_count(sl->map.lines, 'E'))
		errexit("Error! there is no exit!\n", OTHER, sl);
	if (element_count(sl->map.lines, 'P') != 1)
		errexit("Error! invalid starting position\n", OTHER, sl);
	return (cflag);
}

static void	check_map(t_solong *sl, char *path)
{
	int	i;
	int	j;
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		errexit(path, PERR, sl);
	i = -1;
	sl->map.lines = malloc(sizeof(char *) * (sl->map.hei + 1));
	ft_memset(sl->map.lines, 0, ((sizeof(char *)) * (sl->map.hei + 1)));
	while (++i < sl->map.hei)
	{
		sl->map.lines[i] = get_next_line(fd);
		j = -1;
		if (i == 0 || i == sl->map.hei - 1)
			while (sl->map.lines[i][++j])
				if (sl->map.lines[i][j] != '1')
					errexit("Error. it's not surrounded by wall\n", OTHER, sl);
		if (sl->map.lines[i] && (sl->map.lines[i][0] != '1' || \
				sl->map.lines[i][sl->map.wid - 1] != '1'))
			errexit("Error. it's not surrounded by wall\n", OTHER, sl);
	}
	close(fd);
}

int	valid_check(t_solong *sl, char *path)
{
	if (!ft_strrncmp(path, ".ber", 4))
		errexit("invaild file format. try something else\n", OTHER, sl);
	get_info(sl, path);
	check_map(sl, path);
	return (check_elements(sl));
}
