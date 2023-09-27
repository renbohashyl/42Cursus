/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:29 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:29 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

static size_t	ft_strlen(const char *str)
{
	size_t	cnt;

	cnt = 0;
	while (str && str[cnt])
		cnt++;
	return (cnt);
}

int	pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (EXIT_FAILURE);
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	free(pwd);
	pwd = NULL;
	return (EXIT_SUCCESS);
}
