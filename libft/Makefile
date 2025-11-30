# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asmati <asmati@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/12 00:46:53 by tbhuiyan          #+#    #+#              #
#    Updated: 2025/11/30 16:55:34 by asmati           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= libft.a

CC				= cc
CFLAGS			= -Wall -Wextra -Werror
DEPFLAGS		= -MMD -MP
AR				= ar rcs
RM				= rm -f

OBJDIR			= .objs
INC_DIR			= includes
GNL_DIR			= 42-get_next_line
PRINTF_DIR		= 42-printf

SRCS_LIBFT		= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
				  ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
				  ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
				  ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
				  ft_strchr.c ft_strcmp.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
				  ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
				  ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c

SRCS_BONUS		= ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c \
				  ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c \
				  ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c

SRCS_GNL		= $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c \
				  $(GNL_DIR)/get_next_line_bonus.c $(GNL_DIR)/get_next_line_utils_bonus.c

SRCS_PRINTF		= $(PRINTF_DIR)/ft_printf.c $(PRINTF_DIR)/ft_convert.c \
				  $(PRINTF_DIR)/ft_convert2.c

ALL_SRCS		= $(SRCS_LIBFT) $(SRCS_BONUS) $(SRCS_GNL) $(SRCS_PRINTF)
OBJS			= $(ALL_SRCS:%.c=$(OBJDIR)/%.o)
DEPS			= $(ALL_SRCS:%.c=$(OBJDIR)/%.d)

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(DEPFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJDIR)/$(GNL_DIR)/%.o: $(GNL_DIR)/%.c | $(OBJDIR)/$(GNL_DIR)
	@$(CC) $(CFLAGS) $(DEPFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJDIR)/$(PRINTF_DIR)/%.o: $(PRINTF_DIR)/%.c | $(OBJDIR)/$(PRINTF_DIR)
	@$(CC) $(CFLAGS) $(DEPFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/$(GNL_DIR):
	@mkdir -p $(OBJDIR)/$(GNL_DIR)

$(OBJDIR)/$(PRINTF_DIR):
	@mkdir -p $(OBJDIR)/$(PRINTF_DIR)

-include $(DEPS)

clean:
	@$(RM) -r $(OBJDIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
