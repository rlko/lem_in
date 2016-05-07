/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_opts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarin <rliou-ke@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 15:02:00 by akarin            #+#    #+#             */
/*   Updated: 2016/05/07 02:59:00 by akarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rms.h"

static void		print_err_opt(char c)
{
	ft_putstr_fd("len-in: illegal option -- ", 2);
	ft_putchar(c);
	ft_putstr_fd("\nusage: ./lem-in [-bcprtv] < [file]\n", 2);
	exit(EXIT_FAILURE);
}

static char		illegal_opt(char *str)
{
	int i;

	i = 1;
	while (str[i] != '\0')
	{
		if (!(str[i] == 'v' || str[i] == 't' || str[i] == 'c' ||
				str[i] == 'p' || str[i] == 'b' || str[i] == 'r'))
			return (str[i]);
		i++;
	}
	return (0);
}

static int		legit_opt(char *str)
{
	int i;

	if (str[0] == '-')
	{
		i = 1;
		if (str[1] == '\0')
			return (0);
		while (str[i] != '\0')
		{
			if (!(str[i] == 'v' || str[i] == 't' || str[i] == 'c' ||\
						str[i] == 'p' || str[i] == 'b' || str[i] == 'r'))
				return (-1);
			i++;
		}
		return (1);
	}
	return (0);
}

static void		init_opts(int *tab_opt)
{
	int i;

	i = 0;
	while (i < 128)
	{
		tab_opt[i] = 0;
		i++;
	}
}

char			**read_opts(int *t_opt, char **av)
{
	int	char_c;
	int	i;
	int	j;

	init_opts(t_opt);
	i = 1;
	while (av[i] && legit_opt(av[i]) == 1)
	{
		j = 1;
		while (av[i][j])
		{
			char_c = av[i][j++];
			t_opt[char_c] = 1;
		}
		i++;
	}
	if (av[i] && legit_opt(av[i]) == -1)
	{
		if (ft_strcmp("--", av[i]))
			print_err_opt(illegal_opt(av[i]));
		return (&av[i + 1]);
	}
	return (&av[i]);
}
