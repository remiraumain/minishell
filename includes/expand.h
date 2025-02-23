/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:47:31 by rraumain          #+#    #+#             */
/*   Updated: 2025/02/23 16:17:34 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "minishell.h"

//	EXPANDER
void	expand_tokens(t_token *tokens, char **envp, int *status);

//	VARS
char	*get_env_value(char *varname, char **envp);
char	*replace_var(char *token, int start, int varname_len, char *value);

#endif