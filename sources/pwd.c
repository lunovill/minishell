/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:26:34 by skhali            #+#    #+#             */
/*   Updated: 2022/10/26 17:30:14 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//SI PWD existe deja -> renvois son contenu
//Si il est unset -> renvois el dossier dans Trash
//Parcourir env et chercher PWD
//si il existe afficher son contenu
//sinon, afficher le resultat de getcwd

char	*var_checker(t_env *env, char *str)
{
	while (env)
	{
		if ((!ft_strncmp(env->val, str, ft_strlen(str)))
			&& (env->val[ft_strlen(str)] == '='))
			return (env->val);
		env = env->next;
	}
	return (NULL);
}

void	longline(void)
{
	ft_putstr_fd("pwd: the current directory cannot be read\n", 2);
}

int	built_in_pwd(t_env *env, char **cmd)
{
	char	buf[PATH_MAX + 1];
	char	*pwd;
	char	*str;

	if (cmd[1] && !ft_strncmp(cmd[1], "-", 1))
		return (ft_putstr_fd("pwd: ", 2), write(2, cmd[1],
				ft_strlen(cmd[1])), ft_putstr_fd(": invalid option\n", 2), 2);
	str = var_checker(env, "PWD");
	pwd = getcwd(buf, sizeof(buf));
	if (!pwd)
	{
		if (str)
		{
			str = get_content(str);
			if (!str)
				return (longline(), 1);
			return (ft_printf("%s\n", ++str), 0);
		}
		else
			return (ft_putstr_fd("pwd : the current directory cannot be read\n"
					, 2), 1);
	}
	ft_printf("%s\n", buf);
	return (0);
}
