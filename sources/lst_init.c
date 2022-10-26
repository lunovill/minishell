/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 01:33:38 by lunovill          #+#    #+#             */
/*   Updated: 2022/10/26 17:25:35 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_cmd	*lst_init(t_token *init)
{
	t_cmd	*list;

	list = malloc(sizeof(*list));
	if (list == NULL)
		return (NULL);
	list->size = 1;
	list->first = init;
	list->last = init;
	return (list);
}
