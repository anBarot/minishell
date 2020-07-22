/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 20:40:09 by abarot            #+#    #+#             */
/*   Updated: 2020/07/22 17:34:01 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// todo list :
//		- fonction attente commande
//		- structure environnement ==> recreate env
//		- gestion pipe dans redirection cmd


#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>

typedef struct s_list t_list;

struct s_list
{
	char 	*data;
	t_list	*next;
};

typedef struct s_shell
{
	t_list		*env;
	DIR			*dir;
}				t_shell;

int		ft_redirect_cmd(t_list *cmd);
void 	ft_cmd_echo(t_list *cmd);
void 	ft_cmd_cd(t_list *cmd);
void 	ft_cmd_pwd(t_list *cmd);
void 	ft_cmd_export(t_list *cmd);
void 	ft_cmd_unset(t_list *cmd);
void 	ft_cmd_env(t_list *cmd);
void	ft_exit_shell(t_list *cmd);
#endif