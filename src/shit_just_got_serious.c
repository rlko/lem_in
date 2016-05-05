/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shit_just_got_serious.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarin <rliou-ke@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 16:32:01 by akarin            #+#    #+#             */
/*   Updated: 2016/05/05 20:19:55 by akarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rms.h"

static int	all_done(t_list *ants)
{
	t_ant	*ant;

	while (ants)
	{
		ant = (t_ant *)ants->content;
		if (ant->room->type != EDROOM)
			return (0);
		ants = ants->next;
	}
	return (1);
}

static void	reset_turn(t_list *ants)
{
	t_ant	*ant;

	while (ants)
	{
		ant = (t_ant *)ants->content;
		ant->played = 0;
		ants = ants->next;
	}
}

static void	subarashiki_kono_sekai(t_dome *current)
{
	t_list	*side;

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

static void	little_ant_gonna_lift(t_lm box, t_dome *ed)
{
	t_ant	*ant;
	t_list	*la;

	la = box.ants;
	while (la != NULL)
	{
		ant = (t_ant *)la->content;
		subarashiki_kono_sekai(ed);
		find_your_raison_d_etre(ant, box.rooms, box.opt);
		la = la->next;
	}
}

void		shit_just_got_serious(t_lm box)
{
	t_dome	*end;
	int		count;

	count = 1;
	end = get_room(box.rooms, EDROOM);
	while (32)
	{
//		if (!opt['s'])
		little_ant_gonna_lift(box, end);
//		else
//			aint_gonna_give_a_shit(ants, hd, end);
		print_turn(box.ants);
		if (all_done(box.ants))
			break ; 
		reset_turn(box.ants);
		reinit_depth(box.rooms);
		++count;
	}
	print_count_turn(count, box.opt['t']);
	print_pizza(box.rooms, box.nb_ants, box.opt['p']);
}
