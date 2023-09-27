/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:36:28 by jbak              #+#    #+#             */
/*   Updated: 2022/11/25 14:36:28 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubd.h"
#include "parsing.h"
#include "libft.h"

void	*my_realloc(void *buf, size_t len)
{
	char	*new_buf;

	if (len == 0 && buf)
	{
		free(buf);
		return (NULL);
	}
	if (!buf)
		return (ft_calloc(sizeof(len), 1));
	new_buf = ft_calloc(1, len);
	if (!new_buf)
		return (buf);
	new_buf = ft_memcpy(new_buf, buf, ft_strlen(buf));
	free(buf);
	return (new_buf);
}

int	check_direction_and_color(char *gnl)
{
	int	ret;

	ret = 0;
	if (gnl && (*gnl == '\n' || *gnl == '\0'))
		return (-1);
	else if (!ft_strncmp(gnl, "NO ", 3) && !ft_strrncmp(gnl, ".xpm", 4))
		ret = 1;
	else if (!ft_strncmp(gnl, "SO ", 3) && !ft_strrncmp(gnl, ".xpm", 4))
		ret = 2;
	else if (!ft_strncmp(gnl, "WE ", 3) && !ft_strrncmp(gnl, ".xpm", 4))
		ret = 3;
	else if (!ft_strncmp(gnl, "EA ", 3) && !ft_strrncmp(gnl, ".xpm", 4))
		ret = 4;
	else if (!ft_strncmp(gnl, "F ", 2) && !get_color(gnl, NULL))
		ret = 5;
	else if (!ft_strncmp(gnl, "C ", 2) && !get_color(gnl, NULL))
		ret = 6;
	return (ret);
}

int	get_height(int fd, t_info *info)
{
	t_temp	temp;

	ft_bzero(&temp, sizeof(t_temp));
	temp.gnl = get_next_line(fd);
	while (temp.gnl && !(temp.state))
	{
		temp.check = check_direction_and_color(temp.gnl);
		if (temp.check > 0)
			(temp.idx)++;
		if (!(temp.check) && (temp.idx) != 6)
			temp.state = -1;
		else if (!(temp.check) && (temp.idx) == 6)
		{
			(info->height)++;
			if ((int)ft_strlen(temp.gnl) > info->width)
				info->width = ft_strlen(temp.gnl);
		}
		free(temp.gnl);
		temp.gnl = get_next_line(fd);
	}
	close (fd);
	if (temp.gnl)
		free(temp.gnl);
	return (temp.state);
}

void	refine_gnl_to_info(int fd, t_info *info)
{
	char	*gnl;
	int		check;
	int		idx;

	idx = 0;
	gnl = get_next_line(fd);
	while (gnl)
	{
		check = check_direction_and_color(gnl);
		if (*gnl == '\n' || *gnl == '\0')
			free(gnl);
		else if (check > 0 && check < 5)
			info->direc[check - 1] = ft_strdup(gnl + 3);
		else if (check == 5 || check == 6)
			get_color(gnl, &(info->fnc[check - 5]));
		else
			info->lines[idx++] = my_realloc(gnl, info->width);
		if (check > 0 && check <= 6)
			free(gnl);
		gnl = get_next_line(fd);
	}
	info->lines[idx] = NULL;
}

t_info	*parse(const char *filename)
{
	int		fd;
	t_info	*info;

	fd = open(filename, O_RDONLY);
	if (fd == -1 || ft_strrncmp(filename, ".cub", 4))
		exit(errmsg("File open error", CUST));
	info = ft_calloc(sizeof(t_info), 1);
	if (get_height(fd, info))
		exit(errmsg("Map file corrupted", CUST));
	fd = open(filename, O_RDONLY);
	info->lines = ft_calloc(sizeof(char *), info->height + 1);
	refine_gnl_to_info(fd, info);
	close(fd);
	return (info);
}
