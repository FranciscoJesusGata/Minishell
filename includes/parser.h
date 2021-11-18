/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 12:18:35 by fgata-va          #+#    #+#             */
/*   Updated: 2021/11/18 11:57:50 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

t_cmd		*parser(t_list *tokens);

/*
** Commands and redirections management
*/
void	add_cmd(t_list **args, int argc, t_simpleCmd **cmds, int *count);
void	add_arg(t_list **args, char *word);
int		add_redir(t_list *tokens, t_redir **redirs);
void	delete_cmd(t_cmd **cmd);
void	print_cmd(t_cmd *cmd);
#endif
