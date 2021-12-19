# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/19 10:34:45 by fgata-va          #+#    #+#              #
#    Updated: 2021/12/19 22:16:14 by fgata-va         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := gcc

CFLAGS := -Wall -Werror -Wextra -I ./includes/ \
-I/Users/$(USER)/.brew/opt/readline/include -g

NAME := minishell

OBJDIR := build
SRCDIR := src
LIBDIR := libs/

SRC := $(addprefix $(SRCDIR)/, main.c terminal.c utils1.c utils2.c term_utils.c lexer.c \
	  lexer_status.c lexer_utils.c lexer_utils2.c token_manager.c parser.c cmd_manager_1.c \
	  cmd_manager_2.c redir_manager.c init_env.c executor.c ft_pwd.c ft_env.c ft_echo.c \
	  ft_export.c ft_export2.c ft_export3.c ft_unset.c ft_cd.c ft_cd2.c ft_cd3.c ft_exit.c builtins_utils.c \
	  signs.c io_management.c executor_utils_1.c launch_commands.c)

OBJS :=  $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SRC:.c=.o))

NORMI = norminette

LIBFT = -L $(LIBDIR)Libft -lft

READLINE := -lreadline -L /Users/$(USER)/.brew/opt/readline/lib

all: $(NAME)

$(NAME): libft $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(READLINE)

echo:
	echo $(OBJDIR)
	echo $(SRC)
	echo $(OBJS)

$(OBJDIR):
	mkdir $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

norm:
	-$(NORMI) $(SRC)
	-$(NORMI) includes/
	-$(NORMI) $(LIBDIR)Libft/

libft:
	make -C $(LIBDIR)Libft/ bonus

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C $(LIBDIR)Libft clean

fclean: clean
	$(MAKE) -C $(LIBDIR)Libft fclean
	rm -f $(NAME) $(NAME).dSYM

re: fclean all

.PHONY: all clean fclean re libft
