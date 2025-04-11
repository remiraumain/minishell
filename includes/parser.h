/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:55:12 by rraumain          #+#    #+#             */
/*   Updated: 2025/04/11 11:32:41 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

//	UTILS
t_cmd	*create_cmd(int index);
void	free_redir_list(t_redir *redir);
void	free_cmd_list(t_cmd *head);
int		add_current_argv(char **new_argv, int index, const char *word);

//	PARSER
t_cmd	*parse_line(t_token *tokens);
int		add_argv(t_cmd *cmd, const char *word);

// UTILS2.C
int		add_redir(t_cmd *cmd, t_redir_type type, char *filename, int index);

#endif