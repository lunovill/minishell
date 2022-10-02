/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_rmv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunovill <lunovill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 01:36:51 by lunovill          #+#    #+#             */
/*   Updated: 2021/04/28 01:37:18 by lunovill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

int	lst_rmv(t_cmd *list, t_token *remove)
{
	t_token	*previous;

	if (list == NULL || remove == NULL)
		return (-1);
	if (remove == list->first)
		list->first = list->first->next;
	else
	{
		previous = list->first;
		while ((previous->next != remove) && (previous != NULL))
			previous = previous->next;
		if (previous == NULL)
			return (-1);
		previous->next = remove->next;
		if (previous->next == NULL)
			list->last = previous;
	}
	list->size--;
//	free(remove);
	return (0);
}
