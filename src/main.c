/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 10:05:35 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/04 23:03:34 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rms.h"

t_list		**ft_lsttower(t_list **head, char *str)
{
	t_list	*new;
	size_t	len;

	if (!(new = malloc(sizeof(*new))))
		ft_exit_error("ft_lsttower: new: malloc");
	len = ft_strlen(str);
	if (!(new->content = malloc(sizeof(char *) * (len + 1))))
		ft_exit_error("ft_lsttower: new->content: malloc");
	ft_strcpy(new->content, str);
	new->content_size = len;
	ft_lstappend(head, new);
	return (head);
}

t_dome		*get_room(t_dome *lst, enum e_type type)
{
	while (lst != NULL)
	{
		if (lst->type == type)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void		subarashiki_kono_sekai(t_dome *current)
{
	static void	*prev = NULL;
	t_list		*side;

	side = current->adj;
	while (side != NULL)
	{
		if ((current->depth < ((t_dome *)side->content)->depth\
				   	|| ((t_dome *)side->content)->depth == -1) \
				&& ((t_dome *)side->content)->occupied == 0)
		{
			prev = current;
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

void		reset_turn(t_list *ants)
{
	t_ant	*ant;

	while (ants)
	{
		ant = (t_ant *)ants->content;
		ant->played = 0;
		ants = ants->next;
	}
}

static void	reinit_depth(t_dome *rooms)
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

int			all_done(t_list *ants)
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

void		update_ant_data(t_ant *ant, t_dome *dest)
{
	ant->prev = ant->room;
	ant->room->occupied = 0;
	ant->room = dest;
	if (ant->room->type != EDROOM)
		dest->occupied = 1;
	ant->played = 1;
}

void		little_ant_gonna_be_smart(t_list *lsta, t_dome *head, t_dome *end)
{
	t_ant	*ant;
	t_dome	*dest;

	while (lsta != NULL)
	{
		ant = (t_ant *)lsta->content;
		subarashiki_kono_sekai(end);
		if ((dest = get_next_room(ant->room, ant->prev)))
		{
			update_ant_data(ant, dest);
			reinit_depth(head);
		}
		lsta = lsta->next;
	}
}

void		shit_just_got_serious(t_list *ants, t_dome *head)
{
	t_dome	*end;
	int		count;

	count = 1;
	end = get_room(head, EDROOM);
	while (42)
	{
		little_ant_gonna_be_smart(ants, head, end);
		print_turn(ants);
		if (all_done(ants))
			break ; 
		reset_turn(ants);
		reinit_depth(head);
		++count;
	}
	print_count_turn(count, 0);
}

void		the_world_ends_without_you(t_list *ants, t_dome *rooms)
{
	t_list	*tmp;
	t_dome	*del;

	while (ants)
	{
		tmp = ants;
		ants = ants->next;
		free(tmp);
	}
	while (rooms)
	{
		del = rooms;
		rooms = rooms->next;
		while (del->adj)
		{
			tmp = del->adj;
			del->adj = del->adj->next;
			free(tmp);
		}
		ft_strdel(&del->name);
		ft_strdel(&del->x);
		ft_strdel(&del->y);
		free(del);
	}
}

int			main(void)
{
	int		anb;
	t_list	*file;
	t_dome	*rooms;
	t_list	*ants;

	file = NULL;
	if (!(anb = find_antsnbr(&file)))
		return (ft_error("ERROR"));
	rooms = find_rooms(&file);
	find_connections(&file, &rooms);
	if (!ft_is_solvable(rooms))
		return (ft_error("ERROR"));
	print_file_and_bye(&file);
	ants = instantiate_ants(anb, rooms);	
	shit_just_got_serious(ants, rooms);
	the_world_ends_without_you(ants, rooms);
	return (0);
}
