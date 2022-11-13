/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 22:20:22 by skhali            #+#    #+#             */
/*   Updated: 2022/10/23 14:48:03 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return (1);
		s1++;
		s2++;
	}
	return (0);
}

t_env	*var_getter(t_env *env, char *str)
{
	while (env)
	{
		if ((!ft_strncmp(env->val, str, ft_strlen(str)))
			&& (env->val[ft_strlen(str)] == '='))
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	ft_del_lst_el(t_env **list, t_env *to_delete)
{
	t_env	*tmp;
	t_env	*tmp2;

	if (!list || !*list || !to_delete)
		return ;
	tmp = *list;
	if ((*list) == to_delete)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp->val);
		free(tmp);
		return ;
	}
	while (tmp->next && (tmp->next != to_delete))
		tmp = tmp->next;
	if (tmp->next)
	{
		tmp2 = tmp->next;
		tmp->next = tmp->next->next;
		free(tmp2->val);
		free(tmp2);
		return ;
	}
}

int	built_in_unset(t_minishell *ms, t_env **env, char **cmd)
{
	int	i;

	i = 0;
	while (cmd[++i])
	{
		if (var_checker(*env, cmd[i]))
		{
			ft_del_lst_el(env, var_getter(*env, cmd[i]));
			free_split(ms->char_env);
			ms->char_env = envlst_to_tab(ms->env);
		}
	}
	return (0);
}
