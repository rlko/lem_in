/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 10:05:35 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/04/26 16:48:18 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rms.h"

t_list		**ft_lsttower(t_list **head, char *str)
{
	t_list	*new;
	size_t	len;

	if (!(new = malloc(sizeof(*new))))
		ft_exit_error("ft_lsttower: new: malloc");
	len = ft_strlen(str);
	if (!(new->content = malloc(sizeof(char *) * (len + 1))))
		ft_exit_error("ft_lsttower: new->content: malloc");
	ft_strcpy(new->content, str);
	new->content_size = len;
	ft_lstappend(head, new);
	return (head);
}

char		*ft_prevstr(t_list *lst)
{
	while (lst->next->next != NULL)
		lst = lst->next;
	return (lst->content);
}

int			is_unique(char *str)
{
	static int once_s = 0;
	static int once_e = 0;

	if (ft_strequ(str, "##start"))
		return (++once_s);
	else if (ft_strequ(str, "##end"))
		return (++once_e);
	return (0);
}

/*
t_dome		*build_rooms(t_dome **head)
{
	
}
*/

t_dome		*find_rooms(t_list **file)
{
	char 	*line;
	int 	ret;
	int		ncmd;
	t_dome	*rooms;
	char	*prev;

	ncmd = 0;
	rooms = NULL;
	prev = NULL;
	while ((ret = get_next_line(0, &line)) > 0)
	{	
		file = ft_lsttower(file, line);
		if (ncmd)
		{
			if (prev)
				ft_exit_error("ERROR");
			prev = ft_prevstr(*file);
			ft_putstr("le previous: ");
			ft_putendl(prev);
		}
		if (!str_iscomment(line) && !str_iscommand(line, 1))
		{
			if (prev)
			{
				ft_putendl("cool");
				prev = NULL;
			}
			else
			{
				ft_putendl("ok");
			}
		}
		if ((ncmd = is_unique(line)) > 1)
			ft_exit_error("ERROR");

	}
	return (rooms);
}	

int			main(void)
{
	t_list	*file;
	int		anb;
	t_dome	*room;


	file = NULL;
	room = NULL;
	if (!(anb = find_antsnbr(&file)))
		return (ft_error("ERROR"));
	room = find_rooms(&file);
	return (0);
}
