/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:13:58 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/26 14:33:25 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int is_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	if (!ft_strcmp(cmd->argv[0], "echo") || 
		!ft_strcmp(cmd->argv[0], "cd") ||
		!ft_strcmp(cmd->argv[0], "pwd") ||
		!ft_strcmp(cmd->argv[0], "export") ||
		!ft_strcmp(cmd->argv[0], "unset") ||
		!ft_strcmp(cmd->argv[0], "env") ||
		!ft_strcmp(cmd->argv[0], "exit"))
		return (1);
	return (0);
}

void exec_builtin(t_cmd *cmd, t_global_data *data)
{
	
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return ;
	if (!ft_strcmp(cmd->argv[0], "echo"))
		data->status = exec_echo(cmd);
	// if (!ft_strcmp(cmd->argv[0], "cd"))
	// 	status = exec_cd(cmd);
	// if (!ft_strcmp(cmd->argv[0], "pwd"))
	// 	status = exec_pwd(cmd);
	// if (!ft_strcmp(cmd->argv[0], "export"))
	// 	status = exec_export(cmd);
	// if (!ft_strcmp(cmd->argv[0], "unset"))
	// 	status = exec_unset(cmd);
	// if (!ft_strcmp(cmd->argv[0], "env"))
	// 	status = exec_env(cmd);
	// if (!ft_strcmp(cmd->argv[0], "exit"))
	// 	status = exec_exit(cmd);
	exit(data->status);
}

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
	if (!ft_strcmp(cmd->argv[0], "echo") && !ft_strcmp(cmd->argv[1], "-n"))
	{
		if (!cmd->argv[2])
			return (0);
		print_echo(cmd, &i);
	}
	else if (!ft_strcmp(cmd->argv[0], "echo"))
	{
		i = 1;
		print_echo(cmd, &i);
		printf("\n");
	}
	return (0);
}

