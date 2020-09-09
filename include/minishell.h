/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 20:40:09 by abarot            #+#    #+#             */
/*   Updated: 2020/09/09 18:33:22 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// todo list :
//		- droits sur ex (S_IFREG et S_IXUSR)
//		- gestion pipe dans redirection cmd
// 		- gestion memory leeks echo
//		- syntax error : si | | ou ;  ;  ==> ft_syntax_error

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
	char			*cwd;
	char			*r_cwd;
	char			**env;
	char			**argv;
	char			*tilde;
	char			*user;
	pid_t			cpid;
	struct stat		stat;
}				t_shell;

t_shell g_shell;
t_list	*g_garb_cltor;

void	ft_init_shell(char **av, char **envp);
void	ft_set_cwd();
char	*ft_multiline_mng(char *line);
char	*ft_get_cmd_r(char *cmd_line);
int 	ft_parse_cmdline(char *cmd_line);
int		ft_redirect_cmd(t_list *cmd);
void	ft_show_env();
void	ft_append_env(char *str);
char	*ft_get_value(char **env, char *var, char sep);
void	ft_retreive_env(char *str);
void	ft_inthandler();
void 	ft_quithandler(); 
void	ft_set_cwd();
void	ft_show_current_dir();
#endif