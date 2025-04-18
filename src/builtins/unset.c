/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:38:39 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/18 16:27:25 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_one_env(t_envp *current)
{
	free(current->name);
	current->name = NULL;
	free(current->value);
	current->value = NULL;
	free(current);
	current = NULL;
}

int	exec_unset(t_cmd *cmd, t_global_data *data)
{
	t_envp	*prev;
	t_envp	*current;
	int		i;

	i = 0;
	if (!data->envp)
		return (0);
	while (cmd->argv[i++])
	{
		current = data->envp;
		while (current && ft_strcmp(current->name, cmd->argv[i]) != 0)
		{
			prev = current;
			current = current->next;
		}
		if (current)
		{
			if (current == data->envp)
				data->envp = current->next;
			else
				prev->next = current->next;
			free_one_env(current);
		}
	}
	return (0);
}
