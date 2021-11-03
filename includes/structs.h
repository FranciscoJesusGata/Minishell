/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:22:45 by fgata-va          #+#    #+#             */
/*   Updated: 2021/11/03 13:24:24 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUTCS_H
# define STRUTCS_H
# include "minishell.h"

typedef struct	s_token
{
	int			type;
	char		*word;
}				t_token;

typedef struct	s_lexer {
	int			start;
	int			end;
	char		*buffer;
	t_list		*tokens;
}				t_lexer;

#endif
