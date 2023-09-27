/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:38 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:39 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	valid_check(const int argc, const char **argv)
{
	(void)argv;
	if (argc > 1)
	{
		write(2, "Error! you must run this shell without any argument\n", 52);
		exit(1);
	}
}

int	print_list(t_env *list, int flag)
{
	while (list != NULL)
	{
		if (ft_strncmp(list->env_name, "~", -1) == 0 \
			|| ft_strncmp(list->env_name, "?", -1) == 0)
		{
			list = list->next;
			continue ;
		}
		else if (flag == EXPORT)
			write(1, "declare -x ", 11);
		write(1, list->env_name, ft_strlen(list->env_name));
		if (list->env_value != NULL)
		{
			write(1, "=", 1);
			if (flag == EXPORT)
				write(1, "\"", 1);
			write(1, list->env_value, ft_strlen(list->env_value));
			if (flag == EXPORT)
				write(1, "\"", 1);
		}
		write(1, "\n", 1);
		list = list->next;
	}
	return (0);
}

void	init_question_mark(t_env *envs)
{
	char		**split;

	split = malloc(sizeof(char *) * 3);
	split[0] = ft_strdup("?");
	split[1] = ft_itoa(0);
	split[2] = NULL;
	push_env(envs, new_env(split));
	make_free(&split);
}

void	read_it_normally(t_src *src, t_env *envs, char *str)
{
	char		**split;

	split = malloc(sizeof(char *) * 3);
	src->buffer = str;
	src->bufsize = ft_strlen(str);
	src->cur_pos = INIT_SRC_POS;
	add_history(str);
	if (ft_strncmp(str, "exit", -1) == 0)
		exit(0);
	split[0] = ft_strdup("?");
	split[1] = ft_itoa(parse_and_execute(src, envs));
	split[2] = NULL;
	push_env(envs, new_env(split));
	make_free(&split);
	if (str)
		free(str);
}

int	main(const int argc, const char **argv, const char **envp)
{
	char	*str;
	t_env	*envs;
	t_src	src;

	valid_check(argc, argv);
	envs = envp_to_list(envp);
	set_signal(CUSTOM);
	init_question_mark(envs);
	while (1)
	{
		str = readline("minishell > ");
		if (!str)
			exit(write(1, "exit\n", 5) & 0);
		if (str)
			read_it_normally(&src, envs, str);
		else
			break ;
	}
	return (0);
}
