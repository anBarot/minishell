/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ft.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 18:44:37 by abarot            #+#    #+#             */
/*   Updated: 2020/09/07 11:23:38 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_show_env()
{
	int	i;

	i = 0;
	while (g_shell.env[i])
	{
		ft_putendl_fd(g_shell.env[i], 1);
		i++;
	}
}

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

char	*ft_get_value(char **env, char *var, char sep)
{
	int i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], var, 
						ft_max_value(ft_varsize(env[i]), ft_varsize(var))))
		i++;
	if (ft_strchr(env[i], sep))
		return (ft_strchr(env[i], sep) + 1);
	return (0);
}

void	ft_append_env(char *str)
{
	int i;

	i = 0;
	if (!ft_strchr(str, '='))
		return ;
	while (g_shell.env[i] && ft_strncmp(str, g_shell.env[i], 
			ft_max_value(ft_varsize(g_shell.env[i]), ft_varsize(str))))
		i++;
	if (!g_shell.env[i])
	{
		g_shell.env[i] = ft_strdup(str);
		ft_append_elt(&g_garb_cltor, g_shell.env[i]);
		g_shell.env[i + 1] = 0;
	}
	else 
		g_shell.env[i] = ft_strdup(str);
}

void ft_retreive_env(char *str)
{
	int i;

	i = 0;
	while (g_shell.env[i] && ft_strncmp(str, g_shell.env[i], 
			ft_max_value(ft_varsize(g_shell.env[i]), ft_varsize(str))))
		i++;
	if (!ft_strncmp(str, g_shell.env[i], ft_strlen(str)))
	{
		while (g_shell.env[i + 1])
		{
			g_shell.env[i] = g_shell.env[i + 1];
			i++;
		}
			g_shell.env[i] = 0;
	}
}
