/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 10:05:35 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/04/27 18:57:47 by rliou-ke         ###   ########.fr       */
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

char		*ft_prevstr(t_list *lst)
{
	while (lst->next->next != NULL)
		lst = lst->next;
	return (lst->content);
}

int			is_unique(char *str)
{
	static int once_s = 0;
	static int once_e = 0;

	if (ft_strequ(str, "##start"))
		return (++once_s);
	else if (ft_strequ(str, "##end"))
		return (++once_e);
	return (0);
}

/*
t_dome		*build_rooms(t_dome **head)
{
	
}
*/

void		assign_coord(char *str, int *cd)
{
	if (ft_strequ(ft_itoa(ft_atoi(str)), str))
	{
		*cd = ft_atoi(str);
		ft_strdel(&str);
	}
	else
		ft_exit_error("ERROR: coords");
}

void		assign_room(t_list *lst, t_dome **room)
{
	t_list	*tmp;

	(*room)->name = lst->content;
	lst = lst->next;
	(*room)->x = ft_atoi(lst->content);
	(*room)->y = ft_atoi(lst->next->content);

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

void		assign_type(t_dome **room, char *prev)
{
	if (ft_strequ("##start", prev))
		(*room)->type = STROOM;
	else if (ft_strequ("##end", prev))
		(*room)->type = EDROOM;
	else
		(*room)->type = RGROOM;
}

int			data_are_unique(t_dome *head, t_list *lst)
{
	int		x;
	int		y;
	t_dome *tmp;

	x = ft_atoi(lst->next->content);
	y = ft_atoi(lst->next->next->content);
	tmp = head;
	while (tmp != NULL)
	{
		if (ft_strequ(lst->content, tmp->name))
			return (0);
		tmp = tmp->next;
	}
	tmp = head;
	while (tmp != NULL)
	{
		if (x == tmp->x && y == tmp->y)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int			split_parse(char *line, t_list **lst, t_dome *head)
{
	int 	nb_node;

	if (!(*lst = ft_lstsplit(line, ' ')))
		ft_exit_error("mk_rooms: lst: ft_lstsplit");
	nb_node = ft_lstlen(*lst);
	if (ft_strchr(line, '-'))
	{
		if (nb_node == 1)
			return (0);
	}
	else if (nb_node == 3)
	{
		if (data_are_unique(head, *lst))
			return (1);
	}
	ft_exit_error("ERROR");
	return (-42);
}

t_dome		*domebuilder(t_dome *head, t_dome *room)
{
	t_dome *tmp;

	if (head == NULL)
		head = room;
	else
	{
		tmp = head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = room;
	}
	return (head);
}

int			mk_rooms(t_dome **head, char **prev, char *line)
{
	t_dome	*room;
	t_list	*lst;

	if (!line[0])
		ft_exit_error("ERROR");
	if (!split_parse(line, &lst, *head))
		return (0);
	if (!(room = malloc(sizeof(*room))))
		ft_exit_error("mk_rooms: room: malloc");
	room->next = NULL;
	assign_type(&room, *prev);
	assign_room(lst, &room);
	if (*prev)
		*prev = NULL;
	*head = domebuilder(*head, room);
	return (1);
}

char		*check_command(t_list *file, char *prev, char *line)
{
	if (prev)
		ft_exit_error("ERROR");
	prev = ft_prevstr(file);
	if (str_iscommand(line, 0) && str_iscommand(prev, 0))
		ft_exit_error("ERROR");
	return (prev);
}

t_dome		*find_rooms(t_list **file)
{
	char 	*line;
	int		ret[3];
	t_dome	*rooms;
	char	*prev;

	ret[1] = 0;
	rooms = NULL;
	prev = NULL;
	while ((ret[0] = get_next_line(0, &line)) > 0)
	{	
		file = ft_lsttower(file, line);
		if (ret[1])
			prev = check_command(*file, prev, line);
		if (!str_iscomment(line) && !str_iscommand(line, 1))
		{
			if (!(ret[2] = mk_rooms(&rooms, &prev, line)))
				break ;
		}
		if ((ret[1] = is_unique(line)) > 1)
			ft_exit_error("ERROR");
	}
	return (rooms);
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
	
	ft_putchar('\n');
	ft_putendl("Parsing done:");

	int i = 0;
	while (room)
	{
		ft_putstr("Salle: ");
		ft_putnbr(i++);
		ft_putchar('\n');
		ft_putstr("Nom: ");
		ft_putendl(room->name);
		ft_putstr("x: ");
		ft_putnbr(room->x);
		ft_putchar('\n');
		ft_putstr("y: ");
		ft_putnbr(room->y);
		ft_putchar('\n');
		room = room->next;
	}
	ft_putchar('\n');
	ft_putendl("Fichier:");
	while (file)
	{
		ft_putendl(file->content);
		file = file->next;
	}
	return (0);
}
