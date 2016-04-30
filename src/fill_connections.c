/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_connections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/30 19:03:57 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/04/30 19:04:07 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rms.h"

static int	link_already_exists(t_list *adj, char *str)
{
	while (adj != NULL)
	{
		if (ft_strequ(((t_dome *)adj->content)->name, str))
			return (1);
		adj = adj->next;
	}
	return (0);
}

static void	add_to(char *adj_room, t_dome **node, t_dome *lst)
{
	t_list	*connection;

	while (lst != NULL)
	{
		if (ft_strequ(adj_room, lst->name))
		{
			if (!link_already_exists((*node)->adj, adj_room))
			{
				connection = ft_lstnew(lst, sizeof(t_dome));
				ft_lstappend(&(*node)->adj, connection);
			}
			return ;
		}
		lst = lst->next;
	}
	ft_exit_error("Unexpected Fuck: add_to");
}

void	fill_connections(t_list *lst, t_dome **head)
{
	t_dome	*tmp;

	tmp = *head;
	while (tmp != NULL)
	{
		if (ft_strequ(lst->content, tmp->name))
		{
			add_to(lst->next->content, &tmp, *head);
			break ;
		}
		tmp = tmp->next;
	}
	tmp = *head;
	while (tmp != NULL)
	{
		if (ft_strequ(lst->next->content, tmp->name))
		{
			add_to(lst->content, &tmp, *head);
			break ;
		}
		tmp = tmp->next;
	}
}
