/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 11:25:27 by fportalo          #+#    #+#             */
/*   Updated: 2021/11/03 13:31:14 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "minishell.h"

# define SPACEX 32
# define DQUOTE 34
# define EXPAND 36
# define SQUOTE 39

/*
** Status functions
*/
void	create_token(t_lexer *lexer, char *line);
void	is_space(t_lexer *lexer, char *line);
void	is_squote(t_lexer *lexer, char *line);
void	is_dquote(t_lexer *lexer, char *line);
void	is_expand(t_lexer *lexer, char *line);
void	is_meta(t_lexer *lexer, char *line);


/*
** Utils functions
*/
void	ini_lexer(t_lexer *lexer);
char	*divide_str(char *line, int start, int end);
void	save_buffer(t_lexer *lexer, char *line);
void	concat(char **dst, char *src);

#endif
