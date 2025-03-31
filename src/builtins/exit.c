/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:04:44 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/31 16:07:46 by nolecler         ###   ########.fr       */
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


static void print_error_message(char *str)
{
	ft_putstr_fd("exit\n", 2);
    ft_putstr_fd("exit: ", 2);
    ft_putstr_fd(str, 2);
    ft_putstr_fd(": numeric argument required\n", 2);
}

static long long ft_atoll_convert(char *str, int *sign)
{
    int i;
    unsigned long long stock;
	
	i = 0;
	stock = 0;
    while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
        i++;
    while (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            *sign = *sign * -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        stock = (stock * 10) + (str[i] - '0');
        i++;
    }
    return (stock);
}

static long long ft_atoll(char *str)
{
    unsigned long long stock;
    int sign;
	
	sign = 1;
    stock = ft_atoll_convert(str, &sign);
    if (sign == -1)
    {
        if (stock > (unsigned long long)LLONG_MAX + 1)
        {
            print_error_message(str);
            exit(2);
        }
    }
    else if (sign == 1)
    {
        if (stock > LLONG_MAX)
        {
            print_error_message(str);
            exit(2);
        }
    }
    return (stock * sign);
}


static void cleanup(t_global_data *data, t_pid_data *pdata, t_cmd *head)// voir execute_child
{
	free(pdata->pids);
	cleanup_pipes(pdata->pipefd, pdata->nb_cmd - 1);
	clear_env(pdata->gdata->envp);
	free(pdata);
	free(data);
	free_cmd_list(head);
}


// int exec_exit(t_cmd *cmd, t_global_data *data, t_pid_data *pdata, t_cmd *head)
// {
// 	long long value;
	
// 	data->status = 0;
// 	if (!cmd->argv[1])
// 	{
// 		ft_putstr_fd("exit\n", 2);
// 		cleanup(data, pdata, head);
// 		exit (data->status);
// 	}
// 	else if (is_numeric(cmd->argv[1]) && cmd->argv[2])
// 	{
// 		ft_putstr_fd("exit\n", 2);
//     	ft_putstr_fd("exit:", 2);
//     	ft_putstr_fd(" too many arguments\n", 2);
// 		data->status = 1;
// 		return (data->status);
// 	}
// 	else
// 	{	
// 		if (!is_numeric(cmd->argv[1])) 
// 		{
// 			print_error_message(cmd->argv[1]);
// 			data->status = 2;
// 			//cleanup ?? 
// 			exit(data->status);
// 		}
// 		value = ft_atoll(cmd->argv[1]);
//         data->status = (int)value;	
// 	}
// 	cleanup(data, pdata, head);
// 	exit (data->status);
// }


static void    exit_no_args(t_global_data *data, t_pid_data *pdata, t_cmd *head)
{
    ft_putstr_fd("exit\n", 2);
    int status = data->status;
    cleanup(data, pdata, head);
    exit(status);
}

static void    exit_invalid_numeric(char *arg, t_global_data *data, t_pid_data *pdata, t_cmd *head)
{
    print_error_message(arg);
    data->status = 2;
    cleanup(data, pdata, head);
    exit(2);
}


int exec_exit(t_cmd *cmd, t_global_data *data, t_pid_data *pdata, t_cmd *head)
{
    long long value;

    data->status = 0;
    if (!cmd->argv[1])
        exit_no_args(data, pdata, head);
    else if (is_numeric(cmd->argv[1]) && cmd->argv[2])
    {
        ft_putstr_fd("exit\n", 2);
        ft_putstr_fd("exit: too many arguments\n", 2);
        return (1);
    }
    else
    {    
        if (!is_numeric(cmd->argv[1])) 
            exit_invalid_numeric(cmd->argv[1], data, pdata, head);
        value = ft_atoll(cmd->argv[1]);
        data->status = (int)value;
    }
    int status = data->status;
    cleanup(data, pdata, head);
    exit(status);
}
