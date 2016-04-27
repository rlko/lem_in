/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rms.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 09:22:59 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/04/26 13:21:57 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "gnl.h"

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

t_list				**ft_lsttower(t_list **head, char *str);
int					find_antsnbr(t_list **file);
int					str_iscomment(char *str);
int					str_iscommand(char *str, int strict);