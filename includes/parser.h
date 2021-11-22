/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 12:18:35 by fgata-va          #+#    #+#             */
/*   Updated: 2021/11/22 15:35:01 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

t_cmd	*parser(t_list *tokens);

/*
** Commands and redirections management
*/

int		add_cmd(t_parser *parser, t_cmd *cmd);
void	add_arg(t_parser *parser, char *word);
int		add_redir(t_list **tokens, t_redir **redirs);
void	delete_redirs(t_redir *redirs);
void	delete_cmd(t_cmd **cmd);
void	print_cmd(t_cmd *cmd);
void	parse_error(int token);
#endif
