/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:51:51 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/01 18:58:23 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int is_numeric(char *str)
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

void print_error_message(char *str)
{
	ft_putstr_fd("exit\n", 2);
    ft_putstr_fd("exit: ", 2);
    ft_putstr_fd(str, 2);
    ft_putstr_fd(": numeric argument required\n", 2);
}

void cleanup(t_global_data *data, t_pid_data *pdata, t_cmd *head)// voir execute_child
{
	free(pdata->pids);
	cleanup_pipes(pdata->pipefd, pdata->nb_cmd - 1);
	clear_env(pdata->gdata->envp);
	free(pdata);
	free(data);
	free_cmd_list(head);
}


void  exit_no_args(t_global_data *data, t_pid_data *pdata, t_cmd *head)
{
	int status;
	
    ft_putstr_fd("exit\n", 2);
    status = data->status;
    cleanup(data, pdata, head);
    exit(status);
}

void  exit_invalid_numeric(char *arg, t_global_data *data, t_pid_data *pdata, t_cmd *head)
{
    print_error_message(arg);
    data->status = 2;
    cleanup(data, pdata, head);
    exit(2);
}

