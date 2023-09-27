/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:33:58 by jbak              #+#    #+#             */
/*   Updated: 2022/06/06 20:46:37 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static int	prt_what(int option)
{
	if (option == SUC)
		write(STDOUT, "OK\n", 3);
	if (option == FAIL)
		write(STDOUT, "KO\n", 3);
	if (option == ERROR)
		write(STDERR, "Error\n", 6);
	return (0);
}

static int	check_a(t_node *a_top, t_node *b_top)
{	
	while (a_top != NULL && (a_top)->next != NULL && b_top == NULL)
	{
		if (((a_top)->value) > (((a_top)->next)->value))
			return (FAIL);
		a_top = (a_top)->next;
	}
	if ((a_top == NULL || (a_top)->next == NULL) && b_top == NULL)
		return (SUC);
	return (FAIL);
}

int	main(int cnt, char **array)
{
	t_stack	a;
	t_stack	b;
	char	*cmd;

	if (cnt < 2)
		return (0);
	a.top = NULL;
	b.top = NULL;
	parse_digits(cnt, array, &a.top);
	cmd = get_next_line(STDIN);
	while (cmd != NULL)
	{
		doit(cmd, &a.top, &b.top);
		free(cmd);
		cmd = get_next_line(STDIN_FILENO);
	}
	return (prt_what(check_a(a.top, b.top)));
}
