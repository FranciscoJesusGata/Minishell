/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 14:46:18 by fgata-va          #+#    #+#             */
/*   Updated: 2021/05/24 09:53:55 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "minishell.h"

typedef struct s_hist
{
	char			*command;
	char			*replica;
	struct s_hist	*next;
	struct s_hist	*prev;
}					t_hist;

typedef struct s_term
{
	char			buffer[2048];
	char			*cursor;
	char			*termcap;
	t_hist			*history;
	t_hist			*h_cursor;
	struct termios	config;
	struct termios	backup;
}					t_term;

#endif
