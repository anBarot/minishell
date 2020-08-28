/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 20:40:09 by abarot            #+#    #+#             */
/*   Updated: 2020/08/28 11:12:46 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// todo list :
//		- gestion pipe dans redirection cmd
//		- fonction replace variables env
// 		- option -n echo
// 		- gestion si unset home
// 		- supprimer étape liste -> juste tableau

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

typedef struct s_shell
{
	char		*cwd;
	char		*r_cwd;
	char		**env;
	char		**argv;
	DIR			*folder;
}				t_shell;

t_shell g_shell;
t_list	*g_garb_cltor;

void	ft_set_cwd();
int		ft_redirect_cmd(t_list *cmd);
void	ft_show_env();
void	ft_append_env(char *str);
void	ft_retreive_env(char *str);
char	*ft_get_value(char **env, char *var, char sep);
int		ft_varsize(char *var);
#endif