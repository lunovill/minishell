/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 01:35:13 by lunovill          #+#    #+#             */
/*   Updated: 2022/11/04 17:00:17 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

int	lst_print(t_cmd *list)
{
	unsigned int	i;
	t_token			*current;

	if (list == NULL)
		return (-1);
	current = list->first;
	i = list->size;
	while ((current != NULL) && i--)
	{
		ft_printf("case n°%u\n", list->size - i);
		ft_printf("[%u][%s]\n", current->id, current->s);
		ft_putchar('\n');
		current = current->next;
	}
	ft_putstr("(null)\n");
	ft_printf("\ncase : %u\n", list->size);
	return (0);
}
