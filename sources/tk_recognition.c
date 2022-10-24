#include "minishell.h"

static int	tk_operator(t_cmd *cmd)
{
	t_token	*token;
	int		ret;

	ret = 1;
	token = cmd->first;
	while (token && ret)
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
		if (token->id && ((token->previous && token->previous->id) || !token->next))
		{
			ret--;
			break ;
		}
		token = token->next;
	}
	if (!ret)
	{
		if (token->previous && token->previous->id)
			ft_printf("minishell: syntax error near unexpected token `%s'\n", token->s);
		else
			ft_printf("minishell: syntax error near unexpected token `newline'\n");
	}
	return (ret);
}

static int	tk_pipe(t_token *current)
{
	while(current) // pipe_sequence
	{
		if (current->id != TK_PIPE)
		{
			while (current->previous && current->previous->id != TK_PIPE)
				current = current->previous;
			tk_command(current); // return ??
		}
		current = current->previous;
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
		return (ft_free(first), NULL);
	cmd->env = env;
	if (tk_delimiter(line, cmd, first) == -1)
		return (lst_free(cmd), NULL);
	if (!tk_operator(cmd))
		return (lst_free(cmd), NULL);
	if (!tk_pipe(cmd->last))
		return (lst_free(cmd), NULL);
	return (cmd);
}
