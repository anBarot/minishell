/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 20:37:55 by abarot            #+#    #+#             */
/*   Updated: 2020/09/04 16:15:19 by abarot           ###   ########.fr       */
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
		if (cmd_arg[i][0] == '~' && (!cmd_arg[i][1] || cmd_arg[i][1] == '\\'))
			ft_append_elt(&cmd, ft_strjoin("/home/", ft_get_value(g_shell.env, "LOGNAME", '=')));
		else
			ft_append_elt(&cmd, ft_strdup(cmd_arg[i]));
		i++;
		free(tmp);
	}
	if (ft_redirect_cmd(cmd) == EXIT_FAILURE)
	{	
		ft_putstr_fd(cmd->data, 1);
		ft_putstr_fd(": command not found\n", 1);
		ft_clear_list(&cmd);
		return (EXIT_FAILURE);
	}
	ft_clear_list(&cmd);
	return (EXIT_SUCCESS);
}

int		ft_parse_cmdpipe(char **cmd_pipe)
{
	int		i;
	char	**cmd_arg;
	char	*tmp;

	i = 0;
	while (cmd_pipe[i])
	{
		tmp = cmd_pipe[i];
		if (!(cmd_arg = ft_split(cmd_pipe[i], ' ')))
			return (EXIT_FAILURE);
		ft_parse_cmdarg(cmd_arg);
		i++;
		free(tmp);
		free(cmd_arg);
	}
	return (EXIT_SUCCESS);
}

int 	ft_parse_cmdlist(char *cmd_list)
{
	char *cmd;
	int	 i;

	i = 0;
	if (!cmd_list)
		return (EXIT_SUCCESS);
	while (cmd_list[i] && (cmd_list[i] != ';' || 
			(ft_count_elt(cmd_list + i, "\"") % 2 == 1 || ft_count_elt(cmd_list + i, "\'") % 2 == 1)))
			i++;
	cmd = ft_substr(cmd_list, 0, i);
	printf("\ncmd : %s\n", cmd);
	return (EXIT_SUCCESS);
}

char	*ft_replace_var(char *res, char *cmd_line)
{
	char	*var;
	char	*var_dol;

	var = ft_get_word(cmd_line + 1);
	if (var[ft_strlen(var) - 1] == '\"')
		var[ft_strlen(var) - 1] = '\0';
	var_dol = ft_strjoin("$", var);
	if (ft_get_value(g_shell.env, var, '='))
		res = ft_replace_in_str(res, var_dol, ft_get_value(g_shell.env, var, '='));
	ft_append_elt(&(g_garb_cltor), res);
	free(var);
	free(var_dol);
	return (res);
}

char	*ft_get_cmd_r(char *cmd_line)
{
	char	*res;

	res = cmd_line;
	if (*cmd_line == '$' && *(cmd_line + 1) == '?')
		cmd_line++;
	if (*cmd_line == '$' && !(ft_count_elt(cmd_line, "\'") % 2))
		res = ft_replace_var(res, cmd_line);
	cmd_line++;
	while (*cmd_line)
	{
		if (*cmd_line == '$' && (*(cmd_line - 1) != '\\' &&
			!(ft_count_elt(cmd_line, "\'") % 2)))
			res = ft_replace_var(res, cmd_line);
		cmd_line++;
	}
	return (res);
}

char	*ft_get_cmdline(char *line)
{
	char	*cmd_line;

	cmd_line = line;
	while (ft_count_elt(cmd_line, "\"") % 2 != 0 || 
			ft_count_elt(cmd_line, "\'") % 2 != 0)
	{
		ft_append_elt(&(g_garb_cltor), line);
		ft_putstr_fd("> ", 0);
		if (get_next_line(0, &line) == 0 && (ft_count_elt(line, "\"") % 2 != 1
				|| ft_count_elt(line, "\'") % 2 != 1))
			return ("\0");
		cmd_line = ft_strjoin(cmd_line,"\\n");
		ft_append_elt(&(g_garb_cltor), cmd_line);
		cmd_line = ft_strjoin(cmd_line, line);
		ft_append_elt(&(g_garb_cltor), cmd_line);
	}
	return (cmd_line);
}

int		ft_read_input()
{
	char *line;
	char *cmd_line;
	char *cmd_line_r;

	ft_show_current_dir();
	while (get_next_line(0, &line) == 1)
	{
		cmd_line = ft_get_cmdline(line);
		cmd_line_r = ft_get_cmd_r(cmd_line);
		printf("\ncmd line r : %s\n", cmd_line_r);
		ft_parse_cmdlist(cmd_line_r);
		ft_show_current_dir();
	}
	ft_putendl_fd("exit", 1);
	return (EXIT_SUCCESS);
}

void ft_quithandler() 
{
	//quit signal à voir
	printf("\nQuit signal detected\n");
}

void ft_inthandler() 
{
	//interrup signal à voir
	if (g_shell.cpid)
		kill(g_shell.cpid, SIGTERM);
	else
	{
		write(1, "\n", 1);
		ft_show_current_dir();
	}
}

void	ft_set_cwd()
{
	g_shell.cwd = ft_strdup(getcwd(g_shell.cwd, PATH_MAX));
	if (ft_get_value(g_shell.env, "HOME", '='))
		g_shell.r_cwd = ft_replace_in_str(g_shell.cwd, 
					ft_get_value(g_shell.env, "HOME", '='), "~");
	else
		g_shell.r_cwd = ft_strdup(getcwd(g_shell.cwd, PATH_MAX));
	ft_append_elt(&g_garb_cltor, g_shell.cwd);
	ft_append_elt(&g_garb_cltor, g_shell.r_cwd);
}

int		main(int ac, char **av, char **envp)
{
	g_shell.cpid = 0;
	g_garb_cltor = 0;
	signal(SIGINT, ft_inthandler);
	signal(SIGQUIT, ft_quithandler);
	if (!ac || !av || !envp)
		return (EXIT_FAILURE);
	g_shell.argv = av;
	g_shell.env = envp;
	ft_set_cwd();
	if (ft_read_input() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_clear_list(&g_garb_cltor);
	return (EXIT_SUCCESS);
}
