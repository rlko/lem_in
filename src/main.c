/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 10:05:35 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/01 15:36:05 by akarin           ###   ########.fr       */
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

int			ft_pathfinder(t_dome *alst)
{
	t_list *side;

	(alst)->v = 1;
	if ((alst)->type == EDROOM)
		return (1);
	side = (alst)->adj;
	while (side != NULL)
	{
		if (((t_dome *)(side->content))->v == 0 && \
				ft_pathfinder(((t_dome *)(side->content))))
				return (1);
		else
			side = side->next;
	}
	(alst)->v = -1;
	return (0);
}

int			find_possibilities(t_list **paths, t_dome *rooms)
{
	t_dome *start;

	start = rooms;
	(void)paths;
	while (start != NULL)
	{
		if (start->type == STROOM)
			break ;
		start = start->next;
	}
	return (ft_pathfinder(start));
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
	if (!find_possibilities(&paths, rooms))
		return (ft_error("ERROR"));
// DEBUT	TESTS
	t_list  *lst;

	lst = rooms->adj;
	while (lst)
	{
		ft_putendl((((t_dome *)(lst->content))->name));
		ft_putnbr((((t_dome *)(lst->content))->v));
		lst = lst->next;
}
//	print_room_links("7", rooms);
	ft_putendl("\nParsing done:");
	print_rooms(rooms);
	print_file(file);
// FIN		TESTS
	return (0);
}
