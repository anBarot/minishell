/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ft.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 18:44:37 by abarot            #+#    #+#             */
/*   Updated: 2020/07/28 15:19:54 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_varsize(char *var)
{
	int i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (!var[i])
		return (0);
	return (i);
}

char	*ft_get_varval(char *var, char sep)
{
	while (*var && *var != sep)
		var++;
	if (*var)
		var++;
	return (var);
}

void	ft_append_env(char *str)
{
	int i;

	i = 0;
	while (g_shell.env[i] && ft_strncmp(str, g_shell.env[i], 
			ft_max_value(ft_varsize(g_shell.env[i]), ft_varsize(str))))
		i++;
	if (!g_shell.env[i])
	{
		g_shell.env[i] = ft_strdup(str);
		g_shell.env[i + 1] = 0;
	}
	else 
		g_shell.env[i] = ft_strdup(str);
}

void ft_retreive_env(char *str)
{
	int i;

	i = 0;
	while (g_shell.env[i] && ft_strncmp(str, g_shell.env[i], ft_strlen(str)))
		i++;
	if (!ft_strncmp(str, g_shell.env[i], ft_strlen(str)))
	{
		free(g_shell.env[i]);
		while (g_shell.env[i + 1])
		{
			g_shell.env[i] = g_shell.env[i + 1];
		}
			g_shell.env[i] = 0;
	}
}