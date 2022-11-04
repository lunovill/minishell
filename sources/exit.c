/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:08:21 by skhali            #+#    #+#             */
/*   Updated: 2022/10/26 16:57:44 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exit_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == '+' || str[i] == '-'))
		i++;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i])
		return (1);
	return (0);
}

//vérifier si les args sont numeric
//vérifier si il y a plusieurs arguemnts
//vérifier si une seule commande
int	built_in_exit(t_minishell *ms, char **cmd, int child)
{
	int	code;

	if (!child)
		ft_putstr_fd("exit\n", 1);
	if (size_chartab(cmd) == 1)
		return (free_minishell(ms), free_env(ms->env), free(ms), exit(g_status),
			g_status);
	if (check_exit_numeric(cmd[1]))
		return (ft_putstr_fd("exit: numeric argument required\n", 2),
			exit(2), 2);
	if (size_chartab(cmd) > 2)
		return (ft_putstr_fd("exit: too many arguments\n", 2), 1);
	code = ft_atoi(cmd[1]);
	return (free_minishell(ms), free_env(ms->env), free(ms),
		exit(code), 0);
}
