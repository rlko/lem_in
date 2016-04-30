/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 10:05:35 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/04/30 19:36:26 by rliou-ke         ###   ########.fr       */
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

int			find_possibilities()


int			main(void)
{
	ft_putendl("DEBUT: main");
	int		anb;
	t_list	*file;
	t_dome	*rooms;
	t_list	*paths;

	file = NULL;
	rooms = NULL;
	paths = NULL;
	if (!(anb = find_antsnbr(&file)))
		return (ft_error("ERROR"));
	rooms = find_rooms(&file);
	find_connections(&file, &rooms);
	if (!find_possibilities(&rooms))
		return (ft_error("ERROR"));
// DEBUT	TESTS
	print_room_links("7", rooms);
	ft_putendl("\nParsing done:");
	print_rooms(rooms);
	print_file(file);
// FIN		TESTS
	ft_putendl("FIN: main");
	return (0);
}
