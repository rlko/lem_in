/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 13:55:21 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/04 16:55:42 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rms.h"

static char		*ft_prevstr(t_list *lst)
{
	while (lst->next->next != NULL)
		lst = lst->next;
	return (lst->content);
}

static int		is_unique(char *str)
{
	static int once_s = 0;
	static int once_e = 0;

	if (ft_strequ(str, "##start"))
		return (++once_s);
	else if (ft_strequ(str, "##end"))
		return (++once_e);
	return (0);
}

static char		*check_command(t_list *file, char *prev, char *line)
{
	if (prev)
		ft_exit_error("ERROR");
	prev = ft_prevstr(file);
	if (str_iscommand(line, 0) && str_iscommand(prev, 0))
		ft_exit_error("ERROR");
	return (prev);
}

t_dome			*find_rooms(t_list **file)
{
	char		*line;
	int			ret[3];
	t_dome		*rooms;
	char		*prev;

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
					return (rooms);
		}
		if ((ret[1] = is_unique(line)) > 1)
			ft_exit_error("ERROR");
		free(line);
	}
	ft_exit_error("ERROR");
	return (NULL);
}
