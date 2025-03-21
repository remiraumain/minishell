/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:20:03 by rraumain          #+#    #+#             */
/*   Updated: 2025/03/21 12:43:19 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "minishell.h"

#define INT_MAX 2147483647
#define INT_MIN -2147483648

//	GLOBAL
extern int	g_sig;

typedef struct s_envp
{
    char			*name;
    char			*value;
    int				pos;  // rang de la variable
    struct s_envp	*next;   
}	t_envp;

typedef struct s_global_data
{
	struct s_envp	*envp;
	int				status;
}	t_global_data;

typedef enum e_bool
{
	TRUE,
	FALSE
}	t_bool;

//	TOKENS

typedef enum e_token_type
{
	TK_WORD,
	TK_PIPE,
	TK_REDIR_IN,
	TK_REDIR_OUT,
	TK_REDIR_APPEND,
	TK_HEREDOC,
	TK_HEREDOC_QUOTES,
	TK_EOF
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

//	CMD

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_OUT_APPEND,
	REDIR_HEREDOC,
	REDIR_HEREDOC_Q
}	t_redir_type;

typedef struct s_redir
{
	int				index;
	t_redir_type	type;
	char			*filename;
	char			*delimeter;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	int				index;
	char			**argv;
	t_redir			*redir;
	struct s_cmd	*next;
}	t_cmd;

//	PIPES

typedef struct s_pid_data
{
	t_global_data	*gdata;
	int				nb_cmd;
	int				**pipefd;
	pid_t			*pids;
}	t_pid_data;

#endif