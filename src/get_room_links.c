/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_room_links.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/30 19:09:06 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/04/30 19:21:50 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rms.h"

static int	name_exists(char *name, t_dome *room)
{
	while (room != NULL)
	{
		if (ft_strequ(name, room->name))
			return (1);
		room = room->next;
	}
	return (0);
}

static int	link_isvalid(t_list *lst, t_dome *room)
{
	while (lst != NULL)
	{
		if (!name_exists(lst->content, room))
			return (0);
		lst = lst->next;
	}
	return (1);
}

int			get_room_links(char *line, t_dome **room)
{
	t_list	*lsplit;

	lsplit = ft_lstsplit(line, '-');
	if (ft_lstlen(lsplit) != 2)
		return (0);
	if (!link_isvalid(lsplit, *room))
		return (0);
	fill_connections(lsplit, room);
	return (1);
}
