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
#include "libft.h"
#include "internal.h"

static int			f(const char *a, const char *b)
{
	return (((t_path *)a)->size - ((t_path *)b)->size);
}

static t_bool		ft_path_search_end(t_salle *salle, t_path *data, t_uint n, t_map map, t_uint *path_nbr)
{
	t_lst			*tmp;

	if (salle->id == map.end->id)
	{
		if (*path_nbr != 0)
		{
			*path_nbr = *path_nbr - 1;
			return (FALSE);
		}
		FT_DEBUG("%d | %s", n, salle->name);
		ft_list_push_front(&((*data).link), salle);
		(*data).size = n;
		return (TRUE);
	}
	if (salle->id == map.start->id || salle->path == TRUE)
		return (FALSE);
	tmp = salle->link;
	salle->path = TRUE;
	while (tmp)
	{
		if (ft_path_search_end(((t_salle *)tmp->data), data, n + 1, map, path_nbr))
		{
			FT_DEBUG("%d | %s", n, salle->name);
			ft_list_push_front(&((*data).link), salle);
			salle->path = FALSE;
			return (TRUE);
		}
		tmp = tmp->next;
	}
	salle->path = FALSE;
	return (FALSE);
}

static void			ft_path_print(t_lst *path)
{
	t_lst		*tmp;
	t_lst		*link;

	tmp = path;
	while (tmp)
	{
		link = ((t_path *)(tmp->data))->link;
		FT_DEBUG("%d | ", ((t_path *)tmp->data)->size);
		while (link)
		{
			FT_DEBUG("%s -> ", ((t_salle *)link->data)->name);
			link = link->next;
		}
		tmp = tmp->next;
	}
}

static t_bool		ft_path_dispo(t_lst **path, t_lst *pointer)
{
	t_lst		*save;
	t_lst		*tmp;
	t_lst		*link;
	t_lst		*link2;

	save = *path;
	pointer = (*path)->next;
	while (pointer)
	{
		link = ((t_path *)(pointer->data))->link;
		while (link)
		{
			tmp = *path;
			while (tmp != pointer)
			{
				link2 = ((t_path *) (tmp->data))->link;
				while (link2)
				{
					if (((t_salle *) link2->data)->id == ((t_salle *) link->data)->id && link->next)
					{
						save->next = pointer->next;
						ft_list_del(pointer, &free);
						return (ft_path_dispo(path, save->next));
					}
					link2 = link2->next;
				}
				tmp = tmp->next;
			}
			link = link->next;
		}
		save = pointer;
		pointer = pointer->next;
	}
	return (TRUE);
}

extern t_bool		ft_path(t_map map)
{
	t_lst			*path;
	t_path			*data;
	t_lst			*tmp;
	t_uint			path_nbr;
	t_uint			path_nbr_tmp;

	path = NULL;
	tmp = map.start->link;
	path_nbr = 0;
	while (tmp)
	{
		path_nbr_tmp = path_nbr;
		if ((data = malloc(sizeof(t_path))) == NULL)
			return (FALSE);
		data->link = NULL;
		data->size = 0;
		if (ft_path_search_end(tmp->data, data, 1, map, &path_nbr_tmp))
		{
			ft_list_push_back(&path, data);
			path_nbr = path_nbr + 1;
		}
		else
		{
			path_nbr = 0;
			free(data);
		}
		if (!path_nbr)
			tmp = tmp->next;
		FT_DEBUG("%s", "");
	}
	if (!path)
		return (FALSE);

	ft_list_sort(&path, &f);
	FT_DEBUG("Nombre(s) de chemin(s): %d", ft_list_size(path));
	ft_path_print(path);

	FT_DEBUG("Listes des chemins disponibles:%s", "");
	ft_path_dispo(&path, path->next);
	ft_path_print(path);

	ft_algo(map, path);

	return (TRUE);
}