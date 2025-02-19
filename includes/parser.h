/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:55:12 by rraumain          #+#    #+#             */
/*   Updated: 2025/02/19 18:17:07 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_OUT_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*filename;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redir;
	struct s_cmd	*next;
}	t_cmd;

//	UTILS
t_cmd	*create_cmd(void);
void	free_redir_list(t_redir *redir);
void	free_cmd_list(t_cmd *head);
int		add_redir(t_cmd *cmd, t_redir_type type, const char *filename);
int		add_current_argv(char **new_argv, int index, const char *word);

//	PARSER
t_cmd	*parse_line(t_token *tokens);

#endif