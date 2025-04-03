/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:45:21 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/03 10:07:41 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_env(t_cmd *cmd, t_global_data *sdata)
{
	t_envp	*var;

	if (!sdata->envp)
	{
		ft_putstr_fd("envp doesn't exist or is empty\n", 2);
		return (1);
	}
	if (!cmd->argv[1])
	{
		var = sdata->envp;
		while (var)
		{
			if (var->value)
				printf("%s=%s\n", var->name, var->value);
			var = var->next;
		}
	}
	else if (cmd->argv[1])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	return (0);
}
