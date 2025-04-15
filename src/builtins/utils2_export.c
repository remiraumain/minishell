/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:45:47 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/15 11:50:15 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_classic_var_invalid(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '=' || (str[i] >= '0' && str[i] <= '9'))
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (1);
		i++;
	}
	return (0);
}

static int	is_plus_equal_var_invalid(char *str, char *plus_equal)
{
	int	i;
	int	len;

	i = 0;
	len = plus_equal - str;
	if (len == 0 || (str[0] >= '0' && str[0] <= '9'))
		return (1);
	while (i < len)
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (1);
		i++;
	}
	return (0);
}

int	is_var_valid(char *str)
{
	int		result;
	char	*plus_equal;

	plus_equal = ft_strnstr(str, "+=", ft_strlen(str));
	if (plus_equal)
	{
		result = is_plus_equal_var_invalid(str, plus_equal);
		return (result);
	}
	result = is_classic_var_invalid(str);
	return (result);
}

void	add_var_in_env(char *str, t_envp *envp)
{
	t_envp	*last;
	t_envp	*new;

	new = init_var(str);
	if (!new)
	{
		clear_env(envp);
		return ;
	}
	if (!envp)
		envp = new;
	else
	{
		last = ft_lastenv(envp);
		last->next = new;
	}
}
