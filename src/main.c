/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 10:05:35 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/03/13 14:49:16 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rms.h"

static char	*find_str_ants(char *line)
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
		}
		if (!(number = ft_strdup(line)))
			ft_exit_error("find_str_ants: ft_strdup: number");
		return (number);
	}
}

static t_list *room_node(char *line, char *ants)
{
	if (!ants)
		return (NULL);

}

int		main(void)
{
	t_list	*rooms;
	char	*line;
	char	*ants;

	while (get_next_line(0, &line) > 0)
	{
		ants = find_str_ants(line);
		
	}
}
