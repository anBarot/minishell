/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 20:37:55 by abarot            #+#    #+#             */
/*   Updated: 2020/07/23 18:56:58 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_parse_cmd(char **cmd_arg)
{
	t_list	*cmd;
	char	*tmp;
	int		i;

	i  = 0;
	cmd = 0;
	while (cmd_arg[i])
	{
		tmp = cmd_arg[i];
		ft_append_elt(&cmd, ft_strdup(cmd_arg[i]));
		i++;
		free(tmp);
	}
	if (ft_redirect_cmd(cmd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		ft_get_entries()
{
	char *line;
	char **cmd_list;
	char **cmd_arg;
	char *tmp;
	int		i;

	while (get_next_line(0, &line) != -1)
	{
		i = 0;
		if (!(cmd_list = ft_split((const char *)line, ';')))
			return (EXIT_FAILURE);
		while (cmd_list[i])
		{
			tmp = cmd_list[i];
			if (!(cmd_arg = ft_split(cmd_list[i], ' ')))
				return (EXIT_FAILURE);
			ft_parse_cmd(cmd_arg);
			i++;
			free(tmp);
		}
		free(cmd_list);
		free(cmd_arg);
		free(line);
	}
	return (EXIT_FAILURE);
}

int		main()
{
	if (ft_get_entries() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
