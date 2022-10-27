/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_delimiter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunovill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 21:56:22 by lunovill          #+#    #+#             */
/*   Updated: 2022/10/24 21:56:24 by lunovill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #define CheckOprtr(c) ((ft_strichr(STRG_OPERATOR, (c)) == -1) ? 0 : 1)
// #define CheckQuote(c) (((c) != CHAR_SGL_QUOTE && (c) != CHAR_DBL_QUOTE) ? 0 : (c))
// #define CheckExpns(c) (((c) != CHAR_EXPANSION) ? 0 : (c))
// #define CheckBlank(c) (((c) != CHAR_H_TAB && (c) != CHAR_V_TAB && (c) != CHAR_SPACE) ? 0 : 1)

static int	check_char(char c, int set)
{
	if (!set && ft_strichr(STRG_OPERATOR, c) != -1)
		return (1);
	else if (set == 1 && (c == CHAR_SGL_QUOTE || c == CHAR_DBL_QUOTE))
		return (c);
	else if (set == 2 && (c == CHAR_EXPANSION))
		return (c);
	else if (set == 3 && (c == CHAR_H_TAB || c == CHAR_V_TAB || c == CHAR_SPACE))
		return (1);
	return (0);
}

static int	tk_isoprtr(const char *operator, size_t size)
{
	if (!check_char(operator[size], 0))
		return (0);
	if (!ft_strncmp(STRG_DLESS, operator, size + 1)
		|| !ft_strncmp(STRG_DGREAT, operator, size + 1))
		return (1);
	return (0);
}

int	tk_delimiter(char *line, t_cmd *cmd, t_token *token)
{
	int				oprtr;
	int				quote;
	int				expns;
	int				ret;
	unsigned int	i;
	unsigned int	j;

	oprtr = 0;
	quote = 0;
	i = 0;
	j = 0;
	while (line[i] && check_char(line[i], 3))
			i++;
	while (line[i])
	{
		if (i && j)
			token = lst_new();
		oprtr = check_char(line[i], 0);
		quote = check_char(line[i], 1);
		expns = check_char(line[i], 2);
		j = i + 1;
		while (line[j])
		{
			if (oprtr && !quote && tk_isoprtr(line + i, j - i))
			{
				oprtr = check_char(line[j], 0);
				j++;
				continue ;
			}
			else if (oprtr && !quote && !tk_isoprtr(line + i, j - i))
				break ;
			else if (!quote && check_char(line[j], 1))
				quote = line[j];
			else if (quote && line[j] == quote)
				quote = 0;
			else if (quote != CHAR_SGL_QUOTE && expns)
			{
				ret = tk_expansion(&line, &j, cmd->env);
				if (ret == 1)
					continue ;
				else if (ret == -1)
					return (-1);
			}
			else if (!quote && check_char(line[j], 0))
				break ;
			else if (!quote && check_char(line[j], 3))
				break ;
			oprtr = check_char(line[j], 0);
			expns = check_char(line[j], 2);
			j++;
		}
		if (quote)
			return (ft_putstr_fd("minishell: syntax error token `quote' not closed\n", 2), -1);
		token->s = ft_strndup(line + i, j - i);
		if (token != cmd->first)
			lst_add(cmd, cmd->last, token);
		while (line[j] && check_char(line[j], 3))
			j++;
		i = j;
	}
	if (!j)
		token->s = ft_strdup("");
	return (0);
}
