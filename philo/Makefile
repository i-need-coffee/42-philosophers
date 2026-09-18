# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shadya <shadya@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/24 11:39:14 by sjolliet          #+#    #+#              #
#    Updated: 2026/09/18 12:43:12 by shadya           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g -pthread -Iinclude

SRC_DIR			= src
OBJ_DIR			= obj

SRCS			= \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/parsing.c \
	$(SRC_DIR)/threads.c \
	$(SRC_DIR)/routine.c \
	$(SRC_DIR)/watcher.c \
	$(SRC_DIR)/utils/simulation.c \
	$(SRC_DIR)/utils/cleanup.c \
	$(SRC_DIR)/utils/ft_strlen.c \
	$(SRC_DIR)/utils/get_time_ms.c \
	$(SRC_DIR)/utils/throw_error.c \
	$(SRC_DIR)/utils/ft_usleep.c \
	$(SRC_DIR)/utils/print_status.c \
	$(SRC_DIR)/utils/routine_actions.c

OBJS			= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "✅ Philo compiled successfully!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "🧹 Object files removed."

fclean: clean
	@rm -f $(NAME)
	@echo "🗑️  Library removed."

re: fclean all

.PHONY: all clean fclean re