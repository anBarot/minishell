/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 16:00:15 by abarot            #+#    #+#             */
/*   Updated: 2020/07/22 17:25:24 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_allowed_cmd(char *cmd)
{
	if (ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		ft_cmd_echo();
	else if	(ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		ft_cmd_cd();
	else if	(ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		ft_cmd_pwd();
	else if	(ft_strncmp(cmd, "export", ft_strlen(cmd)))
		ft_cmd_export();
	else if	(ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		ft_cmd_unset();
	else if	(ft_strncmp(cmd, "env", ft_strlen(cmd)))
		ft_cmd_env();
	else if	(ft_strncmp(cmd, "exit", ft_strlen(cmd)))
		ft_exit_shell();
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_redirect_cmd(t_list *cmd)
{
	printf("\n---enterring redirect cmd---\n");
	printf("\ncommande : %s \n", cmd->data);
	if (ft_allowed_cmd(cmd->data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}