/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:32:04 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/26 08:40:30 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "minishell.h"

#ifndef EXPAND_H
# define EXPAND_H


//	EXPANDER
void	expand_tokens(t_token *tokens, char **envp, int *status);

//	VARS
char	*get_env_value(char *varname, char **envp);
char	*replace_var(char *token, int start, int varname_len, char *value);

#endif