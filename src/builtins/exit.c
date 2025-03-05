/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:04:44 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/05 15:56:25 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h> 
#include "libft.h"

// long long min et max a gerer
// bash --posix

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (((str[0] == '+' || str[0] == '-') && (str[1] >= '0' && str[1] <= '9'))
			|| (str[i] >= '0' && str[i] <= '9'))
			i++;
		else
			return (0);
	}
	return (1);
}
// le exit code = 255 maximum

static long long ft_atoll(char *str)
{
	int	i;
	long long	stock;
	long long	sign;

	stock = 0;
	sign = 1;
	i = 0;
	
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		 if (((stock > LLONG_MAX / 10) || (stock == LLONG_MAX / 10 && str[i] - '0' > LLONG_MAX % 10)))
		// 	((stock < LLONG_MIN / 10) || (stock == LLONG_MIN / 10 && str[i] - '0' > 8)))
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": numeric argument required", 2);
			return (2);
		}
		if (((stock < LLONG_MIN / 10) || (stock == LLONG_MIN / 10 && str[i] - '0' > -(LLONG_MIN % 10))))
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": numeric argument required", 2);
			return (2);
		}
		stock = (stock * 10) + (str[i] - '0');
		i++;
	}
	return (stock * sign);
}

int exec_exit(t_cmd *cmd, t_global_data *data)
{
	long long value;
	
	data->status = 0;
	if (cmd->argv[2])
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	if (cmd->argv[1])
	{	
		if (!is_numeric(cmd->argv[1])) 
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(cmd->argv[1] , 2);
			ft_putstr_fd(": numeric argument required", 2);
			exit(2);
		}
		// value = ft_atoll(cmd->argv[1]);
		// if (value > LLONG_MAX || value < LLONG_MIN)
        // {
        //     ft_putstr_fd("exit\n", 2);
        //     ft_putstr_fd("exit: ", 2);
        //     ft_putstr_fd(cmd->argv[1], 2);
        //     ft_putstr_fd(": numeric argument required\n", 2);
        //     exit (2); // Retourner le code de sortie 255 en cas de dépassement
        // }

        // Sinon, mettre à jour le status avec la valeur calculée
        //data->status = (int)value;
		else
		{
			value = ft_atoll(cmd->argv[1]);
			if (value > LLONG_MAX || value < LLONG_MIN)
			{
				ft_putstr_fd("exit\n", 2);
				ft_putstr_fd("exit: ", 2);
				ft_putstr_fd(cmd->argv[1] , 2);
				ft_putstr_fd(": numeric argument required", 2);
				exit(2);
			}
		}
	}
	exit (data->status);
}
// exit long long max 9223372036854775807
// exit (255);

// -9223372036854775808 long long min


//atol : conversion d'une chaine de caract en long long int 



