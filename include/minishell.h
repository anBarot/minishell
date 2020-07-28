/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 20:40:09 by abarot            #+#    #+#             */
/*   Updated: 2020/07/28 12:03:52 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// todo list :
//		- fonction attente commande
//		- gestion pipe dans redirection cmd
//		- fonction replace env ($var -> env) pour echo
//		- get LOGNAME@SESSION_MANAGER

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
# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_YELLOW  "\x1b[33m"
# define ANSI_COLOR_BLUE    "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN    "\x1b[36m"
# define ANSI_COLOR_RESET   "\x1b[0m"
# define PATH_MAX        4096
typedef struct s_list t_list;

struct s_list
{
	char 	*data;
	t_list	*next;
};

typedef struct s_shell
{
	char		*cwd;
	char		**env;
	DIR			*folder;
}				t_shell;

t_shell g_shell;

int		ft_redirect_cmd(t_list *cmd);
// void 	ft_cmd_export(t_list *cmd);
// void 	ft_cmd_unset(t_list *cmd);
void	ft_clear_list(t_list **cmd);
int		ft_list_size(t_list *list);
int		ft_append_elt(t_list **list, char *elt);
void	ft_append_env(char *str);
void	ft_retreive_env(char *str);
#endif