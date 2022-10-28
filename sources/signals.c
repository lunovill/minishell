/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:19:04 by skhali            #+#    #+#             */
/*   Updated: 2022/10/29 01:54:45 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

static void	ctrl_c_heredoc(int sig)
{
	(void)sig;
	close(0);
	printf("\n");
	g_status = -42;
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

