/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 09:18:14 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/09 12:29:38 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include "structs.h"
# include "lexer.h"
# include "parser.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>

# define WORD 61
# define LESS 60
# define GREAT 62
# define DLESS 120
# define DGREAT 121
# define PIPE 124

char	*launch_term(void);
t_list	*lexer(char *line);

/*
** Utils
*/

void	malloc_error(void);

/*
** Term utils
*/

void	welcome(void);

#endif
