/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_antsnbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 15:36:32 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/07 15:36:35 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rms.h"

static int		free_zero(char **str)
{
	free(*str);
	str = NULL;
	return (0);
}

static int		get_antsnbr(char *str)
{
	int			a;
	char		*check;
	char		*s;

	s = str;
	a = ft_atoi(str);
	if (!a)
		return (free_zero(&str));
	while (*str == '0')
		++str;
	if (!(check = ft_itoa(a)))
		return (0);
	if (ft_strequ(check, str) && a > 0)
	{
		free(check);
		free(s);
		return (a);
	}
	free(s);
	free(check);
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
