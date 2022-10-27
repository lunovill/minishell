/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:31:15 by skhali            #+#    #+#             */
/*   Updated: 2022/10/26 17:31:54 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	ctrl_c_exec(int signum)
{
	(void)signum;
	ft_putchar_fd('\n', 2);
	g_status = 130;
}

void	reset_signals(t_minishell *data)
{
	(void)data;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_signals_exec(t_minishell *data)
{
	(void)data;
	signal(SIGQUIT, ctrl_back_slash);
	signal(SIGINT, ctrl_c_exec);
}
