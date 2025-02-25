/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:02:58 by rraumain          #+#    #+#             */
/*   Updated: 2025/02/25 15:11:18 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef enum e_token_type
{
	TK_WORD,
	TK_PIPE,
	TK_REDIR_IN,
	TK_REDIR_OUT,
	TK_REDIR_APPEND,
	TK_HEREDOC,
	TK_EOF
}	t_token_type;

typedef enum e_bool
{
	true,
	false
}	t_bool;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

t_token			*lexer(char *input, t_global_data *data);

//	PARSE
int				parse_redirect(t_token **head, int *index, char *input);
// int				parse_quotes(t_token **head, int *index, char *input);
int				parse_word(t_token **head, int *index, char *input, t_global_data *data);

//	TOKENS
t_token			*create_token(t_token_type type, char *value);
void			add_token(t_token **head, t_token *new_token);
void			free_token_list(t_token *head);

//	EXPANDER
char			*expand_var(char *token, int *index, t_global_data *data);

//	UTILS
char			*read_word_and_expand(const char *input, int *index, t_global_data *data);
char			*read_quoted(const char *input, int *index, char quote);
t_token_type	check_redir(const char *input, int *index);

#endif