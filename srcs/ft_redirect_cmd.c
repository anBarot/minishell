/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 16:00:15 by abarot            #+#    #+#             */
/*   Updated: 2020/08/28 11:27:54 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_cmd(t_list *cmd)
{
	cmd = cmd->next;
	while (cmd->next)
	{
		ft_putstr_fd(cmd->data, 1);
		cmd = cmd->next;
		write(1, " ", 1);
	}
	ft_putendl_fd(cmd->data, 1);
}

int	cd_cmd(t_list *cmd)
{
	char	*tmp;

	if (ft_list_size(cmd) == 1)
	{
		if (chdir(ft_get_value(g_shell.env, "HOME", '=')) == -1)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 1);
			return (EXIT_FAILURE);
		}
	}
	else if (ft_list_size(cmd) > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 1);
		return (EXIT_FAILURE);
	}
	else if (chdir(cmd->next->data) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 1);
		ft_putstr_fd(cmd->next->data, 1);
		ft_putendl_fd(": No such file or directory", 1);
		return (EXIT_FAILURE);
	}
	tmp = ft_strjoin("OLDPWD=", g_shell.cwd);
	ft_append_elt(&g_garb_cltor, tmp);
	ft_append_env(tmp);
	ft_set_cwd();
	tmp = ft_strjoin("PWD=", g_shell.cwd);
	ft_append_elt(&g_garb_cltor, tmp);
	ft_append_env(tmp);
	return (EXIT_SUCCESS);
}

void	ft_exec(t_list *cmd)
{
	pid_t	pid;
	int		status;

	pid = 0;
	status = 0;
	if ((pid = fork()) == -1)
		perror("minishell: fork:");
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	} 
	else 
	{
		if	(execve(cmd->data, (char **)ft_list_to_array(cmd), g_shell.env) == EXIT_FAILURE)
			exit(EXIT_FAILURE);
	}
}

int		ft_allowed_cmd(t_list *cmd)
{
	if	(!ft_strncmp(cmd->data, "exit", ft_strlen(cmd->data)))
	{
		ft_clear_list(&cmd);
		ft_append_elt(&g_garb_cltor, g_garb_cltor);
		ft_clear_list(&g_garb_cltor);
		exit(EXIT_SUCCESS);
	}
	else if	(!ft_strncmp(cmd->data, "cd", ft_strlen(cmd->data)))
		return (cd_cmd(cmd));
	else if (!ft_strncmp(cmd->data, "echo", ft_strlen(cmd->data)))
		echo_cmd(cmd);
	else if	(!ft_strncmp(cmd->data, "pwd", ft_strlen(cmd->data)))
		ft_putendl_fd(g_shell.cwd, 1);
	else if	(!ft_strncmp(cmd->data, "export", ft_strlen(cmd->data)))
	{
		if (ft_strchr(cmd->next->data, '='))
			ft_append_env(cmd->next->data);
	}
	else if	(!ft_strncmp(cmd->data, "unset", ft_strlen(cmd->data)))
		ft_retreive_env(cmd->next->data);
	else if	(!ft_strncmp(cmd->data, "env", ft_strlen(cmd->data)))
		ft_show_env();
	else
		ft_exec(cmd);
	return (EXIT_SUCCESS);
}

int	ft_redirect_cmd(t_list *cmd)
{
	if (ft_allowed_cmd(cmd) == EXIT_FAILURE && 
		ft_strncmp(cmd->data, "cd", ft_strlen(cmd->data)))
	{
		ft_putstr_fd(cmd->data, 1);
		ft_putendl_fd(": command not found", 1);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}