/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shit_just_got_serious.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarin <rliou-ke@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 16:32:01 by akarin            #+#    #+#             */
/*   Updated: 2016/05/05 18:43:50 by akarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rms.h"

void		print_pizza(t_dome *head, int nbants, int opt)
{
	if (!opt)
		return ;
	while (head)
	{
		if (head->pizza >= 0)
		{
			ft_putstr("Amount of ants bypassing @So Gusto: ");
			ft_putnbr(head->pizza);
			ft_putchar('\n');
			if (head->pizza != nbants)
			{
				ft_putnbr(nbants - head->pizza);
				ft_putstr(" ants are still starving 😣");
			}
			return ;
		}
		head = head->next;
	}
}

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

void		shit_just_got_serious(t_lm box)
{
	t_dome	*end;
	int		count;

	count = 1;
	end = get_room(box.rooms, EDROOM);
	while (42)
	{
//		if (!opt['s'])
			little_ant_gonna_lift(box.ants, box.rooms, end);
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
