/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_antsnbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 13:19:29 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/04/26 13:37:59 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rms.h"

static int		get_antsnbr(char *str)
{
	int			a;
	char		*check;

	a = ft_atoi(str);
	while (*str == '0')
		++str;
	if (!(check = ft_itoa(a)))
		return (0);
	if (ft_strequ(check, str) && a > 0)
		return (a);
	return (0);
}

static int		free_zero(char **str)
{
	free(*str);
	str = NULL;
	return (0);
}

int				find_antsnbr(t_list **file)
{
	int			ret;
	char		*line;
	char		*str;

	while ((ret = get_next_line(0, &line)) > 0)
	{
		file = ft_lsttower(file, line);
		if (str_iscommand(line, 1))
			return (free_zero(&line));
		if (!str_iscomment(line))
		{
			str = line;
			while (*str)
			{
				if (!ft_isdigit(*str))
					return (free_zero(&line));
				++str;
			}
			free(line);
			return (get_antsnbr(line));
		}
		free(line);
	}
	return (0);
}