/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 21:03:30 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/04 21:11:07 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rms.h"

void		print_turn(t_list *ants)
{
	t_ant	*ant;

	while (ants)
	{
		ant = ants->content;
		if (ant->played)
		{
			ft_putchar('L');
			ft_putnbr(ant->id);
			ft_putchar('-');
			ft_putstr(ant->room->name);
			if (ants->next)
				ft_putchar(' ');
		}
		ants = ants->next;
	}
	ft_putchar('\n');
}

void	print_file_and_bye(t_list **file)
{
	t_list	*del;

	while (*file)
	{
		ft_putendl((*file)->content);
		del = *file;
		*file = (*file)->next;
		free(del->content);
		free(del);
	}
	file = NULL;
	ft_putchar('\n');
}

void	print_count_turn(int count, int opt)
{
	if (opt)
	{
		ft_putstr("\nGame done in \x1b[32m");
		ft_putnbr(count);
		ft_putendl("\x1b[0m turns...");
	}
}
