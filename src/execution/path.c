/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:33:29 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/11 09:46:14 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static char	*search_in_paths(char **paths, char *cmd)
{
	int		i;
	char	*tmp;
	char	*result;

	i = 0;
	result = NULL;
	while (paths && paths[i] && !result)
	{
		tmp = join_paths(paths[i], cmd);
		if (!tmp)
			return (NULL);
		if (access(tmp, F_OK | X_OK) == 0)
			result = tmp;
		else
			free(tmp);
		i++;
	}
	return (result);
}

char	*get_command_path(char *cmd, t_envp *envp)
{
	char	**paths;
	char	*found;

	paths = find_paths_in_env(envp);
	if (!paths)
		return (NULL);
	found = search_in_paths(paths, cmd);
	free_split(paths);
	if (!found)
    {
        if (ft_strchr(cmd, '/') && access(cmd, F_OK) == 0)
            found = ft_strdup(cmd);
    }
	return (found);
}
