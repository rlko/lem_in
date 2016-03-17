/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 10:05:35 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/03/17 18:16:52 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rms.h"

static char		*find_str_ants(char *line)
{
	static char	*number = NULL;
	char		*str;

	if (number)
		return (number);
	if (line[0] == '#' || !line[0])
		return (NULL);
	else
	{
		str = line;
		while (*str)
		{
			if (!isdigit(*str))
				return (NULL);
			str++;
		}
		if (!(number = ft_strdup(line)))
			ft_exit_error("find_str_ants: ft_strdup: number");
		return (number);
	}
}

void		ft_dome_add(t_dome **begin, t_dome *new)
{
	t_dome	*current;
	t_dome	*prev;

	prev = NULL;
	current = *begin;
	while (current != NULL)
	{
		prev = current;
		current = current->next;
	}
	new->next = NULL;
	if (prev == NULL)
		*begin = new;
	else
		prev->next = new;
}

static int		is_reg_room(int *room, char *line)
{
	if (ft_strequ("##start", line))
	{
		*room = 1;
		return (0);
	}
	else if (ft_strequ("##end", line))
	{
		*room = 2;
		return (0);
	}
	return (1);
}

static void		get_cd(char *str, int *x, int *y)
{
	int			n;
	int			i;

	if ((n = ft_getnbr(str)) != 2)
		ft_exit_error("ERROR: Input error: coordinate");
	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			if (n == 2)
				*x = ft_atoi(&str[i]);
			else (n == 1)
				*y = ft_atoi(&str[i]);
			n--;
			while (ft_isdigit(str[i]))
				i++;
		}
		else
			i++;
	}
}

static void		fill_data(char *line, t_dome **node)
{
	char		*str;

	str = *line;
	if (*str && (*str == '#' || *str == 'L'))
		ft_exit_error("ERROR");
	while (!ft_isblank(*str) && *str)
		++str;
	if (!((*node)->name = ft_strsub(line, 0, str - line)))
		ft_exit_error("get_cd: ft_strsub: str");
	get_cd(str + 1, (*node)->x, ((*node)->y));
}

static t_dome	*room_node(char *line, char *ants)
{
	static short	room = 0;
	t_dome			*new;
	char			*name;

	if (!ants || !line || !line[0] || !is_reg_room(&room, line))
		return (NULL);
	if (!(new = malloc(sizeof(*new))))
		ft_exit_error("room_node: malloc: new");
	if (room == 0)
		new->type = RGROOM;
	else if (room == 1)
		new->type = STROOM;
	else if (room == 2)
		new->type = EDROOM;
	room = 0;
	fill_data(line, &new);
	new->next = NULL;
	return (new);
}

int					main(void)
{
	t_dome			*rooms;
	t_dome			*node;
	char			*line;
	char			*ants;
	unsigned short	ret;

	rooms = NULL;
	while ((ret = get_next_line(0, &line)) > 0)
	{
		ants = find_str_ants(line);
		if ((node = room_node(line, ants)))
			ft_dome_add(&rooms, node);
				
	}
	if (ret == -1)
		return (ft_error("gnl error"));
	return (0);
}
