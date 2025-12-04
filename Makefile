# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asmati <asmati@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/29 18:47:23 by tbhuiyan          #+#    #+#              #
#    Updated: 2025/12/03 23:32:33 by asmati           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Wextra 
DEPFLAGS    = -MMD -MP

SRC_DIR     = srcs
OBJ_DIR     = .objs
INC_DIR     = includes
LIBFT_DIR   = libft

LIBFT       = $(LIBFT_DIR)/libft.a
LIBS        = -L$(LIBFT_DIR) -lft -lreadline
INCLUDES    = -I$(INC_DIR) -I$(LIBFT_DIR)/includes

SRCS        = $(shell find $(SRC_DIR) -name '*.c')
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
