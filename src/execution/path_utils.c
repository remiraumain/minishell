/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:33:22 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/05 13:51:32 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

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

char	**find_paths_in_env(t_envp *envp)
{
	t_envp	*var;
	char	**paths;

	var = search_var(envp, "PATH");
	if (!var)
		return (NULL);
	paths = ft_split(var->value, ':');
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
