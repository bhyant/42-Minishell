# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/10 12:29:58 by tbhuiyan          #+#    #+#              #
#    Updated: 2025/11/26 06:14:25 by tbhuiyan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    := minishell
CC      := cc
CFLAGS  := -Wall -Werror -Wextra -g3
MAKE    := make
LIBFT_NAME := libft.a
LIBFT_DIR  := ./libft

# Directories
SRCS_DIR := ./srcs
OBJS_DIR := ./.objs

# Sources
SRCS = minishell.c \
       signal/signal.c \
       lexer/check_syntax.c \
       lexer/syntax_utils.c \
       parsing/parsing.c \
       parsing/tokenisation.c \
       parsing/tokenisation_utils.c \
       parsing/expand.c \
	   parsing/quotes.c \
       parsing/init_command.c \
       utils/env_utils.c \
       utils/env_list.c \
       utils/cleanup.c \
       utils/lst_token.c \
       utils/expand_utils.c \
       utils/command_utils.c \
       exec/exec.c \
       built_in/cd.c \
       built_in/pwd.c \
       built_in/export.c \
       built_in/unset.c \
       built_in/env.c \
       built_in/echo.c \
       built_in/exit.c

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
TOTAL := $(words $(SRCS))

all: $(NAME)

$(LIBFT_DIR)/$(LIBFT_NAME):
	@$(MAKE) -C $(LIBFT_DIR) all

$(NAME): $(LIBFT_DIR)/$(LIBFT_NAME) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)/$(LIBFT_NAME) -o $(NAME) -lreadline
	@printf "\n\033[0;32m✔ Compilation terminée avec succès\n✔ A toi de jouer !\033[0m\n"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@COUNT=$$(find $(OBJS_DIR) -name "*.o" 2>/dev/null | wc -l); \
	PERCENT=$$(echo "$$COUNT * 100 / $(TOTAL)" | bc 2>/dev/null || echo "0"); \
	BARS=$$(echo "$$PERCENT / 5" | bc 2>/dev/null || echo "0"); \
	LINE=$$(printf "%0.s█" $$(seq 1 $$BARS 2>/dev/null || echo "")); \
	SPACES=$$(printf "%0.s " $$(seq $$BARS 19 2>/dev/null || echo "")); \
	printf "\r\033[0;36m[%-20s] %3s%%\033[0m" "$$LINE$$SPACES" "$$PERCENT"

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
