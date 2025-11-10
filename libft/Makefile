# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbhuiyan <tbhuiyan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/12 00:46:53 by tbhuiyan          #+#    #+#              #
#    Updated: 2025/07/12 00:59:50 by tbhuiyan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -MMD -I includes
AR			= ar rc
RM			= rm -f

# Colors
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
RED			= \033[0;31m
BLUE		= \033[0;34m
PURPLE		= \033[0;35m
CYAN		= \033[0;36m
RESET		= \033[0m

# ================================ DIRECTORIES ================================ #

OBJDIR		= .objs
INCDIR		= includes
GNL_DIR		= 42-get_next_line
PRINTF_DIR	= 42-printf

# ================================= SOURCES =================================== #

# Sources libft de base
SRCS_LIBFT	= ft_atoi.c \
			  ft_bzero.c \
			  ft_calloc.c \
			  ft_isalnum.c \
			  ft_isalpha.c \
			  ft_isascii.c \
			  ft_isdigit.c \
			  ft_isprint.c \
			  ft_itoa.c \
			  ft_memchr.c \
			  ft_memcmp.c \
			  ft_memcpy.c \
			  ft_memmove.c \
			  ft_memset.c \
			  ft_putchar_fd.c \
			  ft_putendl_fd.c \
			  ft_putnbr_fd.c \
			  ft_putstr_fd.c \
			  ft_split.c \
			  ft_strchr.c \
			  ft_strdup.c \
			  ft_striteri.c \
			  ft_strjoin.c \
			  ft_strlcat.c \
			  ft_strlcpy.c \
			  ft_strlen.c \
			  ft_strmapi.c \
			  ft_strncmp.c \
			  ft_strnstr.c \
			  ft_strrchr.c \
			  ft_strtrim.c \
			  ft_substr.c \
			  ft_tolower.c \
			  ft_toupper.c

# Sources bonus libft
SRCS_BONUS	= ft_lstadd_back_bonus.c \
			  ft_lstadd_front_bonus.c \
			  ft_lstclear_bonus.c \
			  ft_lstdelone_bonus.c \
			  ft_lstiter_bonus.c \
			  ft_lstlast_bonus.c \
			  ft_lstmap_bonus.c \
			  ft_lstnew_bonus.c \
			  ft_lstsize_bonus.c

# Sources get_next_line
SRCS_GNL	= $(GNL_DIR)/get_next_line.c \
			  $(GNL_DIR)/get_next_line_utils.c

# Sources get_next_line bonus
SRCS_GNL_BONUS = $(GNL_DIR)/get_next_line_bonus.c \
				 $(GNL_DIR)/get_next_line_utils_bonus.c

# Sources ft_printf
SRCS_PRINTF	= $(PRINTF_DIR)/ft_printf.c \
			  $(PRINTF_DIR)/ft_convert.c \
			  $(PRINTF_DIR)/ft_convert2.c

# Toutes les sources
SRCS		= $(SRCS_LIBFT) $(SRCS_GNL) $(SRCS_PRINTF)
SRCS_ALL_BONUS = $(SRCS_BONUS) $(SRCS_GNL_BONUS)

# ================================= OBJECTS =================================== #

OBJS		= $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
OBJS_BONUS	= $(addprefix $(OBJDIR)/, $(SRCS_BONUS:.c=.o))
OBJS_GNL_BONUS = $(addprefix $(OBJDIR)/, $(SRCS_GNL_BONUS:.c=.o))
OBJS_ALL	= $(OBJS) $(OBJS_BONUS) $(OBJS_GNL_BONUS)
DEPS		= $(OBJS_ALL:.o=.d)

INC			= $(INCDIR)/libft.h

# ================================== RULES ==================================== #

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(PURPLE)🔧 Création de la super libft...$(RESET)"
	@$(AR) $(NAME) $(OBJS)
	@echo "$(GREEN)✅ $(NAME) créée avec libft + GNL + printf !$(RESET)"

bonus: $(OBJS) $(OBJS_BONUS) $(OBJS_GNL_BONUS)
	@echo "$(YELLOW)🌟📖 Compilation complète avec tous les bonus...$(RESET)"
	@$(AR) $(NAME) $(OBJS) $(OBJS_BONUS) $(OBJS_GNL_BONUS)
	@echo "$(GREEN)🎉🎉 Super libft COMPLÈTE avec tous les bonus !$(RESET)"

$(OBJDIR):
	@echo "$(CYAN)📁 Création du dossier objets...$(RESET)"
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/$(GNL_DIR)
	@mkdir -p $(OBJDIR)/$(PRINTF_DIR)

$(OBJDIR)/%.o: %.c $(INC) | $(OBJDIR)
	@echo "$(CYAN)⚙️  Compilation de $< → $@...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# ================================= CLEANING ================================== #

clean:
	@echo "$(RED)🧹 Nettoyage du dossier objets...$(RESET)"
	@$(RM) -r $(OBJDIR)
	@echo "$(GREEN)✨ Dossier $(OBJDIR) supprimé !$(RESET)"

fclean: clean
	@echo "$(RED)🗑️  Suppression de $(NAME)...$(RESET)"
	@$(RM) $(NAME)
	@$(RM) test_libft test_gnl test_printf
	@echo "$(GREEN)🎯 Nettoyage complet terminé !$(RESET)"

re: fclean
	@echo "$(BLUE)🔄 Reconstruction de la super libft...$(RESET)"
	@$(MAKE) all

# ================================= STATUS ==================================== #

status:
	@echo "$(CYAN)📊 État de la compilation :$(RESET)"
	@echo "  $(GREEN)Fichiers libft :$(RESET) $(words $(SRCS_LIBFT)) fonctions"
	@echo "  $(GREEN)Fichiers bonus :$(RESET) $(words $(SRCS_BONUS)) fonctions"
	@echo "  $(GREEN)Fichiers GNL :$(RESET) $(words $(SRCS_GNL)) fonctions"
	@echo "  $(GREEN)Fichiers printf :$(RESET) $(words $(SRCS_PRINTF)) fonctions"
	@echo "  $(PURPLE)Total :$(RESET) $(words $(SRCS)) fonctions de base"
	@if [ -f $(NAME) ]; then echo "  $(GREEN)✅ $(NAME) existe$(RESET)"; else echo "  $(RED)❌ $(NAME) n'existe pas$(RESET)"; fi

# ================================= HELP ===================================== #

help:
	@echo "$(CYAN)📖 Super Libft - Commandes disponibles :$(RESET)"
	@echo "  $(GREEN)make$(RESET)           - Compile libft + GNL + printf"
	@echo "  $(GREEN)make bonus$(RESET)- Compile avec TOUS les bonus"
	@echo "  $(GREEN)make status$(RESET)     - Affiche l'état de la compilation"
	@echo "  $(GREEN)make clean$(RESET)      - Supprime les fichiers objets"
	@echo "  $(GREEN)make fclean$(RESET)     - Nettoyage complet"
	@echo "  $(GREEN)make re$(RESET)         - Reconstruction complète"
	@echo "  $(GREEN)make help$(RESET)       - Affiche cette aide"

# ================================= PHONY ==================================== #

.PHONY: all bonus clean fclean re status help

# ============================== DEPENDENCIES =============================== #

-include $(DEPS)