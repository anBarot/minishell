/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 16:00:15 by abarot            #+#    #+#             */
/*   Updated: 2020/09/03 19:44:55 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_cmd(t_list *cmd)
{
	while (cmd->next)
	{
		cmd = cmd->next;
		if (cmd->data)
		{
			ft_putstr_fd(cmd->data, 1);
			write(1, " ", 1);
		}
	}
	write (1, "\n", 1);
}

void	cd_cmd(t_list *cmd)
{
	char	*tmp;

	if (ft_list_size(cmd) == 1)
	{
		if (chdir(ft_get_value(g_shell.env, "HOME", '=')) == -1)
			ft_putendl_fd("minishell: cd: HOME not set", 1);
	}
	else if (ft_list_size(cmd) > 2)
		ft_putendl_fd("minishell: cd: too many arguments", 1);
	else if (chdir(cmd->next->data) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 1);
		ft_putstr_fd(cmd->next->data, 1);
		ft_putendl_fd(": No such file or directory", 1);
	}
	tmp = ft_strjoin("OLDPWD=", g_shell.cwd);
	ft_append_env(tmp);
	ft_append_elt(&g_garb_cltor, tmp);
	ft_set_cwd();
	tmp = ft_strjoin("PWD=", g_shell.cwd);
	ft_append_env(tmp);
	ft_append_elt(&g_garb_cltor, tmp);
}

int		ft_exec(t_list *cmd)
{
	if (stat(cmd->data, &(g_shell.stat)) == -1 || (g_shell.cpid = fork()) == -1)
	{	
		if (*(char *)(cmd->data) == '/')
		{
			ft_putstr_fd("minishell: ", 1);
			ft_putstr_fd(cmd->data, 1);
			ft_putendl_fd(": No such file or directory", 1);
			return (EXIT_SUCCESS);
		}
		else
			return (EXIT_FAILURE);
	}
	if (g_shell.cpid > 0)
	{
		ft_inthandler();
		wait(&(g_shell.cpid));
		kill(g_shell.cpid, SIGTERM);
	}
	if	(execve(cmd->data, (char **)ft_list_to_array(cmd), g_shell.env) != EXIT_SUCCESS)
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(cmd->data, 1);
		ft_putstr_fd(": Permission denied\n", 1);
		return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

int		ft_redirect_cmd(t_list *cmd)
{
	if	(ft_issamestr(cmd->data, "exit"))
	{
		ft_clear_list(&cmd);
		ft_append_elt(&g_garb_cltor, g_garb_cltor);
		ft_clear_list(&g_garb_cltor);
		exit(EXIT_SUCCESS);
	}
	else if	(ft_issamestr(cmd->data, "cd"))
		cd_cmd(cmd);
	else if (ft_issamestr(cmd->data, "echo"))
		echo_cmd(cmd);
	else if	(ft_issamestr(cmd->data, "pwd"))
		ft_putendl_fd(g_shell.cwd, 1);
	else if	(ft_issamestr(cmd->data, "export"))
		ft_append_env(cmd->next->data);
	else if	(ft_issamestr(cmd->data, "unset"))
		ft_retreive_env(cmd->next->data);
	else if	(ft_issamestr(cmd->data, "env"))
		ft_show_env();
	else
		return (ft_exec(cmd));
	return (EXIT_SUCCESS);
}
