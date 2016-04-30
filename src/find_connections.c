/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_connections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/30 19:10:22 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/04/30 19:21:42 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rms.h"

static char	*get_last_line(t_list *file)
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

static void	free_the_intruder(t_list **file)
{
	t_list	*tmp;
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

void		find_connections(t_list **file, t_dome **room)
{
	char	*line;

	if (!(line = get_last_line(*file)))
		ft_exit_error("ERROR: wut");
	if (!get_room_links(line, room))
	{
		free_the_intruder(file);
		return ;
	}
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
}
