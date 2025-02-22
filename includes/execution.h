/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:48:53 by rraumain          #+#    #+#             */
/*   Updated: 2025/02/22 14:04:57 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

typedef struct s_pid_data
{
	char	**envp;
	int		nb_cmd;
	int		**pipefd;
	pid_t	*pids;
}	t_pid_data;

//	EXECUTION
void	execute_cmds(t_cmd *cmd, char **envp);

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