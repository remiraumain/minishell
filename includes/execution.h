/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:48:53 by rraumain          #+#    #+#             */
/*   Updated: 2025/03/03 23:11:34 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

//	EXECUTION
void	execute_cmds(t_cmd *cmd, t_global_data *data);

//	REDIRECTION
int		apply_redirections(t_cmd *cmd, int cmd_i);
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
void	dup_fd(t_pid_data *pdata, int index);

//	HEREDOC
int		set_heredoc(t_redir *redir, t_global_data *data);
void	clean_heredocs(t_cmd *cmd, int len);
char	*create_heredoc_filename(int cmd_i, int redir_i);

#endif