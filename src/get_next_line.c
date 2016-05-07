/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/03 17:09:08 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/07 15:39:57 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "gnl.h"

static int		rnl(int const fd, char **line, char **stock)
{
	int			ret;
	char		buf[BUFF_SIZE + 1];

	while ((ret = read(fd, buf, BUFF_SIZE)) && *stock)
	{
		if (ret == -1)
			return (0);
		buf[ret] = '\0';
		if (ft_strchr(buf, '\n'))
		{
			*line = ft_strjoin(*line, \
					ft_strsub(buf, 0, ft_strchr(buf, '\n') - buf));
			*stock = ft_strdup(ft_strchr(buf, '\n') + 1);
			return (1);
		}
		*line = ft_strjoin(*line, ft_strdup(buf));
	}
	return (0);
}

int				get_next_line(int const fd, char **line)
{
	static char	*stock = 0;

	stock = (stock == 0 ? ft_strnew(BUFF_SIZE + 1) : stock);
	if ((fd < 0 || line == NULL || BUFF_SIZE <= 0))
		return (-1);
	*line = 0;
	if (stock && ft_strchr(stock, '\n'))
	{
		*line = ft_strsub(stock, 0, ft_strchr(stock, '\n') - stock);
		stock = ft_strchr(stock, '\n') + 1;
		return (1);
	}
	else if (stock)
		*line = stock;
	return (rnl(fd, line, &stock));
}
