/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:47:23 by astachni          #+#    #+#             */
/*   Updated: 2023/04/24 17:03:57 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H

# define PROTO_H

# include "struct.h"

void	parse_env(char **envp, t_env_p **env, t_mini mini);
void	add_to_stack(t_env_p **lst, int j, char *value_to_add, t_mini mini);
void	ft_add_back(t_env_p **lst, t_env_p *new);
t_env_p	*ft_last(t_env_p *lst);
t_env_p	*ft_new(char *key, char *value);
void	free_cmd(t_exec **exec, void (*del)(void*));

void	launch_minishell_img(void);
void	prompt(t_mini mini);
void	clear_env(t_env_p **env, void (*del)(void*));
void	exit_minishell(t_mini *mini);
void	error(t_mini *mini, char *message);
void	signal_handler(int sign);

t_mini	parse_and_exec(char *input, t_mini mini);
t_exec	*parse_cmd(char *input, t_exec *exec);
void	add_cmd(t_exec **lst, char	*cmd_name, char **args);
t_mini	file_in_out(t_mini mini);
void	create_env(void);

void	echo(t_mini mini);

#endif