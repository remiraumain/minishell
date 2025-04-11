/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:12:12 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/11 10:09:08 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//test, a voir char **env??

void path_error(t_cmd *cmd, t_cmd *head, t_pid_data *pdata, char **env)
{
    if (cmd->argv[0][0] == '.' || cmd->argv[0][0] == '/')
    {
        if (access(cmd->argv[0], F_OK) == 0 && is_directory(cmd->argv[0]))
        {
            ft_putstr_fd(cmd->argv[0], 2);
            ft_putstr_fd(": Is a directory\n", 2);
            clear_env_array(env);
            exit_clean_child(pdata, head, 126);
        }
        if (access(cmd->argv[0], F_OK) == 0 && access(cmd->argv[0], X_OK) != 0)
        {
            ft_putstr_fd(cmd->argv[0], 2);
            ft_putstr_fd(": Permission denied\n", 2);
            clear_env_array(env);
            exit_clean_child(pdata, head, 126);
        }
        if (access(cmd->argv[0], F_OK) != 0)
        {
            ft_putstr_fd(cmd->argv[0], 2);
            ft_putstr_fd(": No such file or directory\n", 2);
            clear_env_array(env);
            exit_clean_child(pdata, head, 127);
        }
    }
    ft_putstr_fd(cmd->argv[0], 2);
    ft_putstr_fd(": command not found\n", 2);
    clear_env_array(env);
    exit_clean_child(pdata, head, 127);
}