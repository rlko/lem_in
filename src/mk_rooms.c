/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mk_rooms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 13:57:40 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/05 18:24:19 by akarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rms.h"

static int		data_are_unique(t_dome *head, t_list *lst)
{
	int			x;
	int			y;
	t_dome		*tmp;

	if (!ft_isnumber(lst->next->content) && \
			!ft_isnumber(lst->next->next->content))
		return (0);
	x = ft_atoi(lst->next->content);
	y = ft_atoi(lst->next->next->content);
	tmp = head;
	while (tmp != NULL)
	{
		if (ft_strequ(lst->content, tmp->name))
			return (0);
		tmp = tmp->next;
	}
	tmp = head;
	while (tmp != NULL)
	{
		if (x == ft_atoi(tmp->x) && y == ft_atoi(tmp->y))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

static int		count_char(char *str, char c)
{
	int i;

	i = 0;
	while (*str)
	{
		if (*str == c)
			++i;
		++str;
	}
	return (i);
}

static int		split_parse(char *line, t_list **lst, t_dome *head)
{
	int			nb_node;
	char		*str;

	if (count_char(line, ' ') != 2)
		return (0);
	if (!(*lst = ft_lstsplit(line, ' ')))
		ft_exit_error("mk_rooms: lst: ft_lstsplit");
	nb_node = ft_lstlen(*lst);
	if (ft_strchr(line, '-'))
	{
		if (nb_node == 1)
		{
			ft_strdel(&line);
			return (0);
		}
	}
	str = (*lst)->content;
	if (nb_node == 3 && !ft_strchr(str, '-') && \
			str[0] != 'L')
	{
		if (data_are_unique(head, *lst))
			return (1);
	}
	ft_exit_error("ERROR");
	return (-42);
}

static t_dome	*domebuilder(t_dome *head, t_dome *room)
{
	t_dome		*tmp;

	if (head == NULL)
		head = room;
	else
	{
		tmp = head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = room;
	}
	return (head);
}

int				mk_rooms(t_dome **head, char **prev, char *line, int *opt)
{
	t_dome		*room;
	t_list		*lst;

	if (!line[0])
		ft_exit_error("ERROR");
	if (!split_parse(line, &lst, *head))
		return (0);
	if (!(room = malloc(sizeof(*room))))
		ft_exit_error("mk_rooms: room: malloc");
	room->adj = NULL;
	room->next = NULL;
	room->occupied = 0;
	assign_type(&room, *prev, opt);
	room->depth = room->type == EDROOM ? 0 : -1;
	room->pizza = room->type == PIZZA && opt['p'] ? 0 : -1;
	assign_room(lst, &room);
	if (*prev)
		*prev = NULL;
	*head = domebuilder(*head, room);
	return (1);
}
