/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:38:01 by rraumain          #+#    #+#             */
/*   Updated: 2025/04/18 16:36:58 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_sigint_no_redisplay(int sig)
{
	g_sig = sig;
	write(STDOUT_FILENO, "\n", 1);
}

void	handle_sigint(int sig)
{
	g_sig = sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_sig = -29;
	rl_on_new_line();
	rl_replace_line("", 0);
	ioctl(0, TIOCSTI, "\n");
}

void	handle_signal(t_global_data *data)
{
	if (g_sig)
	{
		data->status = 130;
		g_sig = 0;
	}
}
