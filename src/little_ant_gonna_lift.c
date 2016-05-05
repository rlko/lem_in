/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_ant_gonna_lift.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarin <rliou-ke@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 16:28:30 by akarin            #+#    #+#             */
/*   Updated: 2016/05/05 16:41:02 by akarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rms.h"

void		subarashiki_kono_sekai(t_dome *current)
{
	t_list		*side;

	side = current->adj;
	while (side != NULL)
	{
		if ((current->depth < ((t_dome *)side->content)->depth\
				   	|| ((t_dome *)side->content)->depth == -1) \
				&& ((t_dome *)side->content)->occupied == 0)
		{
			((t_dome *)side->content)->depth = current->depth + 1;
			subarashiki_kono_sekai(((t_dome *)side->content));
		}
		side = side->next;
	}
}

t_dome		*get_next_room(t_dome *current, t_dome *prev)
{
	t_list *link;
	t_dome	*room;
	t_dome	*dest;

	dest = NULL;
	link = current->adj;
	while (link)
	{
		room = link->content;
		if (!dest && room->depth != -1 && room != prev)
			dest = room;
		else if (dest)
		{
			if (dest->depth > room->depth && room->depth != -1 && room != prev)
			dest = room;
		}
		link = link->next;
	}
	if (dest)
	{
		if (dest->depth < current->depth)
			return (dest);
	}
	return (NULL);
}

void	reinit_depth(t_dome *rooms)
{
	while (rooms)
	{
		if (rooms->occupied)
			rooms->depth = INTMAX;
		else
			rooms->depth = rooms->type == EDROOM ? 0 : -1;
		rooms = rooms->next;
	}
}

void	little_ant_gonna_lift(t_list *la, t_dome *hd, t_dome *ed)
{
	t_ant	*ant;
	t_dome	*dest;

	while (la != NULL)
	{
		ant = (t_ant *)la->content;
		subarashiki_kono_sekai(ed);
		if ((dest = get_next_room(ant->room, ant->prev)))
		{
			ant->prev = ant->room;
			ant->room->occupied = 0;
			ant->room = dest;
			if (ant->room->type != EDROOM)
				dest->occupied = 1;
			ant->played = 1;
			reinit_depth(hd);
		}
		la = la->next;
	}
}
