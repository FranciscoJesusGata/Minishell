/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 11:25:27 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/13 18:58:47 by fgata-va         ###   ########.fr       */
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
void	is_space(t_lexer *lexer, char *line);
int		is_squote(t_lexer *lexer, char *line);
int		is_dquote(t_lexer *lexer, char *line, char **env);
void	is_expand(t_lexer *lexer, char *line, char **env);
void	is_meta(t_lexer *lexer, char *line);

/*
** Utils functions
*/
void	ini_lexer(t_lexer *lexer);
char	*divide_str(char *line, int start, int end);
void	save_buffer(t_lexer *lexer, char *line);
void	concat(char **dst, char *src);
int		get_metatype(char *line, int start, int end);
char	*ft_getenv(char *search, char **env);
void	expand(t_lexer *lexer, char *line, char **env);
void	expand_exclamation(t_lexer *lexer);

/*
** Token management
*/
void	create_token(t_lexer *lexer, char *word, int type);
void	delete_token(void *tkn);
void	print_tokens(t_list *tokens);
#endif
