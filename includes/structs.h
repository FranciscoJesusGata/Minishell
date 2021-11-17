/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:22:45 by fgata-va          #+#    #+#             */
/*   Updated: 2021/11/17 12:16:59 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "minishell.h"

/*
** LEXER STRUCTS
*/
typedef struct s_token
{
	int			type;
	char		*word;
}				t_token;

typedef struct s_lexer {
	int			start;
	int			end;
	char		*buffer;
	t_list		*tokens;
}				t_lexer;

/*
** ENV STRUCT
*/
typedef struct s_env {
	char		**envp;
	char		**all;
	char		*pwd;
	char		*old_pwd;
	char		**path;
	char		*shlvl;
	char		*home;
	char		*user;
	char		*last;
}				t_env;

#endif
