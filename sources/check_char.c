/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:02:10 by lunovill          #+#    #+#             */
/*   Updated: 2022/11/06 16:32:04 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_char(char c, int set)
{
	if (!set && ft_strichr(STRG_OPERATOR, c) != -1)
		return (1);
	else if (set == 1 && (c == CHAR_SGL_QUOTE || c == CHAR_DBL_QUOTE))
		return (c);
	else if (set == 2 && (c == CHAR_EXPANSION))
		return (c);
	else if (set == 3 && (c == CHAR_H_TAB
			|| c == CHAR_V_TAB || c == CHAR_SPACE))
		return (1);
	return (0);
}
