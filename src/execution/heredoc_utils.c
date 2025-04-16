/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:21:21 by rraumain          #+#    #+#             */
/*   Updated: 2025/04/16 17:21:38 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	putendl_fd_heredoc(char *input, int fd, t_global_data *data)
{
	char	*expanded;

	expanded = expand_line(input, data);
	if (!expanded)
		return ;
	ft_putendl_fd(expanded, fd);
	free(expanded);
}
