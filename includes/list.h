/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 01:25:23 by lunovill          #+#    #+#             */
/*   Updated: 2022/11/06 00:56:47 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H
# include "libft.h"
# include <unistd.h>
# include <linux/limits.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>

extern int					g_status;

typedef struct s_env
{
	char			*val;
	struct s_env	*next;
}							t_env;

typedef struct s_heredoc
{
	char	*filename;
	char	*file;
}							t_heredoc;

typedef struct s_token		t_token;
struct						s_token
{
	unsigned int	id;
	char			*s;
	t_token			*previous;
	t_token			*next;
};

typedef struct s_cmd
{
	t_token	*first;
	t_token	*last;
	size_t	size;
	char	**env;
}						t_cmd;

typedef struct s_command	t_command;
struct s_command
{
	char		*cmds;
	char		**cmds_split;
	int			id;
	t_heredoc	*hd;
	t_command	*next;
};

typedef struct s_partition	t_partition;
struct s_partition
{
	t_command	*cmds;
	int			pid;
	t_partition	*next;
};
typedef struct s_minishell
{
	char		**char_env;
	t_env		*env;
	t_cmd		*cmds;
	t_partition	*partition;
	char		**paths;
	int			nb_pipes;
	int			i;
}							t_minishell;

typedef struct s_tmp
{
	int				*tab;
	int				ret;
	unsigned int	i;
	unsigned int	j;
}							t_tmp;
t_token			*lst_new(void);
t_cmd			*lst_init(t_token *init);
t_command		*lst_init_command(char *str, int id);
int				lst_add(t_cmd *list, t_token *befor, t_token *add);
int				lst_rmv(t_cmd *list, t_token *remove);
int				lst_print(t_cmd *list);
void			lst_free(t_cmd *cmd);

#endif
