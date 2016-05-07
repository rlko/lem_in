/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rms.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 09:22:59 by rliou-ke          #+#    #+#             */
/*   Updated: 2016/05/07 03:24:20 by akarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RMS_H
# define RMS_H
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include "gnl.h"

# define INTMAX		2147483647
# define C_RED		"\x1b[31m"
# define C_GREEN	"\x1b[32m"
# define C_YELLOW	"\x1b[33m"
# define C_BLUE		"\x1b[34m"
# define C_MAGENTA	"\x1b[35m"
# define C_CYAN		"\x1b[36m"
# define C_RESET	"\x1b[0m"

enum		e_type
{
	RGROOM,
	STROOM,
	EDROOM,
	PIZZA
};

typedef struct		s_dome
{
	char			*name;
	enum e_type		type;
	struct s_dome	*next;
	char			*x;
	char			*y;
	t_list			*adj;
	int				depth;
	int				pizza;
	int				occupied;
}					t_dome;

typedef struct		s_ant
{
	int				id;
	t_dome			*room;
	t_dome			*prev;
	int				played;
	int				ate;
}					t_ant;

typedef struct		s_lm
{
	int				nb_ants;
	t_dome			*rooms;
	t_list			*ants;
	int				opt[128];	
}					t_lm;

char				**read_opts(int *t_opt, char **av);
int					ft_verror(char *verbose, int *t_opt);
void				ft_exit_verror(char *verbose, int *t_opt);

t_list				**ft_lsttower(t_list **head, char *str);
t_dome				*get_room(t_dome *lst, enum e_type type);

int					find_antsnbr(t_list **file, int *t_opt);
int					str_iscomment(char *str);
int					str_iscommand(char *str, int strict, int opt);

void				assign_room(t_list *lst, t_dome **room);
void				assign_type(t_dome **room, char *prev, int *t_opt);
int					mk_rooms(t_dome **head, char **prev, char *line, int *opt);
t_dome				*find_rooms(t_list **file, int *t_opt);

void				fill_connections(t_list *lst, t_dome **head);
int					get_room_links(char *line, t_dome **room);
void				find_connections(t_list **file, t_dome **room, int *t_opt);

int					ft_is_solvable(t_dome *room, int *opt);
void				colorize(t_dome *rooms);

t_list				*instantiate_ants(int n, t_dome *room);
void				reinit_depth(t_dome *rooms);
void				find_your_raison_d_etre(t_ant *ant, t_dome *head, int *opt);
void				shit_just_got_serious(t_lm box);

void				print_turn(t_list *ants);
void				print_file_and_bye(t_list **file, int *t_opt);
void				print_count_turn(int count, int *opt);
void				print_pizza(t_dome *head, int nbants, int *opt);
void				ft_print_pizzatime(t_ant *ant, int *opt);
//void				print_route(t_dome *rooms, int *opt);
void				print_route(t_list **route, t_dome *rooms);

void				print_rooms(t_dome *room);
void				print_room_links(char *name, t_dome *room);
void				print_ant_status(t_list *ant);
#endif
