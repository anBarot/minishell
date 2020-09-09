/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 15:15:17 by abarot            #+#    #+#             */
/*   Updated: 2020/09/09 18:16:35 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_create_cmdlist(char *cmd)
{
	t_list	*cmdlist;
	char	*elt;

	cmdlist = 0;
	elt = 0;
	while (*cmd)
	{
		if (*cmd == '\"' || *cmd == '\'')
			elt = ft_get_string(cmd);
		else
			elt = ft_get_word(cmd);
		if (elt)
			ft_append_elt(&cmdlist, elt);
		cmd += ft_strlen(elt);
		while (*cmd == ' ')
			cmd++;
		if (!ft_strlen(elt))
			break;
	}
	if (ft_redirect_cmd(cmdlist) == EXIT_FAILURE)
	{
		ft_putstr_fd(cmdlist->data, 1);
		ft_putstr_fd(": command not found\n", 1);
		ft_clear_list(&cmdlist);
		return (EXIT_FAILURE);
	}
	ft_clear_list(&cmdlist);
	return (EXIT_SUCCESS);
}

int 	ft_parse_cmdline(char *cmd_line)
{
	char	*cmd;
	int		cmd_s;
	int		cmd_end;

	cmd_s = 0;
	cmd_end = 0;
	if (!cmd_line)
		return (EXIT_SUCCESS);
	while (cmd_line[cmd_end])
	{
		while (cmd_line[cmd_end] && (cmd_line[cmd_end] != ';' || 
				(ft_count_elt(cmd_line + cmd_end, "\"") % 2 == 1 ||
					ft_count_elt(cmd_line + cmd_end, "\'") % 2 == 1)))
				cmd_end++;
		cmd = ft_substr(cmd_line, cmd_s, (cmd_end - cmd_s));
		if (cmd)
			ft_append_elt(&g_garb_cltor, cmd);
		// if (ft_syntax_error(cmd_line))
		// {
		// 	ft_putstr_fd("minishell: syntax error near unexpected token", 1);
		// 	return (EXIT_FAILURE);
		// }
		ft_create_cmdlist(cmd);
		cmd_end++;
		cmd_s = cmd_end;
	}
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
		res = ft_replace_in_str(res, var_dol, 
			ft_get_value(g_shell.env, var, '='));
	ft_append_elt(&(g_garb_cltor), res);
	free(var);
	free(var_dol);
	return (res);
}

char	*ft_get_cmd_r(char *cmd_line)
{
	char	*res;

	res = cmd_line;
	// ajouter $? treatment
	if (*cmd_line == '$' && *(cmd_line + 1) == '?')
		cmd_line++;
	if (*cmd_line == '$' && !(ft_count_elt(cmd_line, "\'") % 2))
		res = ft_replace_var(res, cmd_line);
	cmd_line++;
	while (*cmd_line)
	{
		if (*cmd_line == '~' && !(ft_count_elt(cmd_line, "\'") % 2) 
				&& !(ft_count_elt(cmd_line, "\'") % 2))
			res = ft_replace_in_str(res, "~", g_shell.tilde);
		else if (*cmd_line == '$' && (*(cmd_line - 1) != '\\' &&
			!(ft_count_elt(cmd_line, "\'") % 2)))
			res = ft_replace_var(res, cmd_line);
		cmd_line++;
	}
	return (res);
}

char	*ft_multiline_mng(char *line)
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
