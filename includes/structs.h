/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:22:45 by fgata-va          #+#    #+#             */
/*   Updated: 2021/11/05 13:35:30 by fportalo         ###   ########.fr       */
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
	char		*path;
	char		*shlvl;
}				t_env;

#endif
