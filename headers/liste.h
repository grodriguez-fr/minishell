/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liste.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:39:05 by astachni          #+#    #+#             */
/*   Updated: 2023/04/06 14:45:45 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTE_H

# define LISTE_H

typedef struct s_env_p
{
	char	*key;
	char	*value;
	t_env_p	*next;
}	t_env_p;

typedef struct s_mini
{
	*t_env_p	env;
}	t_mini;

#endif