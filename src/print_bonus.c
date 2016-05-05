/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarin <rliou-ke@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 20:19:18 by akarin            #+#    #+#             */
/*   Updated: 2016/05/05 20:19:24 by akarin           ###   ########.fr       */
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
			ft_putstr("Amount of ants bypassing @So Gusto: ");
			ft_putnbr(head->pizza);
			ft_putchar('\n');
			if (head->pizza != nbants)
			{
				ft_putnbr(nbants - head->pizza);
				ft_putstr(" ants are still starving 😣");
			}
			return ;
		}
		head = head->next;
	}
}
