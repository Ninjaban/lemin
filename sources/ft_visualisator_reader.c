/* ----------------------------------------------------------------------------+
                                                                               |
    .------..------..------..------..------..------..------..------..------.   |
    |P.--. ||R.--. ||E.--. ||V.--. ||I.--. ||S.--. ||I.--. ||O.--. ||N.--. |   |
    | :/\: || :(): || (\/) || :(): || (\/) || :/\: || (\/) || :/\: || :(): |   :
    | (__) || ()() || :\/: || ()() || :\/: || :\/: || :\/: || :\/: || ()() |
    | '--'P|| '--'R|| '--'E|| '--'V|| '--'I|| '--'S|| '--'I|| '--'O|| '--'N|
:   `------'`------'`------'`------'`------'`------'`------'`------'`------'
|
|    Created by Jonathan Carra.
|    Copyright (c) 2019 Prévision. All rights reserved.
+---------------------------------------------------------------------------- */

#include <error.h>
#include "get_next_line.h"
#include "libft.h"
#include "internal.h"

static void		ft_tabdel(char **tab)
{
	t_uint		n;

	n = 0;
	while (tab[n])
		free(tab[n++]);
	free(tab);
}

static void		ft_reader_init(t_map *map)
{
	(*map).salles = NULL;
	(*map).start = NULL;
	(*map).end = NULL;
	(*map).fourmis = NULL;
	(*map).nb_fourmis = 0;
}

static t_bool 	ft_reader_first_line(t_map *map)
{
	t_pchar		line;
	t_uint 		n;

	if (get_next_line(0, &line) != 1)
		return (FALSE);
	n = 0;
	while (line[n] != '\0')
		if (!ft_isdigit(line[n++]))
			return (FALSE);
	(*map).nb_fourmis = (t_uint)ft_atoi(line);
	if (((*map).fourmis = malloc(sizeof(t_fourmis) * (*map).nb_fourmis)) == NULL)
		return (FALSE);
	printf("%s\n", line);
	free(line);
	return (TRUE);
}

static void		ft_reader_fourmis_init(t_map *map)
{
	t_uint		n;

	n = 0;
	while (n < (*map).nb_fourmis)
	{
		(*map).fourmis[n].name = n + 1;
		(*map).fourmis[n].localisation = (*map).start->id;
		n = n + 1;
	}
}

static t_bool	ft_reader_file_get_salle(t_pchar line, t_pchar **tab)
{
	if ((*tab = ft_strsplit(line, " \t")) == NULL)
		return (FALSE);
	FT_DEBUG("line {%s} ft_tablen %ld", line, ft_tablen(*tab));
	if (ft_tablen(*tab) != 3)
	{
		ft_tabdel(*tab);
		return (FALSE);
	}
	return (TRUE);
}

static t_bool	ft_reader_file_new_salle(t_pchar line, t_salle *salle)
{
	static t_uint	id = 0;
	t_pchar			*tab;

	if (!ft_reader_file_get_salle(line, &tab))
		return (FALSE);

	(*salle).id = id++;
	(*salle).link = NULL;
	(*salle).name = ft_strdup(tab[0]);
	(*salle).position.x = ft_atoi(tab[1]) + 1;
	(*salle).position.y = ft_atoi(tab[2]);
	(*salle).fourmis = NULL;
	(*salle).path = FALSE;

	ft_tabdel(tab);
	return (TRUE);
}

static t_bool	ft_reader_file_get_link(t_pchar line, t_pchar **tab)
{
	if ((*tab = ft_strsplit(line, "\t-")) == NULL)
		return (FALSE);
	FT_DEBUG("line {%s} ft_tablen %ld", line, ft_tablen(*tab));
	if (ft_tablen(*tab) != 2)
	{
		ft_tabdel(*tab);
		return (FALSE);
	}
	return (TRUE);
}

static t_bool	ft_reader_file_new_link(t_map *map, t_pchar line, t_lst **link)
{
	t_pchar			*tab;
	t_salle			*a;
	t_salle			*b;
	t_lst			*tmp;
	t_link			*data;

	if (!ft_reader_file_get_link(line, &tab))
		return (FALSE);

	a = NULL;
	b = NULL;
	tmp = (*map).salles;
	while (tmp)
	{
		FT_DEBUG("data {%s} a {%s} b {%s}", ((t_salle *)(tmp->data))->name, tab[0], tab[1]);
		if (ft_strcmp(((t_salle *)(tmp->data))->name, tab[0]) == 0)
			a = tmp->data;
		if (ft_strcmp(((t_salle *)(tmp->data))->name, tab[1]) == 0)
			b = tmp->data;
		tmp = tmp->next;
	}
	if (!a || !b)
		return (FALSE);

	if ((data = malloc(sizeof(t_link))) == NULL)
		return (FALSE);
	data->A = a;
	data->B = b;

	ft_list_push_back(&a->link, b);
	ft_list_push_back(&b->link, a);
	ft_list_push_back(link, data);

	ft_tabdel(tab);
	return (TRUE);
}

