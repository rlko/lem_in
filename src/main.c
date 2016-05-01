/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 10:05:35 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/01 20:30:44 by akarin           ###   ########.fr       */
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

void		shit_just_got_serious(t_list **paths, t_dome *rooms)
{
	(void)paths;
	(void)rooms;
	// [insert smart implementation]	
}

int			main(void)
{
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
	if (!ft_is_solvable(rooms))
		return (ft_error("ERROR"));
	shit_just_got_serious(&paths, rooms);
// DEBUT	TESTS
//	print_room_links("7", rooms);
	ft_putendl("\nParsing done:");
	print_rooms(rooms);
	print_file(file);
// FIN		TESTS
	return (0);
}
