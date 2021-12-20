/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signs.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:51:46 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/19 22:40:32 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNS_H
# define SIGNS_H
# include "minishell.h"

void	handle_sigquit(int signo);
void	handle_sigint(int signo);
void	handle_heredoc(int signo);

#endif
