/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 10:05:35 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/04 13:10:48 by rliou-ke         ###   ########.fr       */
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
			break ;
		lst = lst->next;
	}
	return (lst);
}

t_ant		*init_ant(int n, t_dome *start)
{
	t_ant	*ant;

	if (!(ant = malloc(sizeof(*ant))))
		ft_exit_error("init_ant: ant: malloc");
	ant->id = n;
	ant->room = start;
	ant->moved = 0;
	return (ant);
}

t_list		*instantiate_ants(int n, t_dome *room)
{
	t_ant	*ant;
	t_list	*lst_ant;
	t_list	*new;

	lst_ant = NULL;
	room = get_room(room, STROOM);
	while (n)
	{
		ant = init_ant(n, room);
		if (!(new = malloc(sizeof(*new))))
			ft_exit_error("instantiate_ants: new: malloc");
		new->content = ant;
		ft_lstadd(&lst_ant, new);
		n--;
	}
	return (lst_ant);
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

void		destruct_this_world(t_list *file, t_list *ants, t_dome *rooms)
{
	t_list	*tmp;
	t_dome	*del;

	while (file)
	{
		tmp = file;
		file = file->next;
		ft_strdel((char **)&tmp->content);
		free(tmp);
	}
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

t_dome		*get_next_room(t_dome *current)
{
	t_dome *next;
	t_list *link;
	t_dome	*node;

	link = current->adj;
	while (link)
	{
		node = link->content;
		if (node->depth < current->depth)
			return (node);
		link = link->next;
	}
	return (NULL);
}

static void	reinit_depth(t_dome *rooms)
{
	while (rooms)
	{
		rooms->depth = 0;
		rooms = rooms->next;
	}
}

//		if (((t_ant *)ants->content)->room->type == EDROOM)
void		shit_just_got_serious(t_list *ants, t_dome *head)
{
	t_dome	*end;
	t_dome	*dest;
	t_ant	*ant;

	end = get_room(head, EDROOM);
	while (ants != NULL)
	{
		ant = ants->content;
		subarashiki_kono_sekai(end);
		if ((dest = get_next_room(ant->room)))
		{
			ant->room->occupied = 1;
			ant->moved = 1;
			reinit_end(head);
			if (ant->room->type == EDROOM)
				///;
		}
		ants = ants->next;
	}
	shit_just_got_serious(ants);
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
	ants = instantiate_ants(anb, rooms);	
	subarashiki_kono_sekai(get_room(rooms, EDROOM));
//	shit_just_got_serious(ants, rooms);
//	print_ant_status(ants);
// DEBUT	TESTS
//	print_room_links("7", rooms);
	ft_putendl("\nParsing done:");
	print_rooms(rooms);
	print_file(file);
// FIN		TESTS
	destruct_this_world(file, ants, rooms);
	return (0);
}
