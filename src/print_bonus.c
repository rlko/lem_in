/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarin <rliou-ke@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 20:19:18 by akarin            #+#    #+#             */
/*   Updated: 2016/05/05 21:16:23 by akarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rms.h"

void		print_pizza(t_dome *head, int nbants, int opt)
{
	if (!opt)
		return ;
	while (head)
	{
		if (head->pizza >= 0)
		{
			ft_putstr("\nAmount of ants bypassed by So Gusto: ");
			ft_putnbr(head->pizza);
			ft_putstr(" ants");
			ft_putchar('\n');
			if (head->pizza != nbants)
			{
				ft_putnbr(nbants - head->pizza);
				ft_putstr("/");
				ft_putnbr(nbants);
				ft_putstr(" ants are still starving. 😣");
				ft_putstr(" which is about ");
				ft_putnbr(((nbants - head->pizza) * 100) / nbants);
				ft_putstr("% of total ants.");
			}
			return ;
		}
		head = head->next;
	}
}
