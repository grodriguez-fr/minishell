/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:39:05 by astachni          #+#    #+#             */
/*   Updated: 2023/04/06 15:28:27 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H

# define STRUCT_H

typedef struct s_env_p
{
	char	*key;
	char	*value;
	t_env_p	*next;
}	t_env_p;

typedef struct s_mini
{
	*t_env_p	env;
	t_exec		*ex;
}	t_mini;

typedef struct s_exec
{
	int	fd_out; //redirection de la sortie de la commande
	int	fd_in; //redirection de l'entree de la commande
	bool	append_mode; //<< ou <, en gros on ajoute ou on remplace
	s_exec *next; // la prochaine commande a executer
	char	**args; // les arguments a transmettre a la commande
}	t_exec;
#endif