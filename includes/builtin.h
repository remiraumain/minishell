/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:42:58 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/03 09:23:24 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include "execution.h"

/* UTILS*/
int	ft_strcmp(char *s1, char *s2);

/* BUILTUIN*/
int is_builtin(t_cmd *cmd);
void exec_builtin(t_cmd *cmd, t_global_data *data, t_pid_data *pdata);

/* echo */
int exec_echo(t_cmd *cmd);

/* cd */

int exec_cd(t_cmd *cmd, t_pid_data *pdata, t_global_data *sdata);
/* pwd */
int exec_pwd(t_cmd *cmd, t_pid_data *pdata);














#endif 