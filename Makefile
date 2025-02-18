# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/15 14:42:57 by rraumain          #+#    #+#              #
#    Updated: 2025/02/16 23:50:17 by rraumain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LEXER_SRC = lexer/lexer.c lexer/token.c lexer/utils.c lexer/parse.c
UTILS_SRC = utils/string.c

SRC = $(addprefix src/, main.c $(LEXER_SRC) $(UTILS_SRC))

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

LIBS = -lreadline
INCLUDES = -Iincludes

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re