/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 10:05:35 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/01 23:14:31 by akarin           ###   ########.fr       */
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

t_list		*instantiate_ants(int n, t_dome *start)
{
	t_ant	*ant;
	t_list	*lst_ant;
	t_list	*new;
	
	lst_ant = NULL;
	while (start != NULL)
	{
		if (start->type == STROOM)
			break ;
		start = start->next;
	}
	while (n)
	{
		ant = init_ant(n, start);
		if (!(new = malloc(sizeof(*new))))
			ft_exit_error("instantiate_ants: new: malloc");
		new->content = ant;
		ft_lstadd(&lst_ant, new);
		n--;
	}
	return (lst_ant);
}
/*
void		suburashiki_kono_sekai(t_list **ant)
{
	t_dome	*room;

	room = ((t_ant *)(*ant)->content)->room;
	while (room != NULL)
	{

	}
}

void		shit_just_got_serious(t_list *ants)
{
	if (((t_ant *)ants->content)->room->type == EDROOM)
		return ;
	while (ants != NULL)
	{
		subarashiki_kono_sekai(&ants);
		ants = ants->next;
	}
	shit_just_got_serious(ants);
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
//	shit_just_got_serious(ants);
	print_ant_status(ants);
// DEBUT	TESTS
//	print_room_links("7", rooms);
	ft_putendl("\nParsing done:");
	print_rooms(rooms);
	print_file(file);
// FIN		TESTS
	return (0);
}
