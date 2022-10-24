#include "minishell.h"

static void	tk_operator(t_cmd *cmd)
{
	t_token	*token;

	token = cmd->first;
	while (token)
	{
		if (!ft_strcmp(STRG_LESS, token->s))
			token->id = TK_LESS;
		else if (!ft_strcmp(STRG_GREAT, token->s))
			token->id = TK_GREAT;
		else if (!ft_strcmp(STRG_DLESS, token->s))
			token->id = TK_DLESS;
		else if (!ft_strcmp(STRG_DGREAT, token->s))
			token->id = TK_DGREAT;
		else if (!ft_strcmp(STRG_PIPE, token->s))
			token->id = TK_PIPE;
		token = token->next;
	}
}

static int	tk_pipe(t_token *current)
{
	while(current) // pipe_sequence
	{
		if (current->id != TK_PIPE)
		{
			while (current->previous && current->previous->id != TK_PIPE)
				current = current->previous;
			tk_command(current);
			if (current)
				current = current->previous;
		}
		if (current)
		{
			tk_pipe(current->previous);
			return (0);
		}
	}
	return (1);
}

t_cmd	*tk_recognition(char *line, char **env)
{
	t_token			*first;
	t_cmd			*cmd;

	first = lst_new();
	if (!first)
		return (NULL);
	cmd = lst_init(first);
	if (!cmd)
		return (NULL);
	cmd->env = env;
	if (tk_delimiter(line, cmd, first) == -1)
		return (NULL);
	tk_operator(cmd);
	lst_print(cmd);
	if(!tk_pipe(cmd->last))
		return (NULL);
	return (cmd);
}
