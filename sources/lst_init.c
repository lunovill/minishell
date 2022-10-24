/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 01:33:38 by lunovill          #+#    #+#             */
/*   Updated: 2022/10/24 03:21:24 by skhali           ###   ########.fr       */
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

t_command	*lst_init_command(char *str, int id)
{
	t_command	*list;

	if ((list = malloc(sizeof(*list))) == NULL)
		return (NULL);
	list->cmds = ft_strdup(str);
	list->cmds_split = ft_split(str, ' ');
	list->id = id;
	list->hd = NULL;
	list->next = NULL;
	return (list);
}
