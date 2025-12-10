# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/29 18:47:23 by tbhuiyan          #+#    #+#              #
#    Updated: 2025/12/10 15:35:28 by tbhuiyan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Wextra -Werror
DEPFLAGS    = -MMD -MP

SRC_DIR     = srcs
OBJ_DIR     = .objs
INC_DIR     = includes
LIBFT_DIR   = libft

LIBFT       = $(LIBFT_DIR)/libft.a
LIBS        = -L$(LIBFT_DIR) -lft -lreadline
INCLUDES    = -I$(INC_DIR) -I$(LIBFT_DIR)/includes

SRCS        = $(SRC_DIR)/minishell.c \
              $(SRC_DIR)/minishell_utils.c \
              $(SRC_DIR)/loop_helpers.c \
              $(SRC_DIR)/prompt.c \
              $(SRC_DIR)/built_in/cd.c \
              $(SRC_DIR)/built_in/echo.c \
              $(SRC_DIR)/built_in/env.c \
              $(SRC_DIR)/built_in/exit.c \
              $(SRC_DIR)/built_in/export.c \
              $(SRC_DIR)/built_in/export_utils.c \
              $(SRC_DIR)/built_in/pwd.c \
              $(SRC_DIR)/built_in/unset.c \
              $(SRC_DIR)/exec/exec_fonctions.c \
              $(SRC_DIR)/exec/child.c \
              $(SRC_DIR)/exec/parent.c \
              $(SRC_DIR)/exec/search_path.c \
              $(SRC_DIR)/exec/exec_pip.c \
              $(SRC_DIR)/exec/exec_redir.c \
              $(SRC_DIR)/exec/heredoc/heredoc.c \
              $(SRC_DIR)/exec/heredoc/heredoc_utils.c \
              $(SRC_DIR)/lexer/check_syntax.c \
              $(SRC_DIR)/lexer/syntax_helpers.c \
              $(SRC_DIR)/lexer/syntax_utils.c \
              $(SRC_DIR)/parsing/expand.c \
              $(SRC_DIR)/parsing/init_command.c \
              $(SRC_DIR)/parsing/parsing.c \
              $(SRC_DIR)/parsing/quotes.c \
              $(SRC_DIR)/parsing/tokenisation.c \
              $(SRC_DIR)/parsing/tokenisation_helpers.c \
              $(SRC_DIR)/parsing/tokenizer.c \
              $(SRC_DIR)/signal/signal.c \
              $(SRC_DIR)/utils/cleanup.c \
              $(SRC_DIR)/utils/command_utils.c \
              $(SRC_DIR)/utils/env_list.c \
              $(SRC_DIR)/utils/env_list2.c \
              $(SRC_DIR)/utils/env_utils.c \
              $(SRC_DIR)/utils/env_utils2.c \
              $(SRC_DIR)/utils/expand_utils.c \
              $(SRC_DIR)/utils/lst_token.c \
              $(SRC_DIR)/utils/quotes_utils.c \
              $(SRC_DIR)/utils/tokenisation_utils.c

OBJS        = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS        = $(OBJS:.o=.d)

RED         = \033[0;31m
GREEN       = \033[0;32m
YELLOW      = \033[0;33m
CYAN        = \033[0;36m
RESET       = \033[0m

PROGRESS_BAR_WIDTH = 50
TOTAL_FILES = $(words $(OBJS))
CURRENT_FILE = 0

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo ""
	@$(CC) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) created$(RESET)"

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE)+1))))
	@$(eval PERCENT=$(shell echo $$(($(CURRENT_FILE)*100/$(TOTAL_FILES)))))
	@$(eval FILLED=$(shell echo $$(($(CURRENT_FILE)*$(PROGRESS_BAR_WIDTH)/$(TOTAL_FILES)))))
	@printf "$(CYAN)[$(RESET)"
	@printf "$(GREEN)%*s" $(FILLED) | tr ' ' '='
	@printf "%*s" $$(($(PROGRESS_BAR_WIDTH)-$(FILLED))) | tr ' ' '-'
	@printf "$(CYAN)]$(RESET) $(YELLOW)%3d%%$(RESET) Compiling: $(notdir $<)   \r" $(PERCENT)
	@$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDES) -c $< -o $@

-include $(DEPS)

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "$(RED)✓ Objects cleaned$(RESET)"

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "$(RED)✓ Full clean done$(RESET)"

re: fclean all

.PHONY: all clean fclean re
