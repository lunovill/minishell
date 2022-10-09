#include "minishell.h"

static int	token(t_token *token, int id)
{
	unsigned int	i;

	if (!token || (TK_LESS <= token->id && token->id <= TK_PIPE))
		return (0);
	i = 0;
	if (id == TK_IO_NUMBER)
	{
		while (token->s[i])
			if (!ft_isdigit(token->s[i++]))
				return (0);
	}
	token->id = id;
	return (1);
}

static int	cmd_fileorhere(t_token *current, int set)
{
 	if (!current->next)
		return (0);
	if (!set && token(current->next, TK_WD_FILENAME))
	{
	if (current->id == TK_LESS
		|| current->id == TK_GREAT
		|| current->id == TK_DGREAT)
		return (2);
	}
	else if (set && token(current->next, TK_WD_HERE_END))
		if (current->id == TK_DLESS)
			return (2);
	return (0);
}

static int	cmd_redirection(t_token *current)
{
	if (!current || current->id == TK_PIPE)
		return (0);
	if (cmd_fileorhere(current, 0))
		return (2);
	else if (current->next && token(current, TK_IO_NUMBER) && cmd_fileorhere(current->next, 0))
		return (3);
	else if (cmd_fileorhere(current, 1))
		return (2);
	else if (current->next && token(current, TK_IO_NUMBER) && cmd_fileorhere(current->next, 1))
		return (3);
	return (0);
}

int	tk_command(t_token *current)
{
	int	ret;

	ret = cmd_redirection(current);
	if (ret) // cmd_prefix
	{
		while (ret--)
		{
			current = current->next;
			if (!ret)
				ret = cmd_redirection(current);
		}
		if (token(current, TK_WD_CMD_WORD)) // cmd_word
			current = current->next;
		ret = cmd_redirection(current); // cmd_suffix
		if (!ret)
			ret = token(current, TK_WORD);
		while (ret--)
		{
			current = current->next;
			if (!ret)
				ret = cmd_redirection(current);
			if (!ret)
				ret = token(current, TK_WORD);
		}
		if (current && current->id == TK_PIPE) // end of command
			return (0);
		return (1);
	}
	else if (token(current, TK_WD_CMD_NAME)) // cmd_name
	{
		current = current->next;
		ret = cmd_redirection(current); // cmd_suffix
		if (!ret)
			ret = token(current, TK_WORD);
		while (ret--)
		{
			current = current->next;
			if (!ret)
				ret = cmd_redirection(current);
			if (!ret)
				ret = token(current, TK_WORD);
		}
		if (current && current->id == TK_PIPE) // end of command
			return (0);
		return (1);
	}
	return (0);
}
