/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgata-va <fgata-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 16:21:50 by fgata-va          #+#    #+#             */
/*   Updated: 2021/12/09 15:14:05 by fgata-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_error(void)
{
	perror("Error: dynamic allocation\n");
	exit(1);
}

void	print_redir(t_simpleCmd *cmd)
{
	t_redir	*r_iter;

	r_iter = cmd->redirs;
	printf("			redirections:\n");
	while (r_iter)
	{
		printf("				");
		if (r_iter->type < 77)
			printf("%c ", r_iter->type);
		else if (r_iter->type == DGREAT)
			printf(">> ");
		else
			printf("<< ");
		printf("%s\n", r_iter->path);
		r_iter = r_iter->nxt;
	}
}

void	print_argv(t_simpleCmd *cmd)
{
	int	i;

	i = 0;
	printf("			argc: %d\n", cmd->argc);
	printf("			argv: [");
	while (cmd->argv[i])
	{
		printf("\"%s\"", cmd->argv[i]);
		if (cmd->argv[i + 1])
			printf(", ");
		i++;
	}
	printf("]\n");
}

void	print_cmd(t_cmd *cmd)
{
	int			i;
	t_simpleCmd	*iter;

	printf("cmd	{\n");
	printf("	count = %d\n", cmd->count);
	printf("	cmds:\n");
	i = 0;
	iter = cmd->cmds;
	while (iter)
	{
		printf("		cmd%d:\n", i);
		print_argv(iter);
		print_redir(iter);
		iter = iter->nxt;
		i++;
	}
	printf("	}\n");
}

int	minishell_perror(int exit_code, char *name, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	if (name)
	{
		ft_putstr_fd(name, 2);
		write(2, ": ", 2);
	}
	else
		ft_putstr_fd("minishell: ", 2);
	if (msg)
		ft_putstr_fd(msg, 2);
	else
		ft_putstr_fd(strerror(errno), 2);
	write(1, "\n", 1);
	return (exit_code);
}
