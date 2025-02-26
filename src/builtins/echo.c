/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:13:58 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/26 10:08:30 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
		i++;
	if (s1[i] == s2[i])
		return (0);
	return (1);
}

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

int exec_builtin(t_cmd *cmd)
{
	int status;

	status = 0; // a revoir
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (status) ;
	if (!ft_strcmp(cmd->argv[0], "echo"))
		status = exec_echo(cmd);
	if (!ft_strcmp(cmd->argv[0], "cd"))
		status = exec_cd(cmd);
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		status = exec_pwd(cmd);
	if (!ft_strcmp(cmd->argv[0], "export"))
		status = exec_export(cmd);
	if (!ft_strcmp(cmd->argv[0], "unset"))
		status = exec_unset(cmd);
	if (!ft_strcmp(cmd->argv[0], "env"))
		status = exec_env(cmd);
	if (!ft_strcmp(cmd->argv[0], "exit"))
		status = exec_exit(cmd);
	return (status);
}

int exec_echo(t_cmd *cmd)
{
	int	i;

	i = 2;
	if (!ft_strcmp(cmd->argv[0], "echo") && !ft_strcmp(cmd->argv[1], "-n"))
	{
		if (!cmd->argv[2])
			return ;
		while (cmd->argv[i])
		{
			printf("%s", cmd->argv[i]);
			if (cmd->argv[i + 1] != NULL)
				printf(" ");
			i++;
		}
	}
	else if (!ft_strcmp(cmd->argv[0], "echo"))
	{
		i = 1;
		if (cmd->argv[1] == NULL)
		{
			printf("\n");
			return ;
		}
		while (cmd->argv[i])
		{
			printf("%s", cmd->argv[i]);
			if (cmd ->argv[i + 1] != NULL)
				printf(" ");
			i++;
		}		
		printf("\n");
	}
}
