/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:22:45 by fgata-va          #+#    #+#             */
/*   Updated: 2021/11/18 15:45:54 by fgata-va         ###   ########.fr       */
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
	char		*buffer;
	t_list		*tokens;
}				t_lexer;

/*
**		[ Parser Structs ]
*/
typedef struct s_simpleCmd {
	char	**argv;
	int		argc;
	pid_t	pid;
	t_redir		*redirs;
	struct s_simpleCmd	*nxt;
}				t_simpleCmd;

typedef struct s_redir {
	int		type;
	char	*path;
	struct s_redir	*nxt;
}				t_redir;

typedef struct s_cmd {
	int			count;
	t_simpleCmd	*cmds;
}				t_cmd;

#endif
