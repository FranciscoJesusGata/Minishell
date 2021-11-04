# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/19 10:34:45 by fgata-va          #+#    #+#              #
#    Updated: 2021/11/04 14:00:58 by fgata-va         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := gcc

CFLAGS := -Wall -Werror -Wextra -I ./includes/ \
-I/Users/$(USER)/.brew/opt/readline/include -g

NAME := minishell

OBJDIR := build/
SRCDIR := src/
LIBDIR := libs/

SRC = $(addprefix $(SRCDIR), main.c terminal.c term_utils.c lexer.c \
	  lexer_status.c lexer_utils.c token_manager.c)

OBJS =  $(patsubst $(SRCDIR)%,$(OBJDIR)%,$(SRC:.c=.o))

NORMI = norminette

LIBFT = -L $(LIBDIR)Libft -lft

READLINE = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib

all: $(NAME)

$(OBJDIR):
	mkdir $@

$(OBJDIR)%.o: $(SRCDIR)%.c $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): libft $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(READLINE)

norm:
	$(NORMI) $(SRC)
	$(NORMI) $(LIBDIR)Libft/

libft:
	make -C $(LIBDIR)Libft/ bonus

clean:
	rm -rf $(OBJS)
	$(MAKE) -C $(LIBDIR)Libft clean

fclean: clean
	$(MAKE) -C $(LIBDIR)Libft fclean
	rm -f $(NAME) $(NAME).dSYM

re: fclean all

.PHONY: all clean fclean re libft
