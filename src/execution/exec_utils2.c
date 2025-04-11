/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:12:12 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/11 10:49:01 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_message(t_cmd *cmd, char *message)
{
    ft_putstr_fd(cmd->argv[0], 2);
    ft_putstr_fd(message, 2);
}

void    exit_and_clean(t_cmd *head, t_pid_data *pdata, char **env, int status)
{
    clear_env_array(env);
    exit_clean_child(pdata, head, status);
}

void path_error(t_cmd *cmd, t_cmd *head, t_pid_data *pdata, char **env)
{
    if (cmd->argv[0][0] == '.' || cmd->argv[0][0] == '/')
    {
        if (access(cmd->argv[0], F_OK) == 0 && is_directory(cmd->argv[0]))
        {
            print_message(cmd, ": Is a directory\n");
            exit_and_clean(head, pdata, env, 126);
        }
        if (access(cmd->argv[0], F_OK) == 0 && access(cmd->argv[0], X_OK) != 0)
        {
            print_message(cmd, ": Permission denied\n");
            exit_and_clean(head, pdata, env, 126);
        }
        if (access(cmd->argv[0], F_OK) != 0)
        {
            print_message(cmd, ": No such file or directory\n");
            exit_and_clean(head, pdata, env, 127);
        }
    }
    print_message(cmd, ": command not found\n");
    exit_and_clean(head, pdata, env, 127);
}


