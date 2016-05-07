/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus_route.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 16:56:43 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/07 17:02:25 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rms.h"

static void		print_rooms_route(t_list *route)
{
	while (route)
	{
		ft_putchar('[');
		ft_putstr(route->content);
		ft_putchar(']');
		if (route->next)
			ft_putstr("->");
		else
			ft_putchar('\n');
		route = route->next;
	}
}

static t_list	*node_before_last(t_list **r)
{
	t_list		*route;

	route = *r;
	if (route)
	{
		while (route->next)
			route = route->next;
		return (route);
	}
	return (NULL);
}

void			recurse_route(t_list **route, t_list *lst, int curr_dep)
{
	t_dome		*adj;

	while (lst)
	{
		adj = lst->content;
		if (adj->depth == curr_dep)
		{
			if (route && *route && adj)
				print_route(route, adj);
		}
		lst = lst->next;
	}
}

void			print_route(t_list **route, t_dome *rooms)
{
	t_list		*node;
	t_list		*lst;
	t_list		*before;

	before = node_before_last(route);
	if (!(node = malloc(sizeof(*node))))
		ft_exit_error("print_route: malloc: node");
	node->content = rooms->name;
	ft_lstappend(route, node);
	if (rooms->type == EDROOM)
		print_rooms_route(*route);
	else
	{
		lst = rooms->adj;
		recurse_route(route, lst, rooms->depth - 1);
	}
	if (before)
		before->next = NULL;
	free(node);
}
