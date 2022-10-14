#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

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
# define TK_WD_CMD_NAME (TK_WORD + 1)
# define TK_WD_CMD_WORD (TK_WD_CMD_NAME + 1)
# define TK_WD_FILENAME (TK_WD_CMD_WORD + 1)
# define TK_WD_HERE_END (TK_WD_FILENAME + 1)
# define TK_NAME (TK_WD_HERE_END + 1)
# define TK_IO_NUMBER (TK_NAME + 1)
# define TK_LESS (TK_IO_NUMBER + 1)
# define TK_GREAT (TK_LESS + 1)
# define TK_DLESS (TK_GREAT+ 1)
# define TK_DGREAT (TK_DLESS + 1)
# define TK_PIPE (TK_DGREAT + 1)

# include "list.h"


int		tk_delimiter(char *line, t_cmd *cmd, t_token *token);
int		tk_command(t_token *current);
int     tk_expansion(char **line, unsigned int *i, char **env);
t_cmd	*tk_recognition(char *line, char **env);

#endif