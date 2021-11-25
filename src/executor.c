/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:08:07 by fportalo          #+#    #+#             */
/*   Updated: 2021/11/25 17:58:49 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	is_builtin(t_cmd *cmd, t_env *env)
{
	env = NULL;
	if (!ft_strncmp(cmd->cmds->argv[0], "pwd", 3))
		printf("executing pwd...\n");
	else if (!ft_strncmp(cmd->cmds->argv[0], "env", 3))
		printf("executing env...\n");
	else if (!ft_strncmp(cmd->cmds->argv[0], "echo", 4))
		printf("executing echo...\n");
	else if (!ft_strncmp(cmd->cmds->argv[0], "export", 6))
		printf("executing export...\n");
	else if (!ft_strncmp(cmd->cmds->argv[0], "unset", 5))
		printf("executing unset...\n");
	else if (!ft_strncmp(cmd->cmds->argv[0], "cd", 2))
		printf("executing cd...\n");
	else if(!ft_strncmp(cmd->cmds->argv[0], "exit", 4))
		printf("executing exit...\n");
}

void	executor(t_env *env, t_cmd *cmd)
{
	is_builtin(cmd, env);
}
