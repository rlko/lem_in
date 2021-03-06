/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 13:17:02 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/07 15:51:07 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int		str_iscomment(char *str)
{
	return (str[0] == '#' && str[1] != '#');
}

int		str_iscommand(char *str, int strict, int opt)
{
	if (!str)
		ft_exit_error("str_iscommand: str is null");
	if (strict)
		return (ft_strncmp(str, "##", 2) == 0);
	else
	{
		if (!opt)
			return (ft_strequ(str, "##start") || ft_strequ(str, "##end"));
		return (ft_strequ(str, "##start") || ft_strequ(str, "##end") \
				|| ft_strequ(str, "##🍕"));
	}
}

int		ft_verror(char *verbose, int *t_opt)
{
	if (!t_opt['v'])
	{
		if (t_opt['c'])
			return (ft_error("\x1b[31mERROR\x1b[0m"));
		return (ft_error("ERROR"));
	}
	if (t_opt['c'])
		ft_putstr_fd("\x1b[31mERROR\x1b[0m: ", 2);
	else
		ft_putstr_fd("ERROR: ", 2);
	ft_putstr_fd(verbose, 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

void	ft_exit_verror(char *verbose, int *t_opt)
{
	if (!t_opt['v'])
	{
		if (t_opt['c'])
			ft_exit_error("\x1b[31mERROR\x1b[0m");
		ft_exit_error("ERROR");
	}
	if (t_opt['c'])
		ft_putstr_fd("\x1b[31mERROR\x1b[0m: ", 2);
	else
		ft_putstr_fd("ERROR: ", 2);
	ft_putstr_fd(verbose, 2);
	ft_putchar_fd('\n', 2);
	exit(EXIT_FAILURE);
}
