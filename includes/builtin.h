/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:42:58 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/04 15:27:54 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include "execution.h"

/* UTILS*/
int	ft_strcmp(char *s1, char *s2);

/* builtin_control.c */
int is_builtin_child(t_cmd *cmd);
void exec_builtin_child(t_cmd *cmd, t_pid_data *pdata, t_global_data *data);
//int exec_builtin_child(t_cmd *cmd, t_pid_data *pdata, t_global_data *data);
int is_builtin_parent(t_cmd *cmd);
//int exec_builtin_parent(t_cmd *cmd, t_pid_data *pdata, t_global_data *data);
void exec_builtin_parent(t_cmd *cmd, t_pid_data *pdata, t_global_data *data);


/* echo */
int exec_echo(t_cmd *cmd);

/* cd.c */
int exec_cd(t_cmd *cmd, t_pid_data *pdata, t_global_data *sdata);

/* pwd */
int exec_pwd(t_cmd *cmd, t_pid_data *pdata);

/* env.c*/
int exec_env(t_cmd *cmd, t_global_data *sdata);

/* exit.c */
int exec_exit(t_cmd *cmd, t_global_data *data);

/* */









#endif 