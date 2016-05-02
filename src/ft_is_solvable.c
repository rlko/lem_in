/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_solvable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 13:50:27 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/02 13:52:07 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rms.h"

static int	ft_tasukete(t_dome *aniki)
{
	t_list	*sempai;

	aniki->v = 1;
	if (aniki->type == EDROOM)
		return (1);
	sempai = aniki->adj;
	while (sempai != NULL)
	{
		if (((t_dome *)sempai->content)->v == 0 && \
				ft_tasukete(((t_dome *)sempai->content)))
		{
			aniki->c = 1;
			return (1);
		}
		else
			sempai = sempai->next;
	}
	aniki->c = 0;
	return (0);
}

static void	reinit(t_dome *rooms)
{
	while (rooms)
	{
		rooms->v = 0;
		rooms->c = 0;
		rooms = rooms->next;
	}
}

int			ft_is_solvable(t_dome *room)
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
		return (1);
	}
	return (0);
}
