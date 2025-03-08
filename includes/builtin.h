/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:42:58 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/08 12:58:55 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include "execution.h"

typedef struct s_envp
{
    char *name;            // Le nom de la variable d'env
    char *value;           // La valeur de la variable
    struct s_envp *next;   // Pointeur vers le nœud suivant
} t_envp;


/* UTILS string.c */
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

/* unset.c */
int exec_unset(t_cmd *cmd, t_global_data *data);









#endif 