/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbak <jbak@jbak@student.42seoul>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:22:51 by jbak              #+#    #+#             */
/*   Updated: 2022/10/14 19:22:52 by jbak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sig.h"

static void	del_sigchar(void)
{
	printf("\033[2K");
	rl_on_new_line();
	rl_redisplay();
}

void	sig_handler(int signum)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = waitpid(-1, &status, WNOHANG);
	if (signum == SIGINT)
	{
		if (pid == -1)
		{
			del_sigchar();
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
			printf("\n");
	}
	if (signum == SIGQUIT)
	{
		if (pid == -1)
			del_sigchar();
		else
			printf("Quit :3\n");
	}
}

void	pipe_sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	set_signal(int state)
{
	if (state == CUSTOM)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
	}
	if (state == PIPE)
	{
		signal(SIGINT, pipe_sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	if (state == HEREDOC)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
}
