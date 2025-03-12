/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:50:29 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/12 11:43:50 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int copy_var(char **copy_env, char **envp)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (envp && envp[i])
		i++;
	while (j < i)
	{
		copy_env[j] = ft_strdup(envp[j]);
		if (!copy_env[j])
		{
			while(j > 0)
			{
				free(copy_env[j]);
				j--;
			}
			free(copy_env);
			return (0) ;
		}
		j++;
	}
	return (1);
}

char **env_copy(char **envp)
{
	int i;
	int j;
	char **copy_env;
	
	i = 0;
	j = 0;
	copy_env = NULL;
	if (!envp || !envp[i])
		return (NULL);
	while (envp[i])
		i++;
	copy_env = malloc(sizeof(char *) * (i + 1));
	if (!copy_env)
		return (NULL);
	if (copy_var(copy_env, envp) == 0)
		return (NULL);
	copy_env[i] = NULL;
	return (copy_env);
}






