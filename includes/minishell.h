/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 08:51:33 by rraumain          #+#    #+#             */
/*   Updated: 2025/04/11 09:50:47 by nolecler         ###   ########.fr       */
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
# include <sys/stat.h> // is_directory
# include <signal.h>
# include <sys/ioctl.h>
# include <stdbool.h>// a voir si on garde ou pas 
# include "libft.h"

# include "types.h"
# include "signals.h"
# include "utils.h"
# include "builtin.h"
# include "lexer.h"
# include "parser.h"
# include "execution.h"

#endif