/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astachni <astachni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:47:23 by astachni          #+#    #+#             */
/*   Updated: 2023/04/06 16:47:43 by astachni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H

# define PROTO_H

void	parse_env(char **envp, t_env_p **env);
void	add_to_stack(t_env_p **lst, int j, char *value_to_add);
void	ft_add_back(t_env_p **lst, t_env_p *new);
t_env_p	*ft_last(t_env_p *lst);
t_env_p	*ft_new(char *key, char *value);

#endif