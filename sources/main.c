/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:26:40 by skhali            #+#    #+#             */
/*   Updated: 2022/11/04 17:12:01 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell.h"

int	g_status = 0;

t_command	*lst_init_command(char *str, int id)
{
	t_command	*list;

	list = malloc(sizeof(*list));
	if (list == NULL)
		return (NULL);
	list->cmds = delete_quotes(ft_strdup(str));
	list->cmds_split = ft_split(str, ' ');
	list->id = id;
	list->hd = NULL;
	list->next = NULL;
	return (list);
}

int	is_notspace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'
			&& str[i] != '\r' && str[i] != '\v' && str[i] != '\f')
			return (1);
		i++;
	}
	return (0);
}

t_minishell	*init_start(char **env, int argc, char **argv)
{
	t_minishell	*ms;

	(void)argv;
	(void)argc;
	ms = malloc(sizeof(t_minishell));
	if (!ms)
		return (exit(1), NULL);
	ms->env = create_env(env);
	ms->char_env = envlst_to_tab(ms->env);
	return (ms);
}

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_cmd		*cmd;
	t_minishell	*ms;

	ms = init_start(env, argc, argv);
	while (1)
	{
		handle_signals();
		line = readline("minishell> ");
		if (!line)
			return (0);
		if (!is_notspace(line))
			continue ;
		add_history(line);
		cmd = tk_recognition(line, ms->char_env);
		if (!cmd)
			continue ;
		g_status = 0;
		ms = init_minishell(ms, cmd);
		// t_partition *ptt = ms->partition;
		// t_command *pt;
		// // while (ptt)
		// {
		// 	pt = ptt->cmds;
		// 	while (pt)
		// 	{
		// 		printf("partition : %s, id : %d\n", pt->cmds, pt->id);
		// 		pt = pt->next;
		// 	}
		// 	ptt = ptt->next;
		// }
		exec(ms);
		free_minishell(ms);
	}
	return (free_split(ms->char_env), free_env(ms->env), free(ms), 0);
}
