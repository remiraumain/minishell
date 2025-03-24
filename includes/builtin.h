/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:42:58 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/24 15:48:12 by nolecler         ###   ########.fr       */
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

/* cd_utils.c*/
void update_old_pwd(t_envp *envp, const char *old_pwd);
void update_pwd(t_envp*envp, const char *new_pwd);
int print_error(char *argv);
char *get_var_home(t_envp *envp);
//char	*get_old_pwd(t_envp *envp); // for test


/* cd.c */
int exec_cd(t_cmd *cmd, t_pid_data *pdata, t_global_data *sdata);

/* echo.c */
int exec_echo(t_cmd *cmd);

/* env.c*/
int exec_env(t_cmd *cmd, t_global_data *sdata);

/* exit.c */
int exec_exit(t_cmd *cmd, t_global_data *data, t_pid_data *pdata);

/* export.c*/
int exec_export(t_cmd *cmd, t_global_data *data);

/* pwd */
int exec_pwd(t_cmd *cmd, t_pid_data *pdata);


/* unset.c */
int exec_unset(t_cmd *cmd, t_global_data *data);

//	ENVP_COPY
t_envp	*search_var(t_envp *envp, char *str);
//char 	**convert_envp_to_ptrchar(t_envp *envp);


//

#endif 