/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:42:58 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/18 19:39:13 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include "execution.h"


/* builtin_control.c */
int is_builtin_child(t_cmd *cmd);
void exec_builtin_child(t_cmd *cmd, t_pid_data *pdata, t_global_data *data);
//int exec_builtin_child(t_cmd *cmd, t_pid_data *pdata, t_global_data *data);
int is_builtin_parent(t_cmd *cmd);
//int exec_builtin_parent(t_cmd *cmd, t_pid_data *pdata, t_global_data *data);
void exec_builtin_parent(t_cmd *cmd, t_pid_data *pdata, t_global_data *data);



/* cd.c */
int exec_cd(t_cmd *cmd, t_pid_data *pdata, t_global_data *sdata);

/* echo.c */
int exec_echo(t_cmd *cmd);

/* env.c*/
int exec_env(t_cmd *cmd, t_global_data *sdata);

/* exit.c */
int exec_exit(t_cmd *cmd, t_global_data *data, t_pid_data *pdata);


/* pwd */
int exec_pwd(t_cmd *cmd, t_pid_data *pdata);


/* unset.c */
int exec_unset(t_cmd *cmd, t_global_data *data);

//	ENVP_COPY
t_envp	*search_var(t_envp *envp, char *str);
char 	**convert_envp_to_ptrchar(t_envp *envp);




#endif 