/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 20:40:09 by abarot            #+#    #+#             */
/*   Updated: 2020/09/15 13:40:33 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// todo list :
// 		- gestion pipeline
// 		- gestion >> > < et | :
//			- gestion pipe dans redirection cmd
// 		- cd $azezaea ==> chaine nulle
// 		- 'echo azezaeza'
// 		- pb gestion des elt dans "" et '' -> si "string test "'"" ex : cd ""'"$HOME"'""
// 		- gestion memory leeks echo

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
#include <errno.h>
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
	char			**envp;
	char			**argv;
	char			*tilde;
	pid_t			cpid;
	struct stat		stat;
}				t_shell;

t_shell g_shell;
t_list	*g_garb_cltor;

void	ft_init_shell(char **av, char **envp);
void	ft_set_cwd();
void	ft_show_prompt_line();
char	*ft_multiline_mng(char *line);
char	*ft_get_cmd_r(char *cmd_line);
int 	ft_parse_cmdline(char *cmd_line);
int		ft_redirect_cmd(t_list *cmd, int fd_in, int fd_out);
int		ft_redirection(char *cmd, int *fd_in, int *fd_out);
void	ft_show_env(char **envp);
void	ft_append_env(char *str);
char	*ft_get_value(char **envp, char *var, char sep);
char	*ft_search_var(char **envp, char *str);
void	ft_retreive_env(char *str);
void	ft_inthandler();
void 	ft_quithandler(); 
#endif