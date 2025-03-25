/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:38:39 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/25 15:17:08 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"


int exec_unset(t_cmd *cmd, t_global_data *data)
{
	t_envp	*prev;
	t_envp	*current;
	int		i;
	
	i = 1;
	if (!data->envp)
		return (0);
	while (cmd->argv[i])
	{
		current = data->envp;
		while (current && ft_strcmp(current->name, cmd->argv[i]) != 0)
		{
			prev = current;
			current = current->next;
		}
		if (!current)
			return (1);
		if (current == data->envp)
			data->envp = current->next;
		else
			prev->next = current->next;
		free(current->name);
		current->name = NULL;
		free(current->value);
		current->value = NULL;
		free(current);
		current = NULL;
		i++;
	}
	return (1);// test	
}



