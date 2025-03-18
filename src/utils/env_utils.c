/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:32:39 by rraumain          #+#    #+#             */
/*   Updated: 2025/03/18 19:00:31 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_env(t_envp *envp)
{
	t_envp	*temp;

	while (envp)
	{
		temp = envp->next;
		free(envp->name);
		free(envp->value);
		free(envp);
		envp = temp;
	}
}

int	ft_envlen(t_envp *envp)
{
	t_envp	*temp;
	int		count;

	temp = envp;
	count = 0;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

t_envp	*ft_lastenv(t_envp *envp)
{
	t_envp	*temp;

	temp = envp;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

t_envp	*search_var(t_envp *envp, char *str)
{
	t_envp	*var;

	var = envp;
	while (var)
	{
		if (!ft_strcmp(var->name, str))
			return (var);
		var = var->next;
	}
	return (NULL);
}

void	clear_env_array(char **envp)
{
	int i;

	i = 0;
	if (!envp)
		return;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}