/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:39:05 by astachni          #+#    #+#             */
/*   Updated: 2023/05/24 14:07:49 by astachni         ###   ########.fr       */
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
	char			**files_out; //redirection de la sortie de la commande
	char			**files_out_a; //redirection de la sortie de la commande
	int				is_append;
	char			**files_in; //redirection de l'entree de la commande
	char			**here_docs; //redirection de l'entree de la commande
	int				is_heredoc;
	char			**args; // les arguments a transmettre a la commande
	char			*cmd_name;
	struct s_exec	*next; // la prochaine commande a executer
}	t_exec;

typedef struct s_mini
{
	t_env_p		*env;
	t_exec		*ex;
	char		*to_display;
	char		*input;
    int         command_return;
}	t_mini;

#endif
