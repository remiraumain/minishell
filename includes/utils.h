/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:32:33 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/18 18:59:24 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef STRING_H
# define STRING_H

# include "minishell.h"

//	STRING
int		is_whitespace(char c);
int		ft_strcmp(char *s1, char *s2);
void	ft_envpadd_back(t_envp **lst, t_envp *new);
char	*ft_strndup(char *s, size_t n);

//	ENV_UTILS
void	clear_env(t_envp *envp);
void	clear_env_array(char **envp);
int		ft_envlen(t_envp *envp);
t_envp	*ft_lastenv(t_envp *envp);

//	ENV
t_envp	*init_env(char **envp);
char	**convert_env(t_envp *envp);

#endif