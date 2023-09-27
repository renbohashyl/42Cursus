/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 19:52:06 by jbak              #+#    #+#             */
/*   Updated: 2021/11/26 21:13:05 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		cnt;
	t_list	*temp;

	if (!(lst))
		return (0);
	cnt = 0;
	temp = lst;
	while (temp->next)
	{
		cnt++;
		temp = temp->next;
	}
	if (temp->next == (void *)0)
		cnt++;
	return (cnt);
}
