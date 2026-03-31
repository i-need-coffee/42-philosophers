# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/24 11:39:14 by sjolliet          #+#    #+#              #
#    Updated: 2026/03/31 10:00:06 by sjolliet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g -pthread -Iinclude

SRC_DIR			= src
OBJ_DIR			= obj

SRCS			= \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/utils.c \
	$(SRC_DIR)/parsing.c

OBJS			= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "✅ Philo compiled successfully!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "🧹 Object files removed."

fclean: clean
	@rm -f $(NAME)
	@echo "🗑️  Library removed."

re: fclean all

.PHONY: all clean fclean re