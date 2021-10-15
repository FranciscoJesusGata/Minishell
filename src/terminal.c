/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 14:51:58 by fgata-va          #+#    #+#             */
/*   Updated: 2021/10/14 16:09:05 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_term(t_term *term)
{
	tgetent (term->buffer, getenv("TERM"));
	term->cursor = term->buffer;
	ft_bzero(&term->config, sizeof(struct termios));
	tcgetattr(STDIN_FILENO, &term->backup);
	term->config = term->backup;
	term->config.c_lflag &= ~(ICANON | ECHO);
	term->config.c_cc[VMIN] = 1;
	term->config.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term->config);
	tputs(tgetstr("ks", NULL), 1, ft_putchar);
	*term->buffer = 0;
	term->history = ft_dlstnew("");
	term->h_cursor = term->history;
	term->cursor = term->buffer;
}

void	test_commands(t_term *term)
{
	if (!(ft_strncmp(term->buffer, "welcome", 8)))
		welcome();
	if (!(ft_strncmp(term->buffer, "exit", 5)))
	{
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &term->backup);
		free_history(term->history);
		exit(0);
	}
	if (!(ft_strncmp(term->buffer, "history", 7)))
		print_history(term->history);
	if (!(ft_strncmp(term->buffer, "clear", 5)))
		clean_screen();
}

int	enter_command(t_term *term)
{
	write(1, "\r\n", 2);
	if (*term->buffer)
	{
		save_command(term, term->buffer);
		printf("\"%s\"\n", term->buffer);
		test_commands(term); //Aquí integras la función de Lexer
		term->cursor = term->buffer;
		*term->cursor = 0;
	}
	return (0);
}

int	launch_term(void)
{
	t_term	term;
	char	buff[9];
	int		readed;
	int		i;

	welcome();
	init_term(&term);
	prompt(0);
	readed = read(STDIN_FILENO, &buff, 8);
	while (readed > 0)
	{
		i = 0;
		while (i < readed)
		{
			if (buff[i] == '\n')
				prompt(enter_command(&term));
			else if (buff[i] == '\033')
			{
				if (!(ft_strncmp(buff + i, "\033OA", 3)))
					navigate_history(&term, 1);
				else if (!(ft_strncmp(buff + i, "\033OB", 3)))
					navigate_history(&term, 0);
				else
					sound_bell();
				break ;
			}
			else if (buff[i] == 127 && term.cursor != term.buffer)
				delete_buffer(&term.cursor);
			else if (buff[i] >= ' ' && buff[i] < 127)
				write_buffer(&term.cursor, buff[i]);
			else
				sound_bell();
			i++;
		}
		readed = read(STDIN_FILENO, &buff, 8);
	}
	free_history(term.history);
	return (0);
}
