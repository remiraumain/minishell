/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 08:51:33 by rraumain          #+#    #+#             */
/*   Updated: 2025/02/16 23:16:17 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "string.h"
# include "lexer.h"

typedef struct s_data
{
	char	**env;
}	t_data;

typedef struct s_cmd
{
	char			**argv;// Tableau d’arguments, ex: {"echo", "hello", NULL}
	t_redir			*redir;// Liste chaînée de redirections
	struct s_cmd	*next;// Commande suivante dans le pipeline
}	t_cmd;

#endif