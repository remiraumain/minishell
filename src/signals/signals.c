/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:12:25 by rraumain          #+#    #+#             */
/*   Updated: 2025/04/15 15:26:52 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint_no_redisplay(int sig)
{
	g_sig = sig;
	write(STDOUT_FILENO, "\n", 1);
}

static void	handle_sigint(int sig)
{
	g_sig = sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_sig = -29;
	rl_on_new_line();
	rl_replace_line("", 0);
	ioctl(0, TIOCSTI, "\n");
}

void	set_parent_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	set_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_IGN);
}

void	set_heredoc_signals(void)
{
	signal(SIGINT, handle_sigint_heredoc);
}
