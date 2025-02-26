/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:42:58 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/26 09:08:40 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifndef BUILTIN_H
# define BUILTIN_H

/* UTILS*/
int	ft_strcmp(char *s1, char *s2);

int is_builtin(t_cmd *cmd);
int exec_builtin(t_cmd *cmd);
int exec_echo(t_cmd *cmd);














#endif 