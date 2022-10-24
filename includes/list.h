/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunovill <lunovill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 01:25:23 by lunovill          #+#    #+#             */
/*   Updated: 2022/09/29 20:58:54 by lunovill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H
# include "libft.h"

typedef struct s_token	t_token;
struct			s_token
{
	unsigned int id;
	char *s;
	t_token	*previous;
	t_token	*next;
};

typedef	struct	s_cmd
{
	t_token	*first;
	t_token	*last;
	size_t	size;
	char	**env;
}				t_cmd;

t_token			*lst_new();
t_cmd			*lst_init(t_token *init);
int				lst_add(t_cmd *list, t_token *befor, t_token *add);
int				lst_rmv(t_cmd *list, t_token *remove);
int				lst_print(t_cmd *list);
void    		lst_free(t_cmd *cmd);

#endif
