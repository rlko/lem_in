/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_antsnbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 13:19:29 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/05 17:39:21 by akarin           ###   ########.fr       */
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
	{
		ft_strdel(&str);
		return (a);
	}
	ft_strdel(&str);
	return (0);
}

static int		free_zero(char **str)
{
	free(*str);
	str = NULL;
	return (0);
}

int				find_antsnbr(t_list **file, int *t_opt)
{
	int			ret;
	char		*line;
	char		*str;

	while ((ret = get_next_line(0, &line)) > 0)
	{
		file = ft_lsttower(file, line);
		if (str_iscommand(line, 0, t_opt['p']))
			return (free_zero(&line));
		if (!str_iscomment(line) && !str_iscommand(line, 1, t_opt['p']))
		{
			str = line;
			while (*str)
			{
				if (!ft_isdigit(*str))
					return (free_zero(&line));
				++str;
			}
			return (get_antsnbr(line));
		}
		free(line);
	}
	return (0);
}
