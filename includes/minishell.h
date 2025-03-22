/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 08:51:33 by rraumain          #+#    #+#             */
/*   Updated: 2025/03/22 11:11:13 by nolecler         ###   ########.fr       */
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
# include <signal.h>
# include <sys/ioctl.h>

# include "libft.h"

# include "types.h"
# include "signals.h"
# include "utils.h"
//# include "string.h"//a enlever??
# include "lexer.h"
# include "parser.h"
# include "builtin.h"
# include "execution.h"

#endif