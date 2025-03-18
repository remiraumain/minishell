/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:45:21 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/17 12:25:48 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_env(t_cmd *cmd, t_global_data *sdata)
{
    t_envp *envp;
    
    if (!sdata->envp)
    {
        ft_putstr_fd("envp doesn't exist or is empty\n", 2);
        return (1); // return a revoir
    }
    if (!cmd->argv[1])
    {
        envp = sdata->envp;
        while (envp)
        {
            printf("%s=%s\n", envp->name, envp->value);
            envp = envp->next;
        }
    }
    else if (cmd->argv[1]) // cas ou il y a plus d'argv[]
    {
        ft_putstr_fd("env: ", 2);
        ft_putstr_fd(cmd->argv[1], 2);
        ft_putstr_fd(": no such file or directory\n", 2);
        return (127);
    }
    return (0);
}
