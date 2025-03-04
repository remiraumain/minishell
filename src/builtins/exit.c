/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:04:44 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/04 15:34:55 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "libft.h"

// exit entier maximale a gerer ?? 
// + et - a gerer ? 


static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (1);
	}
	return (0);
}
// le exit code = 255 maximum

int exec_exit(t_cmd *cmd, t_global_data *data)
{
	// s il y a un argument 
	// si c'est un nombre trop grand ??
	data->status = 0;
	if (cmd->argv[1])
	{
		// si ce n'est pas un nombre
		if (!is_numeric(cmd->argv[1])) 
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(cmd->argv[1] , 2);
			ft_putstr_fd(": numeric argument required", 2);
			//data->status = 2;
			//exit (data->status);
			exit(2);
		}
		else
			data->status = ft_atoi(cmd->argv[1]);
	}
	exit (data->status);
}