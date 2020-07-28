/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 20:37:55 by abarot            #+#    #+#             */
/*   Updated: 2020/07/29 00:23:47 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_show_current_dir()
{
	ft_putstr_fd(ANSI_COLOR_BLUE, 1);
	ft_putstr_fd(ft_get_value(g_shell.env, "LOGNAME", '='), 1);
	ft_putstr_fd(":", 1);
	ft_putstr_fd(ANSI_COLOR_GREEN, 1);
	ft_putstr_fd(g_shell.r_cwd, 1);
	write (1, "$ " , 2);
	ft_putstr_fd(ANSI_COLOR_RESET, 1);
}

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
	ft_clear_list(&cmd);
	return (EXIT_SUCCESS);
}

int		ft_rd_input()
{
	char *line;
	char **cmd_list;
	char **cmd_arg;
	char *tmp;
	int		i;

	ft_show_current_dir();
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
		ft_show_current_dir();
		free(cmd_list);
		free(cmd_arg);
		free(line);
	}
	return (EXIT_FAILURE);
}

void ft_intHandler() 
{
	kill(0, SIGTERM);
	ft_show_current_dir();
}

int		main(int ac, char **av, char **envp)
{
	// struct dirent *entry;
	signal(SIGINT, ft_intHandler);
	if (!ac || !av || !envp)
		return (EXIT_FAILURE);
	if (!(g_shell.folder = opendir(".")))
		return (EXIT_FAILURE);
	// entry = readdir(g_shell.folder);
	g_shell.env = envp;
	g_shell.cwd = getcwd(g_shell.cwd, PATH_MAX);
	g_shell.r_cwd = ft_replace_in_str(g_shell.cwd, ft_get_value(g_shell.env, "HOME", '='), "~");
	if (ft_rd_input() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	closedir(g_shell.folder);
	free(g_shell.cwd);
	return (EXIT_SUCCESS);
}
