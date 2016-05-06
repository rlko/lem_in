/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   once_upon_a_time.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarin <rliou-ke@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 23:46:01 by akarin            #+#    #+#             */
/*   Updated: 2016/05/06 00:55:28 by akarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rms.h"
#include <stdio.h>

void		ft_print_introduction(void)
{
	char	*line;
	ft_putendl("Once upon a time...");
//	sleep(3);
	ft_putstr("There was a group of ants which studying");
	ft_putstr(" some strange hex magic at some weird school called 42.");
//	sleep(5);
	ft_putstr("\nWell, they were actually pretending to study.");
//	sleep(3);
	ft_putstr("Because who the hell actually knows what is hex magic\n");
//	sleep(3);
	ft_putendl("Anyway it's getting late, I think it's to head home");
//	sleep(3);
	ft_putendl("Press Enter to continue");
	freopen("/dev/tty", "rw", stdin);
	while( getchar() != '\n' );
	sleep(1);
	ft_putendl("In this mode, the number of ants you set earlier will be ignored");
	slee(1);
	ft_putendl("and therefore, I shall remember your name instead");
	ft_putchar('\n');
	ft_putendl("What's your name?");
	while (get_next_line(0,	&line) > 0)
	{
		if (line[0])
		{
			ft_putstr("Is it ");
			ft_putstr(line);
			ft_putstr("? ");
		}

		free(line);	
	}
// puts("Reading from stdin again...");
 //  while(fgets(buf, sizeof(buf), stdin))
//	       fputs(buf, stdout);
}

int		once_upon_a_time(t_lm box)
{
	(void)box;
	ft_print_introduction();
	return (1);
}
