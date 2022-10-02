/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunovill <lunovill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 01:33:38 by lunovill          #+#    #+#             */
/*   Updated: 2021/04/28 01:33:58 by lunovill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_cmd	*lst_init(t_token *init)
{
	t_cmd	*list;

	if ((list = malloc(sizeof(*list))) == NULL)
		return (NULL);
	list->size = 1;
	list->first = init;
	list->last = init;
	return (list);
}
