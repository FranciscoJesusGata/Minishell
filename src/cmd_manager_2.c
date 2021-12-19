/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:23:39 by fgata-va          #+#    #+#             */
/*   Updated: 2021/12/19 22:16:31 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_arg(t_parser *parser, char *word)
{
	t_list	*new;

	new = ft_lstnew(word);
	if (!new)
		malloc_error();
	ft_lstadd_back(&parser->args, new);
	parser->argc++;
}

void	delete_matrix(char **matrix, int lines)
{
	int	i;

	i = 0;
	while (i < lines)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	delete_matrix(char **matrix, int lines)
{
	int	i;

	i = 0;
	while (i < lines)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	delete_redirs(t_redir *redirs)
{
	t_redir	*nxt;

	while (redirs)
	{
		nxt = redirs->nxt;
		free(redirs->path);
		free(redirs);
		redirs = nxt;
	}
}
