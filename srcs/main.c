/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 20:37:55 by abarot            #+#    #+#             */
/*   Updated: 2020/07/22 17:30:16 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_shell()
{
	exit(EXIT_SUCCESS);
}

int		ft_append_elt(t_list **list, char *elt)
{
	t_list *new_elt;

	if (!list || !elt || !(new_elt = malloc(sizeof(t_list))))
		return (EXIT_FAILURE);
	new_elt->data = elt;
	new_elt->next = 0;
	if (!(*list))
	{
		(*list) = new_elt;
		return (EXIT_SUCCESS);
	}
	while ((*list)->next)
		(*list) = (*list)->next;
	(*list)->next = new_elt;
	return (EXIT_SUCCESS);
}

void	ft_parse_cmd(char ***cmd_list)
{
	t_list	*cmd;

	cmd = 0;
	while (**cmd_list && ***cmd_list != ';')
	{
		ft_append_elt(&cmd, ft_strdup(**cmd_list));
		free(**cmd_list);
		*cmd_list = *cmd_list + 1;
	}
	if (ft_redirect_cmd(cmd) == EXIT_FAILURE)
		printf("\nError\n");
}

int		ft_get_entries()
{
	char *line;
	char **cmd_list;
	int		val;

	while ((val = get_next_line(0, &line)))
	{
		if (val == -1)
			return (EXIT_FAILURE);
		if (!(cmd_list = ft_split((const char *)line, ' ')))
			return (EXIT_FAILURE);
		while (*cmd_list)
			ft_parse_cmd(&cmd_list);
		free(line);
	}
	return (EXIT_SUCCESS);
}

int		main(int ac, char **av)
{
	if (ac != 1 && av)
	{
		ft_putstr_fd("\nNo arguments are allowed\n", 1);
		return (1);
	}
	ft_putstr_fd("\n", 1);
	if (ft_get_entries() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
