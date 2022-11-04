/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mangement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:00:00 by skhali            #+#    #+#             */
/*   Updated: 2022/11/04 17:13:22 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoinms(char *s1, char *s2)
{
	char	*str;
	size_t	i;

	if (!s1)
	{
		s1 = malloc(sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s2) + ft_strlen(s1))
	{
		if (i < ft_strlen(s1))
			str[i] = s1[i];
		else
			str[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	str[ft_strlen(s2) + ft_strlen(s1)] = '\0';
	free(s1);
	return (str);
}

t_env	*ft_lstnew(char *value)
{
	t_env	*cell;

	cell = (t_env *)malloc(sizeof(t_env));
	if (!cell)
		return (NULL);
	cell->val = ft_strdup(value);
	cell->next = NULL;
	return (cell);
}

void	ft_lstadd_back(t_env **alst, t_env *new)
{
	t_env	*copy;

	if (!alst)
		return ;
	copy = *alst;
	if (!(*alst))
	{
		*alst = new;
		return ;
	}
	if (copy)
	{
		while (copy->next)
			copy = copy->next;
		copy->next = new;
	}
}

t_env	*create_env(char **env)
{
	char	buf[PATH_MAX + 1];
	char	*pwd;
	t_env	*tmp;
	int		i;

	tmp = NULL;
	getcwd(buf, sizeof(buf));
	pwd = ft_strjoin("PWD=", buf);
	if (!env[0])
	{
		ft_lstadd_back(&tmp, ft_lstnew("SHLVL=2"));
		ft_lstadd_back(&tmp, ft_lstnew(pwd));
		ft_lstadd_back(&tmp, ft_lstnew("_=./minishell"));
		return (tmp);
	}
	free(pwd);
	i = -1;
	while (env[++i])
		ft_lstadd_back(&tmp, ft_lstnew(env[i]));
	return (tmp);
}
