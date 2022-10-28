/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 20:05:01 by skhali            #+#    #+#             */
/*   Updated: 2022/10/29 01:26:15 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

//verifier les erreurs de parsing
//verfier la forme du export : =, +=, :=
int	is_valid(char c)
{
	return ((c <= 'Z' && c >= 'A') || (c <= 'z' && c >= 'a')
		|| (c <= '9' && c >= '0') || (c == '_'));
}

int	is_integer(char c)
{
	return (c <= '9' && c >= '0');
}

int	name_checker(char *cmd)
{
	int	i;

	i = 0;
	if (is_integer(cmd[i]) || (cmd[i] == '='))
		return (0);
	while (cmd[i] && (cmd[i] != '='))
	{
		if (!is_valid(cmd[i]))
			return (0);
		i++;
	}
	return (1);
}

int	built_in_export_p2(t_env *env, char *cmd)
{
	t_env	*tmp;

	tmp = env;
	while (env)
	{
		if (!ft_strncmp(env->val, cmd, get_var_length(env->val)))
		{
			free(env->val);
			env->val = ft_strdup(cmd);
			return (0);
		}
		env = env->next;
	}
	ft_lstadd_back(&tmp, ft_lstnew(cmd));
	return (0);
}

//si pas de = ajout à export
//sans argument renvois une liste
int	built_in_export(t_minishell *ms, t_env *env, char **cmd)
{
	int	i;
	int	exit_stat;

	i = 0;
	exit_stat = 0;
	while (cmd[++i])
	{
		if (!name_checker(cmd[i]))
		{
			ft_putstr_fd("export: ", 2);
			write(2, cmd[i], ft_strlen(cmd[i]));
			ft_putstr_fd(": not a valid identifier\n", 2);
			exit_stat = 1;
		}
		else
			built_in_export_p2(env, cmd[i]);
	}
	free(ms->char_env);
	ms->char_env = envlst_to_tab(ms->env);
	return (exit_stat);
}
