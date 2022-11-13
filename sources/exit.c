/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:08:21 by skhali            #+#    #+#             */
/*   Updated: 2022/11/07 19:00:02 by skhali           ###   ########.fr       */
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

int	built_in_exit(int *fd, t_minishell *ms, char **cmd, int child)
{
	int	code;

	if (!child)
		ft_putstr_fd("exit\n", 1);
	if (size_chartab(cmd) == 1)
		return (close(fd[1]), close(fd[0]), free_minishell(ms),
			free_env(ms->env), free_split(ms->char_env),
			free(ms), exit(g_status), g_status);
	if (check_exit_numeric(cmd[1]))
		return (ft_putstr_fd("exit: numeric argument required\n", 2),
			close(fd[1]), close(fd[0]), free_minishell(ms), free_env(ms->env),
			free_split(ms->char_env),
			free(ms), exit(2), 2);
	if (size_chartab(cmd) > 2)
		return (ft_putstr_fd("exit: too many arguments\n", 2), 1);
	code = ft_atoi(cmd[1]);
	return (close(fd[1]), close(fd[0]), free_minishell(ms), free_env(ms->env),
		free_split(ms->char_env), free(ms),
		exit(code), 0);
}
