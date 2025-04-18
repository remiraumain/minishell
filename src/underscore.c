/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   underscore.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:33:25 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/18 16:33:53 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_underscore(t_global_data *data)
{
	t_envp	*var;
	t_envp	*prev;

	var = data->envp;
	while (ft_strcmp(var->name, "_"))
	{
		prev = var;
		var = var->next;
	}
	prev->next = var->next;
	free_one_env(var);
	add_var_in_env("_=", data->envp);
}

void	update_underscore(t_cmd *cmds, t_global_data *data)
{
	t_cmd	*last;
	size_t	i;
	char	*path;
	char	*updated;

	last = cmds;
	while (last->next)
		last = last->next;
	i = 0;
	while (last->argv[i + 1])
		i++;
	path = get_command_path(last->argv[i], data->envp);
	if (!path)
	{
		updated = ft_strjoin("_=", last->argv[i]);
	}
	else
	{
		updated = ft_strjoin("_=", path);
		free(path);
	}
	if (!updated)
		return ;
	update_value(data, updated);
	free(updated);
}
