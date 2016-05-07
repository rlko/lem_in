/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarin <rliou-ke@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 20:19:18 by akarin            #+#    #+#             */
/*   Updated: 2016/05/07 03:18:20 by akarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rms.h"

static void	print_pizza_suite(int pizza, int nbants)
{
	if (pizza != nbants)
	{
		ft_putchar('\n');
		ft_putnbr(nbants - pizza);
		ft_putstr(" ants are still starving. 😣");
		ft_putstr(" which is about ");
		ft_putnbr(((nbants - pizza) * 100) / nbants);
		ft_putstr("% of total ants.");
	}
	else
		ft_putstr(" 😋");
	ft_putchar('\n');
}

void		print_pizza(t_dome *head, int nbants, int *opt)
{
	if (!opt['p'])
		return ;
	while (head)
	{
		if (head->pizza >= 0)
		{
			if (!opt['c'])
				ft_putstr("\nAmount of ants bypassed by So Gusto: ");
			else
			{
				ft_putstr("\nAmount of ants bypassed by ");
				ft_putstr("\x1b[32;21mSo \x1b[37;21mGus\x1b[31;21mto\x1b[0m: ");
			}
			ft_putnbr(head->pizza);
			ft_putstr("/");
			ft_putnbr(nbants);
			ft_putstr(" ants.");
			print_pizza_suite(head->pizza, nbants);
			return ;
		}
		head = head->next;
	}
}

void		ft_print_pizzatime(t_ant *ant, int *opt)
{
	ft_putchar('L');
	ft_putnbr(ant->id);
	if (opt['c'])
		ft_putendl(" found a slice of \x1b[33mpizza\x1b[0m!");
	else
		ft_putendl(" found a slice of pizza!");

}

static void	print_rooms_route(t_list *route)
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

void		print_route(t_list **route, t_dome *rooms)
{
	t_list	*node;
	t_list	*lst;
	t_dome	*adj;

	if (!(node = malloc(sizeof(*node))))
		ft_exit_error("print_route: malloc: node");
	node->content = rooms->name;
	ft_lstappend(route, node);
	if (rooms->type == EDROOM)
		print_rooms_route(*route);
	else
	{
		lst = rooms->adj;
		while (lst)
		{
			adj = lst->content;
			if (adj->depth == rooms->depth - 1)
				print_route(route, adj);
			lst = lst->next;
		}
	}
	free(node);
}
