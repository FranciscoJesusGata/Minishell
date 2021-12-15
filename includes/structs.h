/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:22:45 by fgata-va          #+#    #+#             */
/*   Updated: 2021/12/15 12:08:45 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "minishell.h"

/*
**		[ Lexer Structs ]
*/
typedef struct s_token
{
	int			type;
	char		*word;
	int			quoted;
}				t_token;

typedef struct s_lexer {
	int			start;
	int			end;
	int			quoted;
	int			expand;
	char		*buffer;
	t_list		*tokens;
}				t_lexer;

/*
**		[ Parser Structs ]
*/
typedef struct s_redir {
	int				type;
	char			*path;
	struct s_redir	*nxt;
}				t_redir;

typedef struct s_simpleCmd {
	char				**argv;
	int					argc;
	pid_t				pid;
	int					fds[2];
	int					*prev;
	t_redir				*redirs;
	struct s_simpleCmd	*nxt;
}				t_simpleCmd;

typedef struct s_cmd {
	int			count;
	t_simpleCmd	*cmds;
}				t_cmd;

typedef struct s_parser {
	t_list		*args;
	t_redir		*redirs;
	int			argc;
	int			type;
}				t_parser;

#endif
