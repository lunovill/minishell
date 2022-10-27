/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:16:56 by skhali            #+#    #+#             */
/*   Updated: 2022/10/21 13:17:14 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_front(t_command **alst, t_command *tmp)
{
	if (*alst)
	{
		tmp->next = *alst;
		*alst = tmp;
	}
	else
		*alst = tmp;
}

void	ft_lstadd_front2(t_partition **alst, t_partition *tmp)
{
	if (*alst)
	{
		tmp->next = *alst;
		*alst = tmp;
	}
	else
		*alst = tmp;
}

void	ft_lstadd_back3(t_command **alst, t_command *new)
{
	t_command	*copy;

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

void	ft_lstadd_back2(t_partition **alst, t_partition *new)
{
	t_partition	*copy;

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
