/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 08:31:23 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/22 11:50:34 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// pour l'execution travailler avec la copie de char **envp
// donc faire une fonction qui copie la liste chainee de l'env mais en char **envp


// cherche une variable dans la liste 
// static int	search_var(t_envp *envp, char *str)
// {
// 	t_envp	*var;

// 	var = envp;
// 	while (var)
// 	{
// 		if (!ft_strcmp(var->name, str))
// 			return (1);
// 		var = var->next;
// 	}
// 	return (0);
// }


static char *var_name(char *envp)
{
	int i;
	char *name;

	name = NULL;
	i = 0;
	if (!envp || !envp[i])
		return (NULL);
	while (envp[i] != '=')
		i++;
	if (envp[i] == '=')
	{
		name = malloc(i + 1);
		if (!name)
		{
			free(name);
			return (NULL);
		}	
        ft_strncpy(name, envp, i);
        name[i] = '\0';
	}
	else
		return (NULL);
	return (name);
}

static char *var_value(char *envp)
{
	int i;
	char *value;
	
	i = 0;
	if (!envp[i])
		return (NULL);
	while (envp[i] != '=')
		i++;
	if (envp[i] == '=')
	{
		value = ft_strdup(&envp[i + 1]);
		if (!value)
			return (NULL);
	}
	else
		return (NULL);
	return (value);
}


t_envp *init_var(char *envp)
{
	t_envp *new;
	
	new = malloc(sizeof(t_envp));
	if (!new)
		return (NULL) ;
	new->name = var_name(envp);
	new->value = var_value(envp);
	new->pos = 0;
	new->next = NULL;
	return (new);
}


// a free dans le main 
t_envp *var_copy(char **envp)
{
	t_envp *new;
	t_envp *vars;
	int	i;
	
	vars = NULL;
	i = 0;
	if (!envp || !envp[0])
		return (NULL);
	while (envp && envp[i])
	{
		new = init_var(envp[i]);
        if (!new)
            return ;
		ft_lstadd_back(vars, new);
		new->pos = i;
		i++;
	}
	return (vars);
}




