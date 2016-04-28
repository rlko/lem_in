/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 13:59:47 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/04/28 14:06:18 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rms.h"

void		assign_room(t_list *lst, t_dome **room)
{
	t_list	*tmp;

	(*room)->name = lst->content;
	(*room)->x = lst->next->content;
	(*room)->y = lst->next->next->content;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

void		assign_type(t_dome **room, char *prev)
{
	if (ft_strequ("##start", prev))
		(*room)->type = STROOM;
	else if (ft_strequ("##end", prev))
		(*room)->type = EDROOM;
	else
		(*room)->type = RGROOM;
}
