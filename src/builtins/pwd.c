/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:17:50 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/28 14:41:04 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int exec_pwd(t_cmd *cmd, t_pid_data *pdata)
{
	char *pwd;

	pwd = getcwd(NULL, 0); // allocation
	if (pwd == NULL)
	{
		perror("getcwd failed");
		return (1);
	}
	if (ft_strcmp(cmd->argv[0], "pwd") == 0 && pdata->nb_cmd == 1 && !cmd->argv[1])
	{
		ft_putstr_fd(pwd , 1);
		ft_putstr_fd("\n" , 1);
	}
	free (pwd);
	return (0);
}