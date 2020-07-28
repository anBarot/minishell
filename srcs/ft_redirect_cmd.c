/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 16:00:15 by abarot            #+#    #+#             */
/*   Updated: 2020/07/29 00:26:04 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_allowed_cmd(t_list *cmd)
{
	int i;
	
	i = 0;
	if	(!ft_strncmp(cmd->data, "exit", ft_strlen(cmd->data)))
	{
		ft_clear_list(&cmd);
		exit(EXIT_SUCCESS);
	}
	else if	(!ft_strncmp(cmd->data, "cd", ft_strlen(cmd->data)))
	{
		if (ft_list_size(cmd) == 1)
			return (EXIT_SUCCESS);
		if (ft_list_size(cmd) > 2)
		{
			ft_putstr_fd("minishell: cd: too many arguments\n", 1);
			return (EXIT_FAILURE);
		}
		if (chdir(cmd->next->data) == -1)
		{
			ft_putstr_fd("minishell: cd: ", 1);
			ft_putstr_fd(cmd->next->data, 1);
			ft_putstr_fd(": No such file or directory\n", 1);
			return (EXIT_FAILURE);
		}
		else 
		{
			g_shell.cwd = getcwd(g_shell.cwd, PATH_MAX);
			g_shell.r_cwd = ft_replace_in_str(g_shell.cwd, ft_get_value(g_shell.env, "HOME", '='), "~");
		}
	}
	else if (!ft_strncmp(cmd->data, "echo", ft_strlen(cmd->data)))
	{
		cmd = cmd->next;
		while (cmd->next)
		{
			ft_putstr_fd(cmd->data, 1);
			cmd = cmd->next;
			write(1, " ", 1);
		}
		ft_putstr_fd(cmd->data, 1);
		write(1, "\n", 1);
	}
	else if	(!ft_strncmp(cmd->data, "pwd", ft_strlen(cmd->data)))
	{	
		ft_putstr_fd(g_shell.cwd, 1);
		write (1, "\n" , 1);
	}
	else if	(!ft_strncmp(cmd->data, "export", ft_strlen(cmd->data)))
	{
		if (ft_strchr(cmd->next->data, '='))
			ft_append_env(cmd->next->data);
	}
	else if	(!ft_strncmp(cmd->data, "unset", ft_strlen(cmd->data)))
		ft_retreive_env(cmd->next->data);
	else if	(!ft_strncmp(cmd->data, "env", ft_strlen(cmd->data)))
	{
		while (g_shell.env[i])
		{
			ft_putstr_fd(g_shell.env[i], 1);
			write(1, "\n", 1);
			i++;
		}
	}
	else
	{
		ft_putstr_fd(cmd->data, 1);
		ft_putstr_fd(": command not found\n", 1);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_redirect_cmd(t_list *cmd)
{
	if (ft_allowed_cmd(cmd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}