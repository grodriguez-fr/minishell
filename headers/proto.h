/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:47:23 by astachni          #+#    #+#             */
/*   Updated: 2023/05/26 16:35:46 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H

# define PROTO_H

# include "minishell.h"
# include <signal.h>

void	parse_env(char **envp, t_env_p **env, t_mini mini);
void	add_to_stack(t_env_p **lst, int j, char *value_to_add, t_mini mini);
void	ft_add_back(t_env_p **lst, t_env_p *new);
t_env_p	*ft_last(t_env_p *lst);
t_env_p	*ft_new(char *key, char *value);
void	free_cmd(t_exec **exec, void (*del)(void*));
t_exec	*ft_last_cmd(t_exec *lst);
void	free_strs(char **strs);
int		ft_isspace(char c);

void	launch_minishell_img(void);
t_mini	get_to_display(t_mini mini);
void	prompt(t_mini mini);
void	clear_env(t_env_p **env, void (*del)(void*));
void	exit_minishell(t_mini *mini);
void	error(t_mini *mini, char *message, char **strs);
void	signal_handler(int sign, siginfo_t *info, void	*context);

char	**get_args(char *cmd);
t_mini	parse_and_exec(char *input, t_mini mini);
t_exec	*parse_cmd(char *input, t_exec *exec, t_mini mini);
char	**ft_split_pipe(char *str, char sep);
void	add_cmd(t_exec **lst, char	*cmd_name, char **args, char *all_pipe);
void	create_env(void);
char	**in_out(char **fd, char *str, char sep);
char	*change_cmdf_here_append(char *str, char *sep);
char	**hear_append(char **fd, char *str, char *sep);
int		take_last_redirect(char *cmd);
size_t	count_sep(char *str, char sep);
char	*change_cmdf(char *str, char sep);

void	echo(t_exec *ex, char *str, int fd);
int		export(t_mini *mini, t_exec *ex);
int		cd(t_mini *mini, t_exec *ex);
int		pwd(t_mini *mini);
int		unset(t_mini *mini, t_exec *ex);
int		env(t_mini *mini);
int		exit_builtin(t_mini *mini, t_exec *ex);

char	**convert_env(t_mini *mini);
void	free_env(char **envp);
int		exec_all(t_mini *mini);
void	free_split(char **splited);
char	*find_path(t_mini *mini, char *cmd_name);
int		check_redirection(t_exec *current);
int		heredoc(t_mini *mini);
int		is_builtin(char *cmd_name);
int		execute_builtin(t_mini *mini, t_exec *ex, char *cmd_name);
int		builtin_env_modifier(char *cmd_name);
char	*get_env_value(t_mini *mini, char *key);
int     replace_or_add(t_mini *mini, char *var);
char    *get_clean_path(char *path);
#endif
