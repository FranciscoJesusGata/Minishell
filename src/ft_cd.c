/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fportalo <fportalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:17:46 by fportalo          #+#    #+#             */
/*   Updated: 2021/12/03 12:10:01 by fportalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	look_for_oldpwd(char **env)
{
	int i;
	char **split;

	i = 0;
	while (env[i])
	{
		split = ft_split(env[i], '=');
		if (!ft_strncmp(split[0], "OLDPWD", ft_strlen(split[0])))		// mirar esto
		{
			ft_freearray(split);
			return (0);
		}
		ft_freearray(split);
		i++;
	}
	return (1);
}

char	**create_oldpwd(char **env)
{
	int		i;
	char	cwd[PATH_MAX];
	char	**tmp;

	i = 0;
	getcwd(cwd, sizeof(cwd));
	tmp = ft_calloc(sizeof(char *), get_size(env) + 1);
	while (env[i])
	{
		tmp[i] = env[i];
		i++;
	}
	free(env);
	tmp[i] = ft_strdup("OLDPWD=");
	tmp[i] = clean_strjoin(tmp[i], cwd);
	tmp[i + 1] = NULL;
	return (tmp);

}

char	**edit_oldpwd(char **env)
{
	int		i;
	char	cwd[PATH_MAX];
	char	**tmp;
	char	**split;

	i = 0;
	getcwd(cwd, sizeof(cwd));
	tmp = ft_calloc(sizeof(char *), get_size(env) + 1);
	while (env[i])
	{
		if (!ft_strncmp(env[i], "OLDPWD=", ft_strlen("OLDPWD=")))		// mirar esto
		{
			split = ft_split(env[i], '=');
			tmp[i] = ft_strdup(split[0]);
			tmp[i] = clean_strjoin(tmp[i], "=");
			tmp[i] = clean_strjoin(tmp[i], cwd);
			ft_freearray(split);
			free(env[i]);
		}
		else
			tmp[i] = clean_strdup(env[i]);
		i++;
	}
	free(env);
	tmp[i] = NULL;
	return (tmp);
}

char	**home_to_pwd(char **env)
{
	int i;
	int j;

	i = 0;
	while(!ft_strncmp(env[i], "HOME=", ft_strlen("HOME="))			// mirar esto
	{

	}
}

void	ft_cd(int argc, char **argv, t_env *env)
{
	argv = NULL;
	if (argc > 1)
	{
		printf("hola\n");
	}
	else
	{
		if (look_for_oldpwd(env->all))				//if OLPDWD doesn't exist
			env->all = create_oldpwd(env->all);
		else										//if OlDPWD exist
			env->all = edit_oldpwd(env->all);
		env->all = home_to_pwd(env->all);
	}
	system("leaks minishell");
}
