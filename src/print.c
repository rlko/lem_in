/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 21:03:30 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/07 03:22:41 by akarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rms.h"

static void	ft_putcolor(char *color, char *s)
{
	ft_putstr(color);
	ft_putstr(s);
	ft_putendl(C_RESET);
}

void		ft_printline(char *str, int *t_opt)
{
	if (!t_opt['c'])
	{
		ft_putendl(str);
		return ;
	}
	if (str_iscommand(str, 0, t_opt['p']))
		ft_putcolor(C_RED, str);
	else if (str_iscommand(str, 1, t_opt['p']))
		ft_putcolor("\x1b[32m\x1b[1m", str);
	else if (str_iscomment(str))
		ft_putcolor(C_CYAN, str);
	else
	{
		ft_putendl(str);
	}
}

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

void	print_file_and_bye(t_list **file, int *t_opt)
{
	t_list	*del;

	while (*file)
	{
		ft_printline((*file)->content, t_opt);
		del = *file;
		*file = (*file)->next;
		free(del->content);
		free(del);
	}
	file = NULL;
	ft_putchar('\n');
}

void	print_count_turn(int count, int *opt)
{
	if (opt['t'])
	{
		if (opt['c'])
		{
			ft_putstr("\nGame done in \x1b[32m");
			ft_putnbr(count);
			ft_putendl("\x1b[0m turns...");
		}
		else
		{
			ft_putstr("\nGame done in ");
			ft_putnbr(count);
			ft_putendl("\x1b[0m turns...");
		}
	}
}
