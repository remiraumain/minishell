/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 08:31:23 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/12 11:46:38 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// gerer le cas sans = (d'ou le bool dans la structure)
// fonction qui affiche export
// export affiche dans l ordre alphabletique avec declare -x au debut
// sera afficher dans export "declare -x titi" mais pas dans env 

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
		name = malloc(i + 1); // a free
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
		value = ft_strdup(&envp[i + 1]); // a free
		if (!value)
		{
			free(value);
			return (NULL);
		}
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


void var_copy(char **envp, t_envp **vars)
{
	t_envp *new;
	int	i;
	
	i = 0;
	if (!envp || !envp[0])
		return ;
	while (envp && envp[i])
	{
		new = init_var(envp[i]); // a free
        if (!new)
            return ;
		if (*vars == NULL)
			*vars = new;	
		else
			ft_lstadd_back(vars, new);
		new->pos = i;
		i++;
	}
}




