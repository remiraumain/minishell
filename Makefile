# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/15 14:42:57 by rraumain          #+#    #+#              #
#    Updated: 2025/04/16 17:25:55 by rraumain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LEXER_SRC = $(addprefix lexer/, lexer.c token.c parse.c utils.c utils2.c expander.c vars.c init.c quotes.c)
PARSER_SRC = $(addprefix parser/, parser.c utils.c utils2.c)
EXEC_SRC = $(addprefix execution/, execution.c exec_utils1.c exec_utils2.c redirection.c path.c path_utils.c utils.c heredoc.c heredoc_utils.c)
BUILTIN_SRC = $(addprefix builtins/, builtin_control.c echo.c utils_cd.c utils2_cd.c cd.c pwd.c env.c exit.c unset.c export.c utils_export.c utils2_export.c utils_exit.c) 
SIGNALS_SRC = $(addprefix signals/, signal_handler.c signal_set.c)
UTILS_SRC = $(addprefix utils/, string.c env.c env_utils.c)

SRC = $(addprefix src/, main.c $(LEXER_SRC) $(PARSER_SRC) $(EXEC_SRC) $(BUILTIN_SRC) $(SIGNALS_SRC) $(UTILS_SRC))

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

LIBS = -L./libs/libft -lft -lreadline
INCLUDES = -Iincludes -Ilibs/libft

all: $(NAME)

$(NAME): $(OBJ) libs/libft/libft.a
	$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

libs/libft/libft.a:
	@$(MAKE) -C libs/libft

clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C libs/libft

fclean: clean
	rm -f $(NAME)
	@$(MAKE) fclean -C libs/libft

re: fclean all

.PHONY: all clean fclean re