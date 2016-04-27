/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 13:17:02 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/04/27 14:34:00 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		str_iscomment(char *str)
{
	return (str[0] == '#' && str[1] != '#');
}

int		str_iscommand(char *str, int strict)
{
	if (!str)
		ft_exit_error("str_iscommand: str is null");
	if (strict)
		return (ft_strncmp(str, "##", 2) == 0);
	else
		return (ft_strequ(str, "##start") || ft_strequ(str, "##end"));
}
