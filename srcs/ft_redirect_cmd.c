/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 16:00:15 by abarot            #+#    #+#             */
/*   Updated: 2020/07/23 18:55:58 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_allowed_cmd(t_list *cmd)
{
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
	}
	// else if (ft_strncmp(cmd->data, "echo", ft_strlen(cmd->data)))
	// 	ft_cmd_echo(cmd);
	// else if	(ft_strncmp(cmd->data, "pwd", ft_strlen(cmd->data)))
	// 	ft_cmd_pwd(cmd);
	// else if	(ft_strncmp(cmd->data, "export", ft_strlen(cmd->data)))
	// 	ft_cmd_export(cmd);
	// else if	(ft_strncmp(cmd->data, "unset", ft_strlen(cmd->data)))
	// 	ft_cmd_unset(cmd);
	// else if	(ft_strncmp(cmd->data, "env", ft_strlen(cmd->data)))
	// 	ft_cmd_env(cmd);
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