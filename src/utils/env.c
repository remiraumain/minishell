/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:33:06 by rraumain          #+#    #+#             */
/*   Updated: 2025/03/18 13:44:28 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_new(t_envp **new, char *envp, char *equal)
{
	(*new)->name = ft_strndup(envp, equal - envp);
	if (!(*new)->name)
	{
		free((*new));
		return ;
	}
	(*new)->value = ft_strdup(equal + 1);
	if (!(*new)->value)
	{
		free((*new)->name);
		free((*new));
		return ;
	}
	(*new)->next = NULL;
}

static t_envp	*init_var(char *envp, int pos)
{
	t_envp	*new;
	char	*equal;

	new = malloc(sizeof(t_envp));
	if (!new)
		return (NULL);
	equal = ft_strchr(envp, '=');
	if (!equal)
	{
		free(new);
		return (NULL);
	}
	new->pos = pos;
	fill_new(&new, envp, equal);
	return (new);
}

t_envp	*init_env(char **envp)
{
	t_envp	*head;
	t_envp	*last;
	t_envp	*new;
	int		i;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		new = init_var(envp[i], i);
		if (!new)
		{
			clear_env(head);
			return (NULL);
		}
		if (!head)
			head = new;
		else
		{
			last = ft_lastenv(head);
			last->next = new;
		}
		i++;
	}
	return (head);
}

static void	fill_var(t_envp *envp, int index, char ***res)
{
	char	*var;
	size_t	len;


	var = malloc(ft_strlen(envp->name) + ft_strlen(envp->value) + 2);
	if (!var)
	{
		while (index > 0)
			free((*res)[--index]);
		free(*res);
		return ;
	}
	len = ft_strlen(envp->name);
	ft_strlcpy(var, envp->name, len + 1);
	var[len] = '=';
	var[len + 1] = '\0';
	ft_strlcat(var, envp->value, len + ft_strlen(envp->value) + 2);
	(*res)[index] = var;
}

char	**convert_env(t_envp *envp)
{
	char	**res;
	t_envp	*temp;
	int		i;

	res = malloc((ft_envlen(envp) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	temp = envp;
	i = 0;
	while (temp)
	{
		fill_var(temp, i, &res);
		if (!res)
			return (NULL);
		i++;
		temp = temp->next;
	}
	res[i] = NULL;
	return (res);
}
