/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rms.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 09:22:59 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/01 14:16:06 by akarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RMS_H
# define RMS_H
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include "gnl.h"

# define INTMAX		2147483647

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
	struct s_dome	*next;
	char			*x;
	char			*y;
	t_list			*adj;
	int				v;
}					t_dome;

t_list				**ft_lsttower(t_list **head, char *str);
int					find_antsnbr(t_list **file);
int					str_iscomment(char *str);
int					str_iscommand(char *str, int strict);

void				assign_room(t_list *lst, t_dome **room);
void				assign_type(t_dome **room, char *prev);
int					mk_rooms(t_dome **head, char **prev, char *line);
t_dome				*find_rooms(t_list **file);

void				fill_connections(t_list *lst, t_dome **head);
int					get_room_links(char *line, t_dome **room);
void				find_connections(t_list **file, t_dome **room);

/*
** Tests functions:
*/

void				print_rooms(t_dome *room);
void				print_file(t_list *file);
void				print_room_links(char *name, t_dome *room);
#endif
