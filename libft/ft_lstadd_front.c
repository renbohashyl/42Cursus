/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 19:33:25 by jbak              #+#    #+#             */
/*   Updated: 2021/11/26 19:49:25 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if ((new == (void *)0) || (lst == (void *)0))
		return ;
	if (*lst)
		new->next = *lst;
	else
		new->next = (void *)0;
	*lst = new;
}
