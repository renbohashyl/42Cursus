/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_check_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:36:31 by jbak              #+#    #+#             */
/*   Updated: 2022/11/25 14:36:36 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

int	count_comma(char *nbr_line, int c)
{
	int	cnt;

	cnt = 0;
	while (*nbr_line != '\0')
		if (*(nbr_line++) == c)
			cnt++;
	return (cnt);
}

int	get_color(char *nbr_line, int *arr)
{
	int		rgb[3];
	int		idx;
	char	**temp;

	idx = -1;
	if (count_comma(nbr_line + 2, ',') != 2)
		return (-1);
	temp = ft_split(nbr_line + 2, ',');
	if (!temp[R] || !temp[G] || !temp[B] || !nbr_line || !(*nbr_line))
		return (-1);
	rgb[R] = ft_atoi(temp[R]);
	rgb[G] = ft_atoi(temp[G]);
	rgb[B] = ft_atoi(temp[B]);
	make_free(&temp);
	if (rgb[R] < 0 || rgb[R] > 255 || rgb[G] < 0 || rgb[G] > 255 || \
		rgb[B] < 0 || rgb[B] > 255)
		return (-1);
	if (arr == NULL)
		return (0);
	else
		while (++idx < 2)
			*arr += rgb[idx] << 16 / (1 + idx);
	*arr += rgb[2];
	return (0);
}

int	check_open_wall(char **lines, int y, int x)
{
	if (y < 0 || x < 0 || !lines[y] || (lines[y] && !lines[y][x]))
		return (1);
	else if (lines[y][x] == '1' || lines[y][x] == 'x')
		return (0);
	lines[y][x] = '1';
	return (check_open_wall(lines, y - 1, x)
		+ check_open_wall(lines, y + 1, x)
		+ check_open_wall(lines, y, x - 1)
		+ check_open_wall(lines, y, x + 1));
}

int	check_right_border(char **lines, int height)
{
	int	idx;
	int	jdx;

	idx = 0;
	jdx = ft_strlen(lines[0]);
	while (jdx > 0 && lines[0][jdx] != '1')
		jdx--;
	while (idx < height)
	{
		if (lines[idx + 1][jdx] == '1')
			idx++;
		else if (lines[idx][jdx + 1] == '1')
			jdx++;
		else if (lines[idx][jdx - 1] == '1')
			while (lines[idx][jdx - 1] == '1')
				jdx--;
		else if ((idx != height || jdx != 0))
			return (-1);
		idx += idx == 0;
	}
	return (0);
}
