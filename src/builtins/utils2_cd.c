/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 10:04:55 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/05 10:37:53 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(char *argv)
{
	if (access(argv, F_OK) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	if (access(argv, X_OK) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": permission denied \n", 2);
		return (1);
	}
	if (chdir(argv) == -1)// cd Makefile message d erreur ici 
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": not a directory \n", 2);
		return (1);
	}
	return (0);
}

void free_path_pwd(char *path, char *pwd)
{
    free(path);
    free(pwd);
}