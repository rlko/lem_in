/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_le-min.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 14:10:05 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/04/28 14:15:11 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rms.h"

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
