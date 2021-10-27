/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 11:25:27 by fportalo          #+#    #+#             */
/*   Updated: 2021/10/27 11:46:13 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "minishell.h"

# define SPACEX 32
# define DQUOTE 34
# define SQUOTE 39
# define XPAND 36

typedef struct	s_lexer {
	int			start;
	int			end;
	char		*buffer;
	t_list		*tokens;
}				t_lexer;


/*
** Status functions
*/
void	create_token(t_lexer *lexer, char *line);
void	is_space(t_lexer *lexer, char *line);
void	is_squote(t_lexer *lexer, char *line);


/*
** Utils functions
*/
char	*divide_str(char *line, int start, int end);
void	save_buffer(t_lexer *lexer, char *line);

#endif