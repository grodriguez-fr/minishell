/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:47:23 by astachni          #+#    #+#             */
/*   Updated: 2023/07/15 13:28:02 by astachni         ###   ########.fr       */
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
int		increment_shell_level(t_env_p *env);

void	launch_minishell_img(void);
void	get_to_display(t_mini *mini);
void	prompt(t_mini mini);
void	clear_env(t_env_p **env, void (*del)(void*));
void	exit_minishell(t_mini *mini, int code);
void	error(t_mini *mini, char *message, char **strs);
void	signal_handler(int sign, siginfo_t *info, void	*context);
void	init_signals(t_mini mini);
void	exit_minishell_nohd(t_mini *mini, int code);

char	**get_args(char *cmd);
char	*allocate_new_string(int size);
void	copy_argument(char *str, int start_index, char *new_str);
char	*cpy_args(char *str);
int		find_next_argument_index(char *cmd, int current_index);
int		get_argument_size(char *str, int start_index);
t_mini	parse_and_exec(char *input, t_mini mini);
t_exec	*parse_cmd(char *input, t_exec *exec, t_mini mini);
char	**ft_split_pipe(char *str, char sep);
int		skip_space(int i, char *str);
int		ft_is_command(char *str, int i, char sep, int *is_command);
int		count_space(char *src, int i);
int		*skip_quote(char *str, int *i, size_t *is_open_d, size_t *is_open_s);
char	**cpy_last(char **dest, char *src, int c, int j);
void	add_cmd(t_exec **lst, char	*cmd_name, char **args, char *all_pipe);
void	create_env(t_env_p **env, t_mini mini);
char	**in_out(char **fd, char *str, char sep);
char	*change_cmdf_here_append(char *str, char *sep);
char	**hear_append(char **fd, char *str, char *sep);
char	*cpy(char *str, char *fd, size_t i);
int		take_last_redirect(char *cmd);
size_t	count_sep(char *str, char sep);
char	*change_cmdf(char *str, char sep);
int		is_open(char *str, int i, size_t is_open, char c);
char	**take_var(t_mini *mini, char *comm, char **args);
int		ft_strstr(const char *haystack, const char *needle);

int		echo(t_exec *ex);
int		export(t_mini *mini, t_exec *ex);
int		cd(t_mini *mini, t_exec *ex);
int		pwd(t_mini *mini);
int		unset(t_mini *mini, t_exec *ex);
int		env(t_mini *mini);
int		exit_builtin(t_mini *mini, t_exec *ex);
t_env_p	*sort_env(t_env_p *env);
char	**export_split(char *input);
int		write_ret_export_error(char *var);

char	**convert_env(t_mini *mini);
void	free_env(char **envp);
int		exec_all(t_mini *mini);
void	free_split(char **splited);
char	*find_path(t_mini *mini, char *cmd_name);
int		check_redirection(t_exec *current);
int		heredoc(t_mini *mini);
int		res_null(char *res, char *word);
void	init_signal(void);
void	signal_handler_heredoc(int sign, siginfo_t *info, void	*context);
char	*heredoc_file_name(unsigned int nb);
int		open_heredoc(unsigned int i);
int		is_builtin(char *cmd_name);
int		execute_builtin(t_mini *mini, t_exec *ex, char *cmd_name);
int		builtin_env_modifier(char *cmd_name);
char	*get_env_value(t_mini *mini, char *key);
int		replace_or_add(t_mini *mini, char *var);
char	*get_clean_path(char *path);
void	exec_cmd(t_mini *mini, t_exec *current, int p[2], int previous_fd);
int		clean_heredocs(void);
int		is_str_numeric(const char *str);
int		same_string(char *a, char *b);
void	exit_errno(t_mini *mini, int ret);
void	write_not_found(t_mini *mini, char **new_env, char *name);
#endif
