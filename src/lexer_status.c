/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 11:43:24 by fportalo          #+#    #+#             */
/*   Updated: 2021/10/26 12:57:48 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	is_space(t_lexer *lexer, char *line)
{
	create_token(lexer, line);
	lexer->end += 1;
	lexer->start = lexer->end;
}

//void	is_squote(char *line, int *start, int *end)
//{
//	*start++;
//	while(line[*end] != SQUOTE)
//	{
//		//if (line[*end] != )
//	}
//}
