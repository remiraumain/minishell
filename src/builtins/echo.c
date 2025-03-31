/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:13:58 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/31 15:45:32 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	print_echo(t_cmd *cmd, int *i)
{
	while (cmd->argv[*i])
	{
		printf("%s", cmd->argv[*i]);
		if (cmd->argv[*i + 1] != NULL)
			printf(" ");
		*i = *i + 1;
	}
}

int exec_echo(t_cmd *cmd)
{
	int	i;

	i = 2;
	if (!ft_strcmp(cmd->argv[1], "-n"))
	{
		if (!cmd->argv[2])
			return (0);
		print_echo(cmd, &i);
	}
	else
	{
		i = 1;
		print_echo(cmd, &i);
		printf("\n");
	}
	return (0);
}
