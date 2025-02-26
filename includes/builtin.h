/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:42:58 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/26 14:15:55 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

/* UTILS*/
int	ft_strcmp(char *s1, char *s2);

int is_builtin(t_cmd *cmd);
void exec_builtin(t_cmd *cmd, t_global_data *data);
int exec_echo(t_cmd *cmd);













#endif 