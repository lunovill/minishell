/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunovill <lunovill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 01:34:24 by lunovill          #+#    #+#             */
/*   Updated: 2021/04/28 01:34:52 by lunovill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_token	*lst_new(void)
{
	t_token	*new;

	if ((new = malloc(sizeof(*new))) == NULL)
		return (NULL);
	new->id  = 0;
	new->previous = NULL;
	new->next = NULL;
	return (new);
}
