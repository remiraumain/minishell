/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:12:25 by rraumain          #+#    #+#             */
/*   Updated: 2025/03/04 09:34:57 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint(int sig)
{
	g_sig = sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	handle_sigint_child(int sig)
{
	g_sig = sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

static void	handle_sigint_heredoc(int sig)
{
	g_sig = sig;
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
	signal(SIGINT, handle_sigint_child);
}

void	set_heredoc_signals(void)
{
	signal(SIGINT, handle_sigint_heredoc);
}