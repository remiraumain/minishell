/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:54:39 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/08 16:27:14 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_and_wait(t_pid_data *pdata)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
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

int is_directory(const char *path)
{
	struct stat sb;
	return (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode));
}