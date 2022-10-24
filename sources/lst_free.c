/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunovill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 23:02:05 by lunovill          #+#    #+#             */
/*   Updated: 2022/10/23 23:02:06 by lunovill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void    lst_free(t_cmd *cmd)
{
    if (cmd)
    {
        if (cmd->size)
            while (cmd->first)
                lst_rmv(cmd, cmd->first);
        free(cmd);
    }
    cmd = NULL;
}