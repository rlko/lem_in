/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shit_just_got_serious.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarin <rliou-ke@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 16:32:01 by akarin            #+#    #+#             */
/*   Updated: 2016/05/05 17:32:03 by akarin           ###   ########.fr       */
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

void		shit_just_got_serious(t_list *ants, t_dome *hd, int *opt)
{
	t_dome	*end;
	int		count;

	count = 1;
	end = get_room(hd, EDROOM);
	while (42)
	{
//		if (!opt['s'])
			little_ant_gonna_lift(ants, hd, end);
//		else
//			aint_gonna_give_a_shit(ants, hd, end);
		print_turn(ants);
		if (all_done(ants))
			break ; 
		reset_turn(ants);
		reinit_depth(hd);
		++count;
	}
	print_count_turn(count, opt['t']);
}
