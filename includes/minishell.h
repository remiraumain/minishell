/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:32:19 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/26 11:00:39 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

# include "libft.h"

typedef struct s_global_data
{
	char	**envp;
	int		status;
}	t_global_data;

# include "string.h"
# include "lexer.h"
# include "expand.h"
# include "parser.h"
# include "builtin.h"
# include "execution.h"


#endif