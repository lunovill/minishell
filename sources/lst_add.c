/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunovill <lunovill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 01:33:00 by lunovill          #+#    #+#             */
/*   Updated: 2021/04/28 01:33:02 by lunovill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

int	lst_add(t_cmd *list, t_token *befor, t_token *add)
{
	t_token	*after;

	if (list == NULL)
		return (-1);
	add->previous = befor;
	if (befor == NULL)
	{
		add->next = list->first;
		list->first = add;
	}
	else
	{
		after = befor->next;
		befor->next = add;
		add->next = after;
	}
	if (add->next == NULL)
		list->last = add;
	list->size++;
	return (0);
}
