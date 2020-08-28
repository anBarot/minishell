/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 20:37:55 by abarot            #+#    #+#             */
/*   Updated: 2020/08/28 11:53:58 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_show_current_dir()
{
	ft_putstr_fd(ANSI_COLOR_BLUE, 1);
	if (ft_get_value(g_shell.env, "LOGNAME", '='))
	{
		ft_putstr_fd(ft_get_value(g_shell.env, "LOGNAME", '='), 1);
		ft_putstr_fd(":", 1);
	}	
	else
		ft_putstr_fd("minishell:", 1);
	ft_putstr_fd(ANSI_COLOR_GREEN, 1);
	ft_putstr_fd(g_shell.r_cwd, 1);
	write (1, "$ " , 2);
	ft_putstr_fd(ANSI_COLOR_RESET, 1);
}

int		ft_parse_cmdarg(char **cmd_arg)
{
	t_list	*cmd;
	char	*tmp;
	int		i;

	i  = 0;
	cmd = 0;
	while (cmd_arg[i])
	{
		tmp = cmd_arg[i];
		if (cmd_arg[i][0] == '$')
			ft_append_elt(&cmd, ft_strdup(ft_get_value(g_shell.env, cmd_arg[i] + 1, '=')));
		else
			ft_append_elt(&cmd, ft_strdup(cmd_arg[i]));
		i++;
		free(tmp);
	}
	if (ft_redirect_cmd(cmd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_clear_list(&cmd);
	return (EXIT_SUCCESS);
}

int 	ft_parse_cmdlist(char **cmd_list)
{
	char **cmd_arg;
	char *tmp;
	int		i;

	i = 0;
	while (cmd_list[i])
	{
		tmp = cmd_list[i];
		if (!(cmd_arg = ft_split(cmd_list[i], ' '))
			|| ft_parse_cmdarg(cmd_arg) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
		free(tmp);
	}
	free(cmd_arg);
	free(cmd_list);
	return (EXIT_SUCCESS);
}

int		ft_rd_input()
{
	char *line;
	char **cmd_list;

	ft_show_current_dir();
	while (get_next_line(0, &line) == 1)
	{
		if (!(cmd_list = ft_split((const char *)line, ';')))
			return (EXIT_FAILURE);
		ft_parse_cmdlist(cmd_list);
		ft_show_current_dir();
		free(line);
	}
	ft_putendl_fd("exit", 1);
	return (EXIT_FAILURE);
}

void ft_inthandler() 
{
	kill(0, SIGTERM);
	ft_show_current_dir();
}

void	ft_set_cwd()
{
	g_shell.cwd = getcwd(g_shell.cwd, PATH_MAX);
	g_shell.r_cwd = ft_replace_in_str(g_shell.cwd, 
					ft_get_value(g_shell.env, "HOME", '='), "~");
	ft_append_elt(&g_garb_cltor, g_shell.cwd);
	ft_append_elt(&g_garb_cltor, g_shell.r_cwd);
}

int		main(int ac, char **av, char **envp)
{
	// struct dirent *entry;
	g_garb_cltor = 0;
	signal(SIGINT, ft_inthandler);
	if (!ac || !av || !envp)
		return (EXIT_FAILURE);
	// if (!(g_shell.folder = opendir(".")))
	// 	return (EXIT_FAILURE);
	// entry = readdir(g_shell.folder);
	g_shell.argv = av;
	g_shell.env = envp;
	ft_set_cwd();
	if (ft_rd_input() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_append_elt(&g_garb_cltor, g_garb_cltor);
	ft_clear_list(&g_garb_cltor);
	// closedir(g_shell.folder);
	return (EXIT_SUCCESS);
}
