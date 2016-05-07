/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus_pizza.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 15:34:48 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/07 17:06:42 by rliou-ke         ###   ########.fr       */
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
			ft_putchar('/');
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
