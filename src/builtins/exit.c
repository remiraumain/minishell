/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:04:44 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/18 19:42:35 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h> 

static int is_numeric(char *str)
{
	int i;

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

// -9223372036854775808 long long min
// 9223372036854775807

static long long ft_atoll(char *str)
{
	int	i;
	unsigned long long	stock;
	int	sign;

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
		stock = (stock * 10) + (str[i] - '0');
		i++;
	}
	if (sign == -1)
	{
		if (stock > (unsigned long long) LLONG_MAX + 1)
		{
			ft_putstr_fd("exit\n", 2);
            ft_putstr_fd("exit: ", 2);
            ft_putstr_fd(str, 2);
            ft_putstr_fd(": numeric argument required\n", 2);
            exit (2);
		}
	}
	else if (sign == 1)
	{
		if (stock > LLONG_MAX)
		{
			ft_putstr_fd("exit\n", 2);
            ft_putstr_fd("exit: ", 2);
            ft_putstr_fd(str, 2);
            ft_putstr_fd(": numeric argument required\n", 2);
            exit (2);
		}	
	}
	return (stock * sign);
}

int exec_exit(t_cmd *cmd, t_global_data *data, t_pid_data *pdata)
{
	long long value;
	int			status;
	
	data->status = 0;
	if (!cmd->argv[1])
	{
		status = data->status;
		free(pdata->pids);
		cleanup_pipes(pdata->pipefd, pdata->nb_cmd - 1);
		clear_env(pdata->gdata->envp);
		free(pdata);
		free(data);
		free_cmd_list(cmd);
		exit (status);
	}
	else if (cmd->argv[2])
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	else if (cmd->argv[1])
	{	
		if (!is_numeric(cmd->argv[1])) 
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(cmd->argv[1] , 2);
			ft_putstr_fd(": numeric argument required", 2);
			exit(2);
		}
		value = ft_atoll(cmd->argv[1]);
        data->status = (int)value;	
	}
	status = data->status;
	free(pdata->pids);
	cleanup_pipes(pdata->pipefd, pdata->nb_cmd - 1);
	clear_env(pdata->gdata->envp);
	free(pdata);
	free(data);
	free_cmd_list(cmd);
	exit (status);
}
