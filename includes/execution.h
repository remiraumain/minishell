/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:31:55 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/26 14:06:36 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "minishell.h"

#ifndef EXECUTION_H
# define EXECUTION_H


typedef struct s_pid_data
{
	//char	**envp; // mis dans global_data 
	int		nb_cmd;
	int		**pipefd;
	pid_t	*pids;
}	t_pid_data;

//	EXECUTION
void	execute_cmds(t_cmd *cmd, t_global_data *data);

//	REDIRECTION
int		apply_redirections(t_cmd *cmd);
// int		setup_redirections(t_cmd *cmd);

//	CMD_PATH
char	*get_command_path(char *cmd, char **envp);

//	PATH_UTILS
void	free_split(char **array);
char	**find_paths_in_env(char **envp);
char	*join_paths(char *dir, char *cmd);

//	UTILS
int		count_cmds(t_cmd *cmd);
void	cleanup_pipes(int **pipefd, int count);
int		**create_pipes(int cmd_count);

#endif