# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgata-va <fgata-va@student.42madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/19 10:34:45 by fgata-va          #+#    #+#              #
#    Updated: 2021/10/14 16:11:47 by fgata-va         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := gcc

CFLAGS := -Wall -Werror -Wextra -I ./includes/ -g

NAME := minishell

OBJDIR := build/
SRCDIR := src/
LIBDIR := libs/

SRC = $(addprefix $(SRCDIR), main.c terminal.c term_utils.c term_utils_2.c history_utils.c \
	history_handle.c utils_1.c)

OBJS =  $(patsubst $(SRCDIR)%,$(OBJDIR)%,$(SRC:.c=.o))

NORMI = norminette

LIBFT = -L $(LIBDIR)Libft -lft

TERMCAPS = -ltermcap

all: $(NAME)

$(OBJDIR):
	mkdir $@

$(OBJDIR)%.o: $(SRCDIR)%.c $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): libft $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(TERMCAPS)

norm:
	$(NORMI) $(SRCDIR)$(SRC)
	$(NORMI) $(LIBDIR)Libft/

libft:
	make -C $(LIBDIR)Libft/ all

clean:
	@rm -rf $(OBJDIR)$(OBJS)
	$(MAKE) -C $(LIBDIR)Libft clean

fclean: clean
	$(MAKE) -C $(LIBDIR)Libft fclean
	@rm -f $(NAME) $(NAME).dSYM

re: fclean all

.PHONY: all clean fclean re libft
