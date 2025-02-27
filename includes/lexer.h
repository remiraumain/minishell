/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:02:58 by rraumain          #+#    #+#             */
/*   Updated: 2025/02/26 21:26:00 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

t_token			*lexer(char *input, t_global_data *data);

//	PARSE
int				parse_redirect(t_token **head, int *index, char *input);
int				parse_word(t_token **head, int *index, char *input,
					t_global_data *data);

//	TOKENS
t_token			*create_token(t_token_type type, char *value);
void			add_token(t_token **head, t_token *new_token);
void			free_token_list(t_token *head);

//	EXPANDER
void			expand_word(char **word, t_global_data *data);

//	VARS
char			*get_env_value(char *varname, char **envp);
char			*replace_var(char *token, int start, int varname_len,
					char *value);

//	UTILS
char			*read_word_and_expand(const char *input, int *index,
					t_global_data *data);
t_token_type	check_redir(const char *input, int *index);

#endif