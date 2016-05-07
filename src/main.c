/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 10:05:35 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/07 15:41:47 by rliou-ke         ###   ########.fr       */
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

t_dome		*get_room(t_dome *lst, enum e_type type)
{
	while (lst != NULL)
	{
		if (lst->type == type)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void		the_world_ends_without_you(t_list *ants, t_dome *rooms)
{
	t_list	*tmp;
	t_dome	*del;

	while (ants)
	{
		tmp = ants;
		ants = ants->next;
		free(tmp);
	}
	while (rooms)
	{
		del = rooms;
		rooms = rooms->next;
		while (del->adj)
		{
			tmp = del->adj;
			del->adj = del->adj->next;
			free(tmp);
		}
		ft_strdel(&del->name);
		ft_strdel(&del->x);
		ft_strdel(&del->y);
		free(del);
	}
}

int			main(int ac, char **av)
{
	t_lm	box;
	t_list	*file;

	(void)ac;
	av = read_opts(box.opt, av);
	if (box.opt['b'] && !box.opt['p'])
		return (ft_error("Error: option -b cannot work wihout option -p"));
	if (av[0])
		return (ft_error("Usage: ./lem-in [-bcprtv] < [file]"));
	file = NULL;
	if (!(box.nb_ants = find_antsnbr(&file, box.opt)))
		return (ft_verror("Invalid ants number", box.opt));
	box.rooms = find_rooms(&file, box.opt);
	find_connections(&file, &box.rooms, box.opt);
	if (!ft_is_solvable(box.rooms, box.opt))
		return (ft_verror("Invalid map", box.opt));
	print_file_and_bye(&file, box.opt);
	box.ants = instantiate_ants(box.nb_ants, box.rooms);	
	shit_just_got_serious(box);
	the_world_ends_without_you(box.ants, box.rooms);
	return (0);
}
