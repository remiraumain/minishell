# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/15 14:42:57 by rraumain          #+#    #+#              #
#    Updated: 2025/02/19 00:26:38 by rraumain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LEXER_SRC = lexer/lexer.c lexer/token.c lexer/utils.c lexer/parse.c
PARSER_SRC = parser/parser.c parser/utils.c
UTILS_SRC = utils/string.c

SRC = $(addprefix src/, main.c $(LEXER_SRC) $(PARSER_SRC) $(UTILS_SRC))

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