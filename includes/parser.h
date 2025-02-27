/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:55:12 by rraumain          #+#    #+#             */
/*   Updated: 2025/02/27 20:34:00 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

//	UTILS
t_cmd	*create_cmd(void);
void	free_redir_list(t_redir *redir);
void	free_cmd_list(t_cmd *head);
int		add_redir(t_cmd *cmd, t_redir_type type, const char *filename);
int		add_current_argv(char **new_argv, int index, const char *word);

//	PARSER
t_cmd	*parse_line(t_token *tokens);

#endif