/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 20:37:55 by abarot            #+#    #+#             */
/*   Updated: 2020/09/09 18:32:35 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_show_current_dir()
{
	ft_putstr_fd(ANSI_COLOR_BLUE, 1);
	if (ft_get_value(g_shell.env, "USER", '='))
	{
		ft_putstr_fd(ft_get_value(g_shell.env, "USER", '='), 1);
		ft_putstr_fd(":", 1);
	}
	else if (ft_get_value(g_shell.env, "LOGNAME", '='))
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

void	ft_set_cwd()
{
	g_shell.cwd = ft_strdup(getcwd(g_shell.cwd, PATH_MAX));
	if (!(g_shell.r_cwd = ft_replace_in_str(g_shell.cwd, g_shell.tilde, "~")))
		g_shell.r_cwd = ft_strdup(getcwd(g_shell.cwd, PATH_MAX));
	ft_append_elt(&g_garb_cltor, g_shell.cwd);
	ft_append_elt(&g_garb_cltor, g_shell.r_cwd);
}

int		ft_read_input()
{
	char *line;
	char *cmd_line;
	char *cmd_line_r;

	ft_show_current_dir();
	while (get_next_line(0, &line) == 1)
	{
		cmd_line = ft_multiline_mng(line);
		cmd_line_r = ft_get_cmd_r(cmd_line);
		ft_parse_cmdline(cmd_line_r);
		ft_show_current_dir();
		if (ft_list_size(g_garb_cltor) > 50)
		{	
			ft_clear_list(&(g_garb_cltor));
			g_garb_cltor = 0;
		}
	}
	ft_putendl_fd("exit", 1);
	return (EXIT_SUCCESS);
}

void	ft_init_shell(char **av, char **envp)
{
	g_shell.cpid = 0;
	g_shell.argv = av;
	g_shell.env = envp;
	if (!(g_shell.tilde = ft_get_value(g_shell.env, "HOME", '=')))
	{
		if (ft_get_value(g_shell.env, "LOGNAME", '='))
			g_shell.tilde = ft_strjoin("/home/",
					ft_get_value(g_shell.env, "LOGNAME", '='));
		else
			g_shell.tilde = 0;
	}
	ft_set_cwd();
}

int		main(int ac, char **av, char **envp)
{
	g_garb_cltor = 0;
	signal(SIGINT, ft_inthandler);
	signal(SIGQUIT, ft_quithandler);
	if (!ac || !av || !envp)
		return (EXIT_FAILURE);
	ft_init_shell(av, envp);
	if (ft_read_input() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_clear_list(&g_garb_cltor);
	return (EXIT_SUCCESS);
}
