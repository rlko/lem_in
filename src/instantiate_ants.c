/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instantiate_ants.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 21:14:30 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/07 15:40:53 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rms.h"

t_ant		*init_ant(int n, t_dome *start)
{
	t_ant	*ant;

	if (!(ant = malloc(sizeof(*ant))))
		ft_exit_error("init_ant: ant: malloc");
	ant->id = n;
	ant->room = start;
	ant->prev = start;
	ant->played = 0;
	ant->ate = 0;
	return (ant);
}

t_list		*instantiate_ants(int n, t_dome *room)
{
	t_ant	*ant;
	t_list	*lst_ant;
	t_list	*new;

	lst_ant = NULL;
	room = get_room(room, STROOM);
	while (n)
	{
		ant = init_ant(n, room);
		if (!(new = malloc(sizeof(*new))))
			ft_exit_error("instantiate_ants: new: malloc");
		new->content = ant;
		ft_lstadd(&lst_ant, new);
		n--;
	}
	return (lst_ant);
}
