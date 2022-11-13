/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 20:05:12 by skhali            #+#    #+#             */
/*   Updated: 2022/11/06 20:00:14 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//si le temps : modifier la valeur de _ en env
//display error si un argument est entré
int	built_in_env(t_env *env, char **cmd)
{
	if (cmd[1])
		return (ft_putstr_fd("env: ", 2), write(2, cmd[1],
				ft_strlen(cmd[1])), ft_putstr_fd(": no such file or directory.\n"
				, 2), 127);
	while (env)
	{
		ft_printf("%s\n", env->val);
		env = env->next;
	}
	return (0);
}
