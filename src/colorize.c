/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 15:35:05 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/07 17:44:20 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rms.h"

static char	*ft_strcolordup(char *color, char *str)
{
	char	*tmp;
	char	*new;

	if (!(tmp = ft_strjoin(color, str)))
		ft_exit_error("ft_strcolordup: ft_strjoin");
	if (!(new = ft_strjoin(tmp, "\x1b[0m")))
		ft_exit_error("ft_strcolordup: ft_strjoin");
	ft_strdel(&tmp);
	return (new);
}

static char	*room_color(char *str, enum e_type type)
{
	char	*new;

	if (type == STROOM)
		new = ft_strcolordup(C_RED, str);
	else if (type == EDROOM)
		new = ft_strcolordup(C_RED, str);
	else if (type == PIZZA)
		new = ft_strcolordup(C_YELLOW, str);
	else
		new = ft_strcolordup(C_BLUE, str);
	return (new);
}

void		colorize(t_dome *rooms)
{
	char	*del;

	while (rooms)
	{
		del = rooms->name;
		rooms->name = room_color(rooms->name, rooms->type);
		free(del);
		rooms = rooms->next;
	}
}
