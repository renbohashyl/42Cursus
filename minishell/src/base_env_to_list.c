/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_env_to_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:19 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:20 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_env	*delete_env(t_env **node)
{
	t_env	*temp;

	temp = (*node)->next;
	free((*node)->env_name);
	(*node)->env_name = NULL;
	free((*node)->env_value);
	(*node)->env_value = NULL;
	free(*node);
	*node = NULL;
	return (temp);
}

t_env	*new_env(char **split)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	node->env_name = ft_strdup(split[0]);
	node->env_value = ft_strdup(split[1]);
	node->next = NULL;
	return (node);
}

void	push_env(t_env *list, t_env *new_env_node)
{
	while (list)
	{
		if (ft_strncmp(list->env_name, new_env_node->env_name, -1) == 0)
		{
			if (list->env_value && new_env_node->env_value)
			{
				free(list->env_value);
				list->env_value = ft_strdup(new_env_node->env_value);
			}
			delete_env(&new_env_node);
			return ;
		}
		else if (list->next == NULL)
		{
			list->next = new_env_node;
			return ;
		}
		list = list->next;
	}
}

void	tilde_do(t_env *env, int *cnt)
{
	(*cnt)--;
	free(env->next->env_name);
	env->next->env_name = ft_strdup("~");
}

t_env	*envp_to_list(const char **envp)
{
	t_env	*env;
	t_env	*head;
	char	**split;
	int		cnt;
	int		temp;

	cnt = 0;
	temp = 0;
	split = ft_split(envp[cnt], '=');
	env = new_env(split);
	make_free(&split);
	head = env;
	while (envp[++cnt])
	{
		split = ft_split(envp[cnt], '=');
		env->next = new_env(split);
		make_free(&split);
		if (ft_strncmp(envp[cnt], "HOME=", 5) == 0 && temp++ == 0)
			tilde_do(env, &cnt);
		env = env->next;
	}
	mergesort_for_linked_list(&head);
	return (head);
}
