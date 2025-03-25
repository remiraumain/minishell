/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:17:50 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/25 15:17:22 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// cas de too many argument	A FAIRE
int exec_pwd(t_cmd *cmd, t_pid_data *pdata)
{
	char *pwd;
	
	(void)pdata;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		perror("getcwd failed");
		return (1);
	}
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
	{
		ft_putstr_fd(pwd , 1);
		ft_putstr_fd("\n" , 1);
	}
	free (pwd);
	return (0);
}
