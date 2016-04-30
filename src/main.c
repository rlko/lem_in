/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 10:05:35 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/04/30 18:56:19 by rliou-ke         ###   ########.fr       */
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

int			link_already_exists(t_list *adj, char *str)
{
	while (adj != NULL)
	{
		if (ft_strequ(((t_dome *)adj->content)->name, str))
			return (1);
		adj = adj->next;
	}
	return (0);
}

void		add_to(char *adj_room, t_dome **node, t_dome *lst)
{
	t_list	*connection;

	while (lst != NULL)
	{
		if (ft_strequ(adj_room, lst->name))
		{
			if (!link_already_exists((*node)->adj, adj_room))
			{
				connection = ft_lstnew(lst, sizeof(t_dome));
				ft_lstappend(&(*node)->adj, connection);
			}
			return ;
		}
		lst = lst->next;
	}
	ft_exit_error("Unexpected Fuck: add_to");
}

void		fill_connections(t_list *lst, t_dome **head)
{
	t_dome	*tmp;

	tmp = *head;
	while (tmp != NULL)
	{
		if (ft_strequ(lst->content, tmp->name))
		{
			add_to(lst->next->content, &tmp, *head);
			break ;
		}
		tmp = tmp->next;
	}
	tmp = *head;
	while (tmp != NULL)
	{
		if (ft_strequ(lst->next->content, tmp->name))
		{
			add_to(lst->content, &tmp, *head);
			break ;
		}
		tmp = tmp->next;
	}
}


int		get_room_links(char *line, t_dome **room)
{
	t_list	*lsplit;

	lsplit = ft_lstsplit(line, '-');
	if (ft_lstlen(lsplit) != 2)
		return (0);
	if (!link_isvalid(lsplit, *room))
		return (0);
	fill_connections(lsplit, room);
	return (1);
}

void	free_the_intruder(t_list **file)
{
	t_list *tmp;
	t_list	*prev;

	tmp = *file;
	while (tmp->next != NULL)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	prev->next = NULL;
	free(tmp->content);
	free(tmp);
}

#include <stdio.h>
void		find_connections(t_list **file, t_dome **room)
{
	ft_putendl("DEBUT: find_connections");
	char	*line;

	if (!(line = get_last_line(*file)))
		ft_exit_error("ERROR: wut");
	if (!get_room_links(line, room))
	{
		free_the_intruder(file);
		return ;
	}
//	ft_putendl(((t_dome *)(tmp->adj->content))->name);
	while (get_next_line(0, &line) > 0)
	{
		if (str_iscommand(line, 0))
			return ;
		if (!str_iscomment(line))
		{
			if (!get_room_links(line, room))
				return ;
		}
		file = ft_lsttower(file, line);
	}
	ft_putendl("FIN: find_connections");
}

int			main(void)
{
	ft_putendl("DEBUT: main");
	t_list	*file;
	int		anb;
	t_dome	*room;

	file = NULL;
	room = NULL;
	if (!(anb = find_antsnbr(&file)))
		return (ft_error("ERROR"));
	room = find_rooms(&file);
	find_connections(&file, &room);
	print_room_links("7", room);
	

	ft_putendl("\nParsing done:");
	print_rooms(room);
	print_file(file);

	ft_putendl("FIN: main");
	return (0);
}
