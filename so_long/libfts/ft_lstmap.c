/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:38:28 by jbak              #+#    #+#             */
/*   Updated: 2021/12/06 01:39:57 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*freturn;

	freturn = (void *)0;
	while (lst)
	{
		temp = ft_lstnew((*f)(lst->content));
		if (temp == (void *)0)
		{
			ft_lstclear(&freturn, del);
			return ((void *)0);
		}
		ft_lstadd_back(&freturn, temp);
		lst = lst->next;
	}
	return (freturn);
}
