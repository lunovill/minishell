/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 01:25:23 by lunovill          #+#    #+#             */
/*   Updated: 2022/10/24 03:19:00 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H
# include "libft.h"
#include <unistd.h>
#include <linux/limits.h>
 # include <signal.h>
 #include <sys/wait.h>
 # include <readline/readline.h>
# include <readline/history.h>
#include <stdio.h>

extern int g_status;
typedef struct s_env
{
    char *val;
    struct s_env *next;  
}   t_env;

typedef struct s_heredoc
{
    char *filename;
    char *file;
} t_heredoc;

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
	char **env;
}				t_cmd;
typedef struct s_command	t_command;
typedef struct s_command
{
	char *cmds;
	char **cmds_split;
	int		id;
	t_heredoc *hd;

	t_command *next;
}	t_command;
typedef struct s_partition	t_partition;
typedef struct s_partition
{
	t_command *cmds;
	int	pid;
	t_partition *next;
}	t_partition;
typedef struct s_minishell
{
    //t_env *env;
	t_env *env;
    t_cmd *cmds;
    t_partition *partition;
    char **paths;
    int     nb_pipes;
} t_minishell;

t_token			*lst_new();
t_cmd			*lst_init(t_token *init);
t_command		*lst_init_command(char *str, int id);
int				lst_add(t_cmd *list, t_token *befor, t_token *add);
int				lst_rmv(t_cmd *list, t_token *remove);
int				lst_print(t_cmd *list);
void    		lst_free(t_cmd *cmd);

char	**envlst_to_tab(t_env *env);
int     get_var_length(char *env);
char    *var_checker(t_env *env, char *str);
int     built_in_pwd(t_env *env, char **cmd);
int     built_in_env(t_env *env, char **cmd);
int     built_in_cd(t_env *env, char **cmd);
int     built_in_export(t_env *env, char **cmd);
int     built_in_unset(t_env **env, char **cmd);
int     built_in_echo(char **cmds);
int		built_in_exit(t_minishell *ms, char **cmd, int child);
int     builtins(t_minishell *ms, char **cmd, int child);

size_t	ft_strlen(const char *s);
char	*ft_strjoinms(char *s1, char *s2);
t_env	*ft_lstnew(char  *value);
void	ft_lstadd_back(t_env **alst, t_env *new);
t_env *create_env(char **env);
int built_in_export_p2(t_env *env, char *cmd);

int	ft_strcmp(const char *s1, const char *s2);
char *get_content(char *env);
int size_chartab(char **cmd);

int	here_doc(t_minishell *ms);
char	*delete_quotes(char *str);
int	is_builtin(t_command *cmd);
int	exec_single_builtin(t_minishell *ms);
void	exec_single(t_minishell *ms);
int exec(t_minishell *ms);

void	free_minishell(t_minishell *ms);
void free_env(t_env *env);
t_minishell *init_minishell(t_minishell *ms, t_cmd *cmd);

void	ft_lstadd_front(t_command **alst, t_command *tmp);
void	ft_lstadd_back3(t_command **alst, t_command *new);
void	ft_lstadd_back2(t_partition **alst, t_partition *new);
int		redirections(int fd_in, int fd_out, t_command* cmd);

char	*cmd_path(char **paths, char *cmd);
int		env_size(t_env *env);
char	**envlst_to_tab(t_env *env);
int	is_notspace(char *str);
void	ft_lstadd_front2(t_partition **alst, t_partition *tmp);
void	handle_signals_heredoc(void);
t_command *find_word(t_command *cmd);
void	handle_signals(void);
void	reset_signals(t_minishell *data);
void	handle_signals_exec(t_minishell *data);

#endif
