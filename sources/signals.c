/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:19:04 by skhali            #+#    #+#             */
/*   Updated: 2022/11/06 20:00:25 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ctrl_c_heredoc(int sig)
{
	(void)sig;
	close(0);
	ft_printf("\n");
	g_status = -42;
}

void	ctrl_c(int sig)
{
	(void)sig;
	g_status = 130;
	ft_putstr_fd("\n", 2);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_signals_heredoc(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c_heredoc);
}

void	handle_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c);
}

void	reset_signals(t_minishell *data)
{
	(void)data;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
