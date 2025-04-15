/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:13:58 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/15 11:05:35 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_n_option(char *s)
{
	int	i;

	if (!s || s[0] != '-')
		return (0);
	i = 1;
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	if (i > 1)
		return (1);
	else
		return (0);
}

int	exec_echo(t_cmd *cmd)
{
	int	i;
	int	no_newline;

	i = 1;
	no_newline = 0;
	while (cmd->argv[i] && is_valid_n_option(cmd->argv[i]))
	{
		no_newline = 1;
		i++;
	}
	while (cmd->argv[i])
	{
		printf("%s", cmd->argv[i]);
		if (cmd->argv[i + 1])
			printf(" ");
		i++;
	}
	if (no_newline == 0)
		printf("\n");
	return (0);
}
