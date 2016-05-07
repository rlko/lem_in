/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_connections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 15:37:41 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/07 15:37:43 by rliou-ke         ###   ########.fr       */
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

static int	check_command(t_list *file)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	while (file)
	{
		if (ft_strequ(file->content, "##start"))
			start = 1;
		else if (ft_strequ(file->content, "##end"))
			end = 1;
		file = file->next;
	}
	return (start && end);
}

void		find_connections(t_list **file, t_dome **room, int *t_opt)
{
	char	*line;

	if (!check_command(*file))
		ft_exit_verror("##start or/and ##end missing", t_opt);
	if (!(line = get_last_line(*file)))
		ft_exit_error("ERROR: whut the fuck happened");
	if (!get_room_links(line, room))
	{
		free_the_intruder(file);
		return ;
	}
	while (get_next_line(0, &line) > 0)
	{
		if (str_iscommand(line, 0, t_opt['p']))
			return ;
		if (!(line[0] == '#'))
		{
			if (!get_room_links(line, room))
				return ;
		}
		file = ft_lsttower(file, line);
	}
}
