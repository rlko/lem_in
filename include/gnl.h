/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/05 21:01:43 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/03/04 07:10:25 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H
# include "libft.h"
# define BUFF_SIZE 30

int get_next_line(int const fd, char **line);
#endif