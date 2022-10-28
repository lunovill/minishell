/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:31:15 by skhali            #+#    #+#             */
/*   Updated: 2022/10/29 01:54:36 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	reset_signals(t_minishell *data)
{
	(void)data;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
