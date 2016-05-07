/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_solvable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 15:38:48 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/07 15:38:49 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rms.h"

static int	ft_tasukete(t_dome *aniki)
{
	t_list	*sempai;

	aniki->occupied = 1;
	if (aniki->type == EDROOM)
		return (1);
	sempai = aniki->adj;
	while (sempai != NULL)
	{
		if (((t_dome *)sempai->content)->occupied == 0 && \
				ft_tasukete(((t_dome *)sempai->content)))
		{
			return (1);
		}
		else
			sempai = sempai->next;
	}
	return (0);
}

static void	reinit(t_dome *rooms)
{
	while (rooms)
	{
		rooms->occupied = 0;
		rooms = rooms->next;
	}
}

int			ft_is_solvable(t_dome *room, int *opt)
{
	t_dome	*start;

	start = room;
	while (start != NULL)
	{
		if (start->type == STROOM)
			break ;
		start = start->next;
	}
	if (ft_tasukete(start))
	{
		reinit(room);
		if (opt['c'])
			colorize(room);
		return (1);
	}
	return (0);
}
