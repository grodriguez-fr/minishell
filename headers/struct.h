/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:39:05 by astachni          #+#    #+#             */
/*   Updated: 2023/04/07 19:05:16 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H

# define STRUCT_H

typedef struct s_env_p
{
	char			*key;
	char			*value;
	struct s_env_p	*next;
}	t_env_p;

typedef struct s_exec
{
	int				fd_out; //redirection de la sortie de la commande
	int				fd_in; //redirection de l'entree de la commande
	int				append_mode; //<< ou <, en gros on ajoute ou on remplace
	char			**args; // les arguments a transmettre a la commande
	char			*cmd_name;
	struct s_exec	*next; // la prochaine commande a executer
}	t_exec;

typedef struct s_mini
{
	t_env_p		*env;
	t_exec		*ex;
}	t_mini;

#endif