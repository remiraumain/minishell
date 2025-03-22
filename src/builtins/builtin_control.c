/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:10:52 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/19 16:03:28 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin_child(t_cmd *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	if (!ft_strcmp(cmd->argv[0], "echo") || 
		!ft_strcmp(cmd->argv[0], "pwd") ||
		!ft_strcmp(cmd->argv[0], "env"))
		return (1);
	return (0);
}

int is_builtin_parent(t_cmd *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	if (!ft_strcmp(cmd->argv[0], "cd") ||
		!ft_strcmp(cmd->argv[0], "export") ||
		!ft_strcmp(cmd->argv[0], "unset") ||
		!ft_strcmp(cmd->argv[0], "exit"))
		return (1);
	return (0);
}

void exec_builtin_child(t_cmd *cmd, t_pid_data *pdata, t_global_data *data)
//int exec_builtin_child(t_cmd *cmd, t_pid_data *pdata, t_global_data *data)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return ; // return(data->status) ou exit (data->status);
	if (!ft_strcmp(cmd->argv[0], "echo"))
		data->status = exec_echo(cmd);
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		data->status = exec_pwd(cmd, pdata);
	if (!ft_strcmp(cmd->argv[0], "env"))
		data->status = exec_env(cmd, data);
	// exit(data->status); 
}

void exec_builtin_parent(t_cmd *cmd, t_pid_data *pdata, t_global_data *data)
//int exec_builtin_parent(t_cmd *cmd, t_pid_data *pdata, t_global_data *data)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return ; // return (data->status) ?
	if (!ft_strcmp(cmd->argv[0], "cd"))
		data->status = exec_cd(cmd, pdata, data);
	if (!ft_strcmp(cmd->argv[0], "export"))
		data->status = exec_export(cmd, data);
	// if (!ft_strcmp(cmd->argv[0], "unset"))
	// 	data->status = exec_unset(cmd, data);
	if (!ft_strcmp(cmd->argv[0], "exit"))
		data->status = exec_exit(cmd, data, pdata);
	// return(0); // return a voir
}
