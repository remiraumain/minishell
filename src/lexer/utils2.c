/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:46:32 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/12 14:13:13 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_stop_char(char c)
{
	if (
		is_whitespace(c)
		|| c == '\''
		|| c == '"'
		|| c == '|'
		|| c == '<'
		|| c == '>'
	)
		return (1);
	return (0);
}

int	is_inset(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	copy_char(char **buffer, char c)
{
	int		len;
	char	*new_buf;

	if (!*buffer)
	{
		*buffer = malloc(2);
		if (!*buffer)
			return ;
		(*buffer)[0] = c;
		(*buffer)[1] = '\0';
		return ;
	}
	len = ft_strlen(*buffer);
	new_buf = malloc(len + 2);
	if (!new_buf)
		return ;
	ft_memcpy(new_buf, *buffer, len);
	new_buf[len] = c;
	new_buf[len + 1] = '\0';
	free(*buffer);
	*buffer = new_buf;
}
