/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 10:05:35 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/02 20:42:54 by rliou-ke         ###   ########.fr       */
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

t_ant		*init_ant(int n, t_dome *start, t_dome *end)
{
	t_ant	*ant;

	if (!(ant = malloc(sizeof(*ant))))
		ft_exit_error("init_ant: ant: malloc");
	ant->id = n;
	ant->room = start;
	ant->end = end;
	ant->moved = 0;
	return (ant);
}

t_list		*instantiate_ants(int n, t_dome *room)
{
	t_ant	*ant;
	t_list	*lst_ant;
	t_list	*new;
	t_dome	*end;

	lst_ant = NULL;
	end = get_room(room, EDROOM);
	room = get_room(room, STROOM);
	while (n)
	{
		ant = init_ant(n, room, end);
		if (!(new = malloc(sizeof(*new))))
			ft_exit_error("instantiate_ants: new: malloc");
		new->content = ant;
		ft_lstadd(&lst_ant, new);
		n--;
	}
	return (lst_ant);
}

int			depth_able(void *prev, void *curr)
{
	if (curr != prev || ((t_dome *)curr)->type != EDROOM)
		return (1);
	return (0);
}

void		subarashiki_kono_sekai(t_dome *room, t_dome *current)
{
	static void	*prev = NULL;
	t_list		*side;

	if (room == current)
		return ;
	side = current->adj;
	while (side != NULL)
	{
//		(void)prev;
		if (depth_able(prev, side->content))
		{
			if ((((t_dome *)side->content)->depth < current->depth + 1) || ((t_dome *)side->content)->depth == -1)
				((t_dome *)side->content)->depth = current->depth + 1;
		}
		side = side->next;
	}
	side = current->adj;
	while (side != NULL)
	{
		if (((t_dome *)side->content)->v == 0)
		{
			((t_dome *)side->content)->v = 1;
			prev = current;
			subarashiki_kono_sekai(room, ((t_dome *)side->content));
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
		free(tmp->content);
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
		free(del->name);
		free(del->x);
		free(del->y);
		free(del);
	}
}
/*
void		shit_just_got_serious(t_list **ants)
{
	if (((t_ant *)ants->content)->room->type == EDROOM)
		return ;
	subarashiki_kono_sekai(((t_ant *)ants->content)->room, ((t_ant *)ants->content)->end);
//	while (ants != NULL)
//	{
//		ants = ants->next;
//	}
//	shit_just_got_serious(ants);
}
*/
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
	subarashiki_kono_sekai(((t_ant *)ants->content)->room, ((t_ant *)ants->content)->end);
//	shit_just_got_serious(ants);
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