static t_bool	ft_reader_file_salle_spe(t_map *map, t_bool start)
{
	t_pchar		line;
	t_salle		*salle;

	if (get_next_line(0, &line) != 1)
		return (FALSE);
	if ((salle = malloc(sizeof(t_salle))) == NULL)
		return (FALSE);
	if (!ft_reader_file_new_salle(line, salle))
		return (FALSE);
	if (start)
	{
		(*map).start = salle;
		ft_reader_fourmis_init(map);
	}
	else
		(*map).end = salle;
	ft_list_push_back(&(*map).salles, salle);
	printf("%s\n", line);
	free(line);
	return (TRUE);
}

static t_bool	ft_reader_file_salle(t_map *map, t_pchar line, t_lst **link)
{
	static t_bool	mode = FALSE;
	t_salle			*salle;

	if (mode == FALSE)
	{
		if ((salle = malloc(sizeof(t_salle))) == NULL)
			return (FALSE);
		if (ft_reader_file_new_salle(line, salle))
		{
			ft_list_push_back(&(*map).salles, (void *) salle);
			printf("%s\n", line);
			return (TRUE);
		}
		mode = TRUE;
	}

	if (!ft_reader_file_new_link(map, line, link))
		return (FALSE);

	printf("%s\n", line);
	return (TRUE);
}

static t_bool	ft_reader_file(t_map *map, t_lst **link)
{
	t_pchar		line;

	while (get_next_line(0, &line) == 1)
	{
		if (line[0] == '#')
		{
			FT_DEBUG("strcmp %d", ft_strcmp(line, "##start") == 0);
			printf("%s\n", line);
			if (ft_strcmp(line, "##start") == 0 &&
				!ft_reader_file_salle_spe(map, TRUE))
				return (FALSE);
			else if (ft_strcmp(line, "##end") == 0 &&
					 !ft_reader_file_salle_spe(map, FALSE))
				return (FALSE);
		}
		else if (!ft_reader_file_salle(map, line, link))
			return (FALSE);
		free(line);
	}
	return (TRUE);
}

static t_bool	ft_reader_turn_fourmis_check(t_pchar value, t_uint *name, t_uint *localisation)
{
	int		n;

	n = 0;
	if (value[n++] != 'L')
		return (FALSE);
	if (!ft_isdigit(value[n]))
		return (FALSE);
	while (value[n] && ft_isdigit(value[n]))
		n = n + 1;
	if (value[n++] != '-')
		return (FALSE);
	if (!ft_isdigit(value[n]))
		return (FALSE);
	*name = (t_uint)ft_atoi(value + 1);
	*localisation = (t_uint)ft_atoi(value + n);
	return (TRUE);
}

static t_bool	ft_reader_turn_fourmis(t_lst **fourmis, t_pchar line)
{
	t_pchar		*tab;
	int			n;
	t_fourmis	*data;

	if ((tab = ft_strsplit(line, " \t")) == NULL)
		return (FALSE);
	n = 0;
	while (tab[n])
	{
		if ((data = malloc((sizeof(t_fourmis)))) == NULL)
			return (FALSE);
		if (!ft_reader_turn_fourmis_check(tab[n], &data->name, &data->localisation))
		{
			free(data);
			return (FALSE);
		}
		ft_list_push_back(fourmis, data);
		n = n + 1;
	}
	return (TRUE);
}

static t_bool	ft_reader_turn(t_lst **turn)
{
	t_pchar		line;
	t_lst		*fourmis;

	while (get_next_line(0, &line) == 1)
	{
		fourmis = NULL;
		if (!ft_reader_turn_fourmis(&fourmis, line))
			return (FALSE);
		ft_list_push_back(turn, fourmis);
		free(line);
	}
	return (TRUE);
}

extern t_bool	ft_reader(void)
{
	t_map		map;
	t_lst		*turn;
	t_lst		*link;

	turn = NULL;
	link = NULL;
	ft_reader_init(&map);
	ft_reader_first_line(&map);
	ft_reader_file(&map, &link);
	if (!map.start || !map.end || !map.fourmis)
		return (FALSE);
	if (!ft_reader_turn(&turn))
		return (FALSE);
	if (!ft_visualisator(map, turn, link))
		return (FALSE);
	FT_DEBUG("%s", "OK");
	return (TRUE);

}