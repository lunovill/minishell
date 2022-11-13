/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:43:34 by lunovill          #+#    #+#             */
/*   Updated: 2022/11/07 19:04:09 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <linux/limits.h>

// Characteres values
# define CHAR_H_TAB 9
# define CHAR_V_TAB 11
# define CHAR_SPACE 32
# define CHAR_DBL_QUOTE 34
# define CHAR_EXPANSION 36
# define CHAR_SGL_QUOTE 39
# define CHAR_PIPE 124

// Strings operators
# define STRG_OPERATOR "<>|"
# define STRG_LESS "<"
# define STRG_GREAT ">"
# define STRG_DLESS "<<"
# define STRG_DGREAT ">>"
# define STRG_PIPE "|"

// Tokens values
# define TK_WORD 1
# define TK_WD_CMD_NAME 2
# define TK_WD_CMD_WORD 3
# define TK_WD_FILENAME 4
# define TK_WD_HERE_END 5
# define TK_NAME 6
# define TK_IO_NUMBER 7
# define TK_LESS 8
# define TK_GREAT 9
# define TK_DLESS 10
# define TK_DGREAT 11
# define TK_PIPE 12

# include "list.h"

int				check_char(char c, int set);
int				tk_delimiter(char *line, t_cmd *cmd, t_token *token,
					t_tmp *tmp);
int				tk_command(t_token *current);
int				tk_expansion(char **line, unsigned int *i, char **env);
t_cmd			*tk_recognition(char *line, char **env);
int				tk_split_cmd(t_cmd *cmd);

int				tk_pt4(t_cmd *cmd, t_token *token, char **line,
					unsigned int *j);
char			*tk_pt5(int *tab, unsigned int i, char *line, unsigned int j);
int				tk_pt6(t_token *token, unsigned int j);
void			tk_pt7(void);
void			tk_pt2(unsigned int i, int *tab, char *line, unsigned int *j);
void			tk_pt3(unsigned int *i, int *tab, char *line, unsigned int *j);

int				tk_isoprtr(const char *operator, size_t size);
int				boucle_p1(t_tmp *tmp, char **line);
int				boucle_p2(t_tmp *tmp, char **line, t_cmd *cmd);
int				boucle_p3(t_tmp *tmp, char **line, t_cmd *cmd);
int				boucle_p4_2(t_tmp *tmp, char **line, t_cmd *cmd);
int				boucle_p4(t_tmp *tmp, char **line, t_cmd *cmd);

char			**envlst_to_tab(t_env *env);
int				get_var_length(char *env);
char			*var_checker(t_env *env, char *str);
int				built_in_pwd(t_env *env, char **cmd);
int				built_in_env(t_env *env, char **cmd);
int				built_in_cd(t_env *env, char **cmd);
int				built_in_export(t_minishell *ms, t_env *env, char **cmd);
int				built_in_unset(t_minishell *ms, t_env **env, char **cmd);
int				built_in_echo(char **cmds);
int				built_in_exit(int *fd, t_minishell *ms, char **cmd, int child);
int				builtins(int *fd, t_minishell *ms, char **cmd, int child);
void			command_notfound(t_command *cmds);

size_t			ft_strlen(const char *s);
char			*ft_strjoinms(char *s1, char *s2);
t_env			*ft_lstnew(char *value);
void			ft_lstadd_back(t_env **alst, t_env *new);
t_env			*create_env(char **env);
int				built_in_export_p2(t_env *env, char *cmd);

int				ft_strcmp(const char *s1, const char *s2);
char			*get_content(char *env);
int				size_chartab(char **cmd);

int				here_doc(t_minishell *ms);
char			*delete_quotes(char *str);
int				is_builtin(t_command *cmd);
int				exec_single_builtin(t_minishell *ms);
void			exec_single(t_minishell *ms);
int				exec(t_minishell *ms);

void			free_minishell(t_minishell *ms);
void			free_env(t_env *env);
t_minishell		*init_minishell(t_minishell *ms, t_cmd *cmd);

void			ft_lstadd_front(t_command **alst, t_command *tmp);
void			ft_lstadd_back3(t_command **alst, t_command *new);
void			ft_lstadd_back2(t_partition **alst, t_partition *new);
int				redirections(int fd_in, int fd_out, t_command	*cmd);

char			*cmd_path(char **paths, char *cmd);
int				env_size(t_env *env);
char			**envlst_to_tab(t_env *env);
int				is_notspace(char *str);
void			ft_lstadd_front2(t_partition **alst, t_partition *tmp);
void			handle_signals_heredoc(void);
t_command		*find_word(t_command *cmd);
void			handle_signals(void);
void			reset_signals(t_minishell *data);
void			handle_signals_exec(t_minishell *data);
int				pipe_number(t_cmd *first);
void			parsing_paths(t_env *envp, t_minishell *ms);
t_token			*next_token(t_token *tk);

void			ctrl_c_exec(int signum);
void			reset_signals(t_minishell *data);
void			handle_signals_exec(t_minishell *data);
void			ctrl_back_slash(int signum);

int				exec(t_minishell *ms);
void			print_signal(int signal);
void			exec_child(t_minishell *ms, t_command *cmd, int *fd, int *tmp);
void			free_split(char	**str);
char			*word_parsing(t_token *token);

#endif
