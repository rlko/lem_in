/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rms.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 09:22:59 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/03/17 16:02:53 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

enum		e_type
{
	RGROOM,
	STROOM,
	EDROOM
};

typedef struct		s_dome
{
	char			*name;
	enum e_type		type;
	struct s_room	*next;
	int				x;
	int				y;
}					t_dome;
