/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_le-min.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 14:10:05 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/02 16:30:15 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rms.h"

void				print_room_links(char *name, t_dome *room)
{
	t_list *lst;

	while (room)
	{
		if (ft_strequ(room->name, name))
		{
			ft_putstr(name);
			ft_pustr("'s connections: ");
			lst = room->adj;
			while (lst)
			{
				ft_putstr(((t_dome *)lst->content)->name);
				ft_putstr(" ");
				lst = lst->next;
			}
		}
		room = room->next;
	}
	ft_putchar('\n');
}

void				print_rooms(t_dome *room)
{
	int i = 0;
	ft_putendl("########### ROOMS ###########");
	while (room)
	{
		ft_putstr("Salle: ");
		ft_putnbr(++i);
		ft_putstr(" Nom: ");
		ft_putstr(room->name);
		ft_putstr(" x: ");
		ft_putstr(room->x);
		ft_putstr(" y: ");
		ft_putstr(room->y);
		ft_putstr(" visited: ");
		ft_putnbr(room->v);
		ft_putstr(" depth: ");
		ft_putnbr(room->depth);
//		ft_putstr(room->v ? "yes" : "no");
		ft_putchar('\n');
		room = room->next;
	}
	ft_putstr("########### ROOMS ###########");
	ft_putchar('\n');
}

void			print_file(t_list *file)
{
	ft_putendl("########### FICHER ###########");
	while (file)
	{
		ft_putendl(file->content);
		file = file->next;
	}
	ft_putendl("########### FICHER ###########");
}

void			print_ant_status(t_list *ant)
{
	while (ant)
	{
		ft_putstr("Ant no #");
		ft_putnbr(((t_ant *)ant->content)->id);
		ft_putstr(" @room: ");
		ft_putendl(((t_ant *)ant->content)->room->name);
		ant = ant->next;
	}
}
