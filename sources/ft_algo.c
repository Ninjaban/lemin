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

#include "libft.h"
#include "error.h"
#include "internal.h"

static void			ft_algo_move_path(t_lst *link)
{
	if (link->next)
		ft_algo_move_path(link->next);
	else
	{
		((t_salle *)link->data)->fourmis = NULL;
		return ;
	}
	if (((t_salle *)link->data)->fourmis && !((t_salle *)link->next->data)->fourmis)
	{
		printf("L%d-%s ", ((t_salle *)link->data)->fourmis->name, ((t_salle *)link->next->data)->name);
		(*((t_salle *)link->data)->fourmis).localisation = ((t_salle *)link->next->data)->id;
		((t_salle *)link->next->data)->fourmis = ((t_salle *)link->data)->fourmis;
		((t_salle *)link->data)->fourmis = NULL;
	}
}

static void			ft_algo_move(t_lst *path)
{
	if (path->next)
		ft_algo_move(path->next);
	ft_algo_move_path(((t_path *)path->data)->link);
}

static void	 		ft_algo_fourmis(t_map map, t_lst *path)
{
	t_lst		*tmp;
	t_uint		n;

	tmp = path;
	while (tmp)
	{
		n = 0;
		while (n < map.nb_fourmis && map.fourmis[n].localisation != map.start->id)
			n = n + 1;
		if (n < map.nb_fourmis)
		{
			FT_DEBUG("fourmis %d", map.fourmis[n].name);
			if (!((t_salle *) (((t_path *) tmp->data)->link->data))->fourmis)
			{
				printf("L%d-%s ", map.fourmis[n].name, ((t_salle *) (((t_path *) tmp->data)->link->data))->name);
				((t_salle *) (((t_path *) tmp->data)->link->data))->fourmis = &map.fourmis[n];
				map.fourmis[n].localisation = ((t_salle *) (((t_path *) tmp->data)->link->data))->id;
			}
		}
		tmp = tmp->next;
	}
}

static t_bool		ft_algo_check_end(t_map map)
{
	t_uint		n;

	n = 0;
	while (n < map.nb_fourmis)
	{
		if (map.fourmis[n].localisation != map.end->id)
			return (FALSE);
		n = n + 1;
	}
	return (TRUE);
}

extern t_bool		ft_algo(t_map map, t_lst *path)
{
	printf("\n");
	while (!ft_algo_check_end(map))
	{
		ft_algo_move(path);
		ft_algo_fourmis(map, path);
		printf("\n");
	}
	return (TRUE);
}