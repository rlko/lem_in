/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 10:05:35 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/04/28 17:14:09 by rliou-ke         ###   ########.fr       */
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

static char		*get_last_line(t_list *file)
{
	if (file)
	{
		while (file->next != NULL)
			file = file->next;
		if (file->content)
			return (file->content);
	}
	return (NULL);
}

int			name_exists(char *name, t_dome *room)
{
	while (room != NULL)
	{
		if (ft_strequ(name, room->name))
			return (1);
		room = room->next;
	}
	return (0);
}

int			link_isvalid(t_list *lst, t_dome *room)
{
	while (lst != NULL)
	{
		if (!name_exists(lst->content, room))
			return (0);
		lst = lst->next;
	}
	return (1);
}

void		add_to(char *adj_room, t_dome **node, t_dome **head)
{
	t_dome *tmp;

	tmp = *head;
	while (tmp)
	{
		if (ft_strequ(adj_room, tmp->name))
			//
		tmp = tmp->next;
	}
}

void		fill_connections(t_list *lst, t_dome **head)
{
	t_dome *tmp;

	tmp = *head;
	while (tmp != NULL)
	{
		if (ft_strequ(lst->content, tmp->name))
			add_to(lst->next->content, &tmp, head);
		tmp = tmp->next;
	}
}

void		find_connections(t_list **file, t_dome **room)
{
	char	*line;
	t_list	*lsplit;

	line = get_last_line(*file);
	lsplit = ft_lstsplit(line, '-');
	if (ft_lstlen(lsplit) != 2)
		ft_exit_error("ERROR: Link format");
	if (!link_isvalid(lsplit, *room))
		return ;
	fill_connections(lsplit, room);
	while (get_next_line(0, &line) > 0)
	{
	//...	
	}
}

int			main(void)
{
	t_list	*file;
	int		anb;
	t_dome	*room;

	file = NULL;
	room = NULL;
	if (!(anb = find_antsnbr(&file)))
		return (ft_error("ERROR"));
	room = find_rooms(&file);
	find_connections(&file, &room);
	

	ft_putendl("\nParsing done:");
	print_rooms(room);
	print_file(file);

	return (0);
}
