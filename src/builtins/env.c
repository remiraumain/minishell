/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:45:21 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/04 13:43:54 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_env( t_cmd *cmd, t_global_data *sdata)
{
	int i;
	
	i = 0;
	if (!sdata->envp || !sdata->envp[0])
	{
		ft_putstr_fd("envp doesn't exist or is empty\n", 2);
		return (1);// return a revoir
	}
	if (!cmd->argv[1])
	{
		while (sdata->envp && sdata->envp[i] && !cmd->argv[1])
		{
			printf("%s\n", sdata->envp[i]);
			i++;
		}
	}
	else if (cmd->argv[1]) // cas ou il y a plus d'argv[];
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(cmd->argv[1] , 2);
		ft_putstr_fd(": no such file or directory ", 2);
		ft_putstr_fd("\n", 2);
		return (127);
	}
	return (0);
}
