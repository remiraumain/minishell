/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:02:58 by rraumain          #+#    #+#             */
/*   Updated: 2025/04/18 14:59:16 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

t_token			*lexer(char *input, t_global_data *data);

//	PARSE
int				parse_redirect(t_token **head, int *index, char *input);
int				parse_word(t_token **head, char *input, int *index,
					t_global_data *data);

//	TOKENS
t_token			*create_token(t_token_type type, char *value);
void			add_token(t_token **head, t_token *new_token);
void			free_token_list(t_token *head);

//	EXPANDER
char			*expand_line(char *input, t_global_data *data);

// INIT
void			process_input(char *input, t_global_data *data);
t_global_data	*init_global_data(char **envp);
int				clean_exit(t_global_data *data);

//	VARS
char			*get_varname(char *input, int *i);
char			*get_var_value(char *varname, t_global_data *data);

//	QUOTES
char			*process_quoted_word(const char *input, int *index);
char			*process_unquoted_text(const char *input, int *index);

//	UTILS
char			*read_word(const char *input, int *index);
t_token_type	check_redir(const char *input, int *index);

//	UTILS2
int				is_stop_char(char c);
int				is_inset(char c, char *set);
void			copy_char(char **buffer, char c);
t_token			*tokenlast(t_token *token);
void			trim_whitespace(char **str);

#endif