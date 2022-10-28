/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:26:52 by skhali            #+#    #+#             */
/*   Updated: 2022/10/23 14:51:42 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

int	builtins(t_minishell *ms, char **cmd, int child)
{
	if (!cmd[0])
		return (-1);
	if (!ft_strncmp(cmd[0], "echo", sizeof(cmd[0])))
		return (built_in_echo(cmd));
	else if (!ft_strncmp(cmd[0], "pwd", sizeof(cmd[0])))
		return (built_in_pwd(ms->env, cmd));
	else if (!ft_strncmp(cmd[0], "env", sizeof(cmd[0])))
		return (built_in_env(ms->env, cmd));
	else if (!ft_strncmp(cmd[0], "cd", 2))
		return (built_in_cd(ms->env, cmd));
	else if (!ft_strncmp(cmd[0], "export", sizeof(cmd[0])))
		return (built_in_export(ms->env, cmd));
	else if (!ft_strncmp(cmd[0], "unset", sizeof(cmd[0])))
		return (built_in_unset(&(ms->env), cmd));
	else if (!ft_strncmp(cmd[0], "exit", sizeof(cmd[0])))
		return (built_in_exit(ms, cmd, child));
	return (-1);
}