/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 10:05:35 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/04/27 16:20:20 by rliou-ke         ###   ########.fr       */
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
	int		i;
	t_list	*tmp;

	if ((i = ft_lstlen(lst)) != 3)
		ft_exit_error("ERROR");
	i = 0;
	while (lst != NULL)
	{
		tmp = lst;
		if (i == 0)
			(*room)->name = lst->content;
		else
		{
			if (i == 1)
				assign_coord(lst->content, &(*room)->x);
			else if (i == 2)
				assign_coord(lst->content, &(*room)->y);
			else
				ft_exit_error("assign_room: wut");
		}
		lst = lst->next;
		free(tmp);
		++i;
	}
}

void		assign_type(t_dome **room, char *prev)
{
	if (strequ("##start", prev))
	{
		room->type = STROOM;
	}
	else if (strequ("##end", prev))
	{
		room->type = EDROOM;
	}
	else
	{
		room->type = RGROOM;
	}
}

t_dome		*mk_rooms(t_dome *head, char **prev, char *line)
{
	t_dome	*tmp;
	t_dome	*room;
	t_list	*lst;

	if (!line[0])
		ft_exit_error("ERROR");
	if (!(room = malloc(sizeof(*room))))
		ft_exit_error("mk_rooms: room: malloc");
	if (!(lst = ft_lstsplit(line, " ")))
		ft_exit_error("mk_rooms: lst: ft_lstsplit");
	assign_room(lst, &room);
	assign_type(&room, *prev);
	room->next = NULL;
	if (*prev)
		*prev = NULL;
	if (head == NULL)
		return (room);
	tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = room;
	return (head);
}

char		*check_command(char *prev, char *line)
{
	if (prev)
		ft_exit_error("ERROR");
	prev = ft_prevstr(*file);
	if (str_iscommand(line, 0) && str_iscommand(prev, 0))
		ft_exit_error("ERROR");
	return (prev);
}

t_dome		*find_rooms(t_list **file)
{
	char 	*line;
	int		ret[2];
	t_dome	*rooms;
	char	*prev;

	ret[1] = 0;
	rooms = NULL;
	prev = NULL;
	while ((ret[0] = get_next_line(0, &line)) > 0)
	{	
		file = ft_lsttower(file, line);
		if (ret[1])
			prev = check_command(prev, line);
		if (!str_iscomment(line) && !str_iscommand(line, 1))
			rooms = mk_rooms(rooms, &prev, line);
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
	return (0);
}
