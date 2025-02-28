/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:33:22 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/27 10:37:16 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static char	*get_env_path(char **envp)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (envp[i] && !path)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path = envp[i] + 5;
		i++;
	}
	return (path);
}

void	free_split(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**find_paths_in_env(char **envp)
{
	char	*env_path;
	char	**paths;

	env_path = get_env_path(envp);
	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ':');
	return (paths);
}

char	*join_paths(char *dir, char *cmd)
{
	char	*joined;
	int		len_dir;
	int		len_cmd;
	size_t	total_size;

	len_dir = ft_strlen(dir);
	len_cmd = ft_strlen(cmd);
	total_size = (size_t)len_dir + (size_t)len_cmd + 2;
	joined = malloc(sizeof(char) * total_size);
	if (!joined)
		return (NULL);
	ft_strlcpy(joined, dir, total_size);
	joined[len_dir] = '/';
	ft_strlcpy(joined + len_dir + 1, cmd, total_size - (len_dir + 1));
	return (joined);
}
