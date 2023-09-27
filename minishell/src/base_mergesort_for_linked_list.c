/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_mergesort_for_linked_list.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:23 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:23 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/_types/_null.h>
#include <unistd.h>

static int	__ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0 && *s1 && *s2)
	{
		if (*s1 != *s2)
			break ;
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	if (s1 && !s2)
		return (*(unsigned char *)s1);
	else if (!s1 && s2)
		return (*(unsigned char *)s2);
	else
		return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

static void	split_list(t_env *source, t_env **frontRef, t_env **backRef)
{
	t_env	*fast;
	t_env	*slow;

	if (source == NULL || source->next == NULL)
	{
		*frontRef = source;
		*backRef = NULL;
	}
	else
	{
		slow = source;
		fast = source->next;
		while (fast != NULL)
		{
			fast = fast->next;
			if (fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
		*frontRef = source;
		*backRef = slow->next;
		slow->next = NULL;
	}
}

static t_env	*sortedmerge(t_env *a, t_env *b)
{
	t_env	*result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (__ft_strncmp(a->env_name, b->env_name, -1) <= 0)
	{
		result = a;
		result->next = sortedmerge(a->next, b);
	}
	else
	{
		result = b;
		result->next = sortedmerge(a, b->next);
	}
	return (result);
}

void	mergesort_for_linked_list(t_env **head_ref)
{
	t_env	*head;
	t_env	*a;
	t_env	*b;

	head = *head_ref;
	if ((head == NULL) || (head->next == NULL))
		return ;
	split_list(head, &a, &b);
	mergesort_for_linked_list(&a);
	mergesort_for_linked_list(&b);
	*head_ref = sortedmerge(a, b);
}
