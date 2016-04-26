/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 10:05:35 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/04/26 11:54:24 by rliou-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rms.h"

static t_list	**ft_lsttower(t_list **head, char *str)
{
	t_list	*new;
	size_t	len;

	if (!(new = malloc(sizeof(*new))))
		ft_exit_error("find_antsnbr: file: malloc");
	len = ft_strlen(str);
	if (!(new->content = malloc(sizeof(char *) * (len + 1))))
		ft_exit_error("find_antsnbr: file->data: malloc");
	new->content = ft_strcpy(new->content, str);
	new->content_size = len;
	new->next = NULL;
	ft_lstappend(head, new);
	return (head);
}

static int		get_antsnbr(char *str)
{
	int			a;
	char		*check;

	a = ft_atoi(str);
	ft_putnbr(a);
	if (!(check = ft_itoa(a)))
		return (0);
	if (ft_strequ(check, str) && a > 0)
		return (a);
	return (0);
}

int				str_iscomment(char *str)
{
	return (str[0] == '#' && str[1] != '#');
}

int				str_iscommand(char *str, int strict)
{
	if (strict)
		return (ft_strncmp(str, "##", 2) == 0);
	else
		return (ft_strequ(str, "##start") || ft_strequ(str, "##end"));
}

static int	free_zero(char **str)
{
	free(*str);
	str = NULL;
	return (0);
}

static int		find_antsnbr(t_list **file)
{
	int 	ret;
	char	*line;
	char	*str;

	while ((ret = get_next_line(0, &line)) > 0)
	{
		file = ft_lsttower(file, line);
		if (str_iscommand(line, 1))
			return (free_zero(&line));
		if (!str_iscomment(line))
		{
			str = line;
			while (*str)
			{
				if (!ft_isdigit(*str))
					return (free_zero(&line));
				++str;
			}
			free(line);
			return (get_antsnbr(line));
		}
		free(line);
	}
	return (0);
}

int					main(void)
{
	t_list		*file;
	int			anb;

	file = NULL;
	anb = find_antsnbr(&file);
	if (!anb)
		return (ft_error("ERROR"));
	ft_putnbr(anb);
	ft_putstr("\n");

	return (0);
}
