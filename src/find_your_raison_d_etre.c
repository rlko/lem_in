/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_your_raison_d_etre.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 15:38:12 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/07 15:48:44 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rms.h"

static t_dome	*get_next_room(t_dome *current, t_dome *prev)
{
	t_list		*link;
	t_dome		*room;
	t_dome		*dest;

	dest = NULL;
	link = current->adj;
	while (link != NULL)
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

void			reinit_depth(t_dome *rooms)
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

static void		find_libre_pizza(t_ant *ant, t_dome *head, int *opt)
{
	static int	deeeepa = 0;

	if (ant->room->pizza >= 0)
	{
		ft_print_pizzatime(ant, opt);
		ant->ate = 1;
		++ant->room->pizza;
	}
	if (opt['b'] && ant->room->type == PIZZA)
	{
		if (deeeepa == 0)
		{
			deeeepa = 1;
			find_your_raison_d_etre(ant, head, opt);
			deeeepa = 0;
		}
	}
}

void			find_your_raison_d_etre(t_ant *ant, t_dome *head, int *opt)
{
	t_dome		*dest;

	if ((dest = get_next_room(ant->room, ant->prev)))
	{
		ant->prev = ant->room;
		ant->room->occupied = 0;
		ant->room = dest;
		if (ant->room->type != EDROOM)
		{
			ant->room->occupied = 1;
			find_libre_pizza(ant, head, opt);
		}
		ant->played = 1;
		reinit_depth(head);
	}
}
