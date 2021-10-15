/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 09:18:14 by fportalo          #+#    #+#             */
/*   Updated: 2021/10/15 12:46:59 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <term.h>
# include "structs.h"

int		main();
int		launch_term(void);
void	minishell(void);

/*
** Utils
*/

int		ft_putchar(int c);
int		ft_strcmp(const char *s1, const char *s2);

/*
** Term utils
*/

void	prompt(int exit_code);
void	sound_bell(void);
void	welcome(void);
void	clear_line(t_term *term);
void	clean_screen(void);

/*
** History handling
*/

void	free_history(t_hist *history);
void	restore_position(t_hist **history);
t_hist	*ft_dlstnew(char const *command);
void	ft_dlst_prepend(t_hist *current, t_hist *new_element);
void	restore_original(t_hist *history);
void	write_buffer(char **buffer, char input);
void	delete_buffer(char **buffer);
void	save_command(t_term *term, char *command);
void	navigate_history(t_term *term, int dir);
void	print_history(t_hist *history);

#endif
