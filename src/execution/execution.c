/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:24:39 by rraumain          #+#    #+#             */
/*   Updated: 2025/04/04 15:23:51 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_and_wait(t_pid_data *pdata)
{
	int	i;
	int	status;

	i = 0;
	while (i < pdata->nb_cmd - 1)
	{
		close(pdata->pipefd[i][0]);
		close(pdata->pipefd[i][1]);
		i++;
	}
	i = 0;
	while (i < pdata->nb_cmd)
    {
		if (pdata->pids[i] > 0)
   			waitpid(pdata->pids[i], &status, 0);
        if (WIFEXITED(status))
            pdata->gdata->status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            pdata->gdata->status = 128 + WTERMSIG(status);
        i++;
    }
}

#include <sys/stat.h>

static int is_directory(const char *path)
{
	struct stat sb;
	return (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode));
}


static void	exit_clean_child(t_pid_data *pdata, t_cmd *head, char **env, char *path, int status)
{
	if (env)
	{
		clear_env_array(env);
		env = NULL;
	}
	if (path)
		free(path);
	if (pdata)
	{
		free(pdata->pids);
		cleanup_pipes(pdata->pipefd, pdata->nb_cmd - 1);
		clear_env(pdata->gdata->envp);
		free(pdata->gdata);
		free(pdata);
	}
	free_cmd_list(head);
	exit(status);
}

static void	execute_child(t_cmd *cmd, int index, t_pid_data *pdata, t_cmd *head)
{
	int		i;
	char	*path;
	char 	**env;
	
	dup_fd(pdata, index, cmd);
	pdata->gdata->status = 0;
	i = 0;
	while (i < pdata->nb_cmd - 1)
	{
		close(pdata->pipefd[i][0]);
		close(pdata->pipefd[i][1]);
		i++;
	}
	if (!apply_redirections(cmd, index))
		exit_clean_child(pdata, head, NULL, NULL, EXIT_FAILURE);
	if (is_builtin_child(cmd) == 1)
	{
		exec_builtin_child(cmd, pdata, pdata->gdata);
		free(pdata->pids);
		cleanup_pipes(pdata->pipefd, pdata->nb_cmd - 1);
		clear_env(pdata->gdata->envp);
		free(pdata->gdata);
		free(pdata);
		free_cmd_list(head);
		exit(0); // should be status exit code
		//exit (data->status);
	}
	env = convert_env(pdata->gdata->envp);
	path = get_command_path(cmd->argv[0], pdata->gdata->envp);
	if (!path)
	{
		if (cmd->argv[0][0] == '.' || cmd->argv[0][0] == '/')
		{
			// Fichier existe mais pas exécutable
			if (access(cmd->argv[0], F_OK) == 0 && access(cmd->argv[0], X_OK) != 0)
			{
				//printf("je rentre ici 1\n");// ///!!!!!
				ft_putstr_fd(cmd->argv[0], 2);
				ft_putstr_fd(": Permission denied\n", 2);
				exit_clean_child(pdata, head, env, NULL, 126);
			}
			// C’est un dossier
			if (access(cmd->argv[0], F_OK) == 0 && is_directory(cmd->argv[0]))
			{
				ft_putstr_fd(cmd->argv[0], 2);
				ft_putstr_fd(": Is a directory\n", 2);
				exit_clean_child(pdata, head, env, NULL, 126);
			}
			// Fichier inexistant
			if (access(cmd->argv[0], F_OK) != 0)
			{
				ft_putstr_fd(cmd->argv[0], 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				exit_clean_child(pdata, head, env, NULL, 127);
			}
		}
		// Cas : pas un chemin, juste une commande invalide
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit_clean_child(pdata, head, env, NULL, 127);
	}
	execve(path, cmd->argv, env);		
	clear_env_array(env);
	free(path);
	ft_putstr_fd(cmd->argv[0], 2);//??
	exit(EXIT_FAILURE);
}

static int	fork_and_exec_child(t_cmd *cmd, int i, t_pid_data *pdata, t_cmd *head)
{
	pid_t	pid;

	if (cmd->redir && (cmd->redir->type == REDIR_HEREDOC
		|| cmd->redir->type == REDIR_HEREDOC_Q)
	&& !set_heredoc(cmd->redir, pdata->gdata))
	{
		perror("heredoc");
		return (0);
	}
	if (g_sig && ft_strncmp(cmd->argv[0], "echo", 5) != 0)
		return (0);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (0);
	}
	set_child_signals();
	if (pid == 0)
		execute_child(cmd, i, pdata, head);
	pdata->pids[i] = pid;
	return (1);
}

static void	process_cmds(t_cmd *cmd, t_pid_data *pdata, t_global_data *data)
{
	t_cmd	*head;
	int		i;

	head = cmd;
	pdata->pids = malloc(sizeof(pid_t) * pdata->nb_cmd);
	if (!pdata->pids)
		return ;
	ft_bzero(pdata->pids, sizeof(pid_t) * pdata->nb_cmd);
	i = 0;
	while (cmd)
	{
		if (!cmd->argv || !cmd->argv[0] || cmd->argv[0][0] == '\0')
		{
			data->status = 0;
			cmd = cmd->next;
			continue ;
		}
		if (is_builtin_parent(cmd) == 1)
		{
			if (!has_child_process(head))
			{
				exec_builtin_parent(cmd, pdata, data, head);
				clean_heredocs(head);
				free(pdata->pids);
				return ;
			}
		}
		else if (!fork_and_exec_child(cmd, i, pdata, head))
			break ;
		i++;
		cmd = cmd->next;
	}
	close_and_wait(pdata);
	clean_heredocs(head);
	free(pdata->pids);
}

void	execute_cmds(t_cmd *cmd, t_global_data *data)
{
	t_pid_data	*pdata;

	pdata = malloc(sizeof(t_pid_data));
	if (!pdata)
		return ;
	pdata->gdata = data;
	pdata->nb_cmd = count_cmds(cmd);
	if (pdata->nb_cmd == 0)
	{
		free(pdata);
		return ;
	}
	pdata->pipefd = create_pipes(pdata->nb_cmd - 1);
	if (!pdata->pipefd && pdata->nb_cmd - 1 > 0)
	{
		free(pdata);
		return ;
	}
	process_cmds(cmd, pdata, data);
	cleanup_pipes(pdata->pipefd, pdata->nb_cmd - 1);
	free(pdata);
}

