/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:42:58 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/11 10:15:18 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include "execution.h"

typedef struct s_envp
{
    char *name;
    char *value; 
    int pos;  // rang de la variable   
    //bool equal; //        
    struct s_envp *next;   
} t_envp;




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

/* envp.copy.c*/
t_envp *init_var(char *envp);
void var_copy(char **envp, t_envp **vars);

/* exit.c */
int exec_exit(t_cmd *cmd, t_global_data *data);


/* pwd */
int exec_pwd(t_cmd *cmd, t_pid_data *pdata);


/* unset.c */
int exec_unset(t_cmd *cmd, t_global_data *data);


/* Utils1.c */
int     ft_strcmp(char *s1, char *s2);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
// char	*ft_strdup(char *src);
// void	ft_lstadd_back(t_envp **lst, t_envp *new);
void    free_env_copy(t_envp *var);






#endif 