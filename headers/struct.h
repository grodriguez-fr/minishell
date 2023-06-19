/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:39:05 by astachni          #+#    #+#             */
/*   Updated: 2023/06/19 13:26:42 by gurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H

# define STRUCT_H

# include "minishell.h"

typedef struct s_env_p
{
	char			*key;
	char			*value;
	struct s_env_p	*next;
}	t_env_p;

typedef struct s_exec
{
	char			*comp_pipe;
	char			**files_out;
	char			**files_out_a;
	int				is_append;
	char			**files_in;
	char			**here_docs;
	int				is_heredoc;
	char			**args;
	char			*cmd_name;
	int				pid;
	struct s_exec	*next;
}	t_exec;

typedef struct s_mini
{
	t_env_p		*env;
	t_exec		*ex;
	char		*to_display;
	char		*input;
}	t_mini;

#endif
