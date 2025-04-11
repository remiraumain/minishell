/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:42:58 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/11 09:55:07 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "execution.h"
# include "minishell.h"

/* builtin_control.c */
int		is_builtin_child(t_cmd *cmd);
void	exec_builtin_child(t_cmd *cmd, t_pid_data *pdata, t_global_data *data);
int		has_child_process(t_cmd *head);
int		is_builtin_parent(t_cmd *cmd);
void	exec_builtin_parent(t_cmd *cmd, t_pid_data *pdata, t_global_data *data,
			t_cmd *head);

/* cd.c */
int		exec_cd(t_cmd *cmd, t_pid_data *pdata, t_global_data *sdata);

/* echo.c */
int		exec_echo(t_cmd *cmd);

/* env.c*/
int		exec_env(t_cmd *cmd, t_global_data *sdata);

/* exit.c */
int		exec_exit(t_cmd *cmd, t_global_data *data, t_pid_data *pdata,
			t_cmd *head);

/* export.c*/
int		exec_export(t_cmd *cmd, t_global_data *data);

/* pwd.c */
int		exec_pwd(t_cmd *cmd, t_pid_data *pdata);

/* unset.c */
int		exec_unset(t_cmd *cmd, t_global_data *data);

/* utils_cd.c*/
void	update_old_pwd(t_envp *envp, const char *old_pwd);
void	update_pwd(t_envp *envp, const char *new_pwd);
int		print_error(char *argv);
char	*get_var_home(t_envp *envp);
int		cd_slash(t_cmd *cmd, char *pwd);

/* utils2_cd.c */
int		print_error(char *argv);
void	free_path_pwd(char *path, char *pwd);

/* utils_exit.c*/
int		is_numeric(char *str);
void	print_error_message(char *str);
void	exit_no_args(t_global_data *data, t_pid_data *pdata, t_cmd *head);
void	exit_invalid_numeric(char *arg, t_global_data *data, t_pid_data *pdata,
			t_cmd *head);
void	cleanup(t_global_data *data, t_pid_data *pdata, t_cmd *head);

/* utils_export.c*/
void	ft_sort_params(t_envp *env);
int		is_var_valid(char *str);
int		is_var_exist(char *argv, t_global_data *data);

#endif