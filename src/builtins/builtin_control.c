/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:10:52 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/03 14:03:03 by nolecler         ###   ########.fr       */
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


void exec_builtin(t_cmd *cmd, t_global_data *data, t_pid_data *pdata)
{
	
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return ;
	if (!ft_strcmp(cmd->argv[0], "echo"))
		data->status = exec_echo(cmd);
	if (!ft_strcmp(cmd->argv[0], "cd"))
		data->status = exec_cd(cmd, pdata, data);
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		data->status = exec_pwd(cmd, pdata);
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