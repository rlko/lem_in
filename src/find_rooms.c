/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 15:38:03 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/07 15:47:53 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rms.h"

static char		*ft_prevstr(t_list *lst)
{
	while (lst->next->next != NULL)
		lst = lst->next;
	return (lst->content);
}

static int		is_unique(char *str, int opt)
{
	static int once_s = 0;
	static int once_e = 0;
	static int once_pizza = 0;

	if (ft_strequ(str, "##start"))
		return (++once_s);
	else if (ft_strequ(str, "##end"))
		return (++once_e);
	else if (ft_strequ(str, "##🍕") && opt)
		return (++once_pizza);
	return (0);
}

static char		*check_command(t_list *file, char *prev, char *line, int *t_opt)
{
	if (prev)
		ft_exit_verror("Known commands in a row do not belong here", t_opt);
	prev = ft_prevstr(file);
	if (str_iscommand(line, 0, t_opt['p']) \
			&& str_iscommand(prev, 0, t_opt['p']))
		ft_exit_verror("Known commands in a row do not belong here", t_opt);
	return (prev);
}

t_dome			*find_rooms(t_list **file, int *t_opt)
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
			prev = check_command(*file, prev, line, t_opt);
		if (!str_iscomment(line) && !str_iscommand(line, 1, t_opt['p']))
		{
			if (!(ret[2] = mk_rooms(&rooms, &prev, line, t_opt)))
				return (rooms);
		}
		if ((ret[1] = is_unique(line, t_opt['p'])) > 1)
			ft_exit_verror("More than 1 known command each used", t_opt);
		free(line);
	}
	ft_exit_verror("File incomplete", t_opt);
	return (NULL);
}
