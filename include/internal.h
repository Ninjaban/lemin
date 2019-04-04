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

#ifndef INTERNAL_H
# define INTERNAL_H

#include "types.h"

# define QUEUE_SIZE			(WINDOW_SIZE_X * WINDOW_SIZE_Y)

typedef struct		s_fourmis
{
	t_uint			name;

	t_uint			localisation;
}					t_fourmis;

typedef struct		s_salle
{
	t_pchar			name;
	t_position		position;

	t_uint 			id;

	t_lst			*link;
	t_fourmis		*fourmis;
	t_bool			path;
}					t_salle;

typedef struct		s_map
{
	t_lst			*salles;
	t_salle			*start;
	t_salle			*end;

	t_fourmis		*fourmis;
	t_uint			nb_fourmis;
}					t_map;

typedef struct		s_path
{
	t_lst			*link;
	t_uint			size;
}					t_path;

typedef struct		s_link
{
	t_salle			*A;
	t_salle			*B;
}					t_link;

typedef struct		s_end_link
{
	t_position		end;
	int				xmin;
	int				xmax;
	int				ymin;
	int				ymax;
}					t_end_link;

extern t_bool		ft_reader(void);
extern t_bool		ft_path(t_map map);
extern t_bool		ft_algo(t_map map, t_lst *path);
extern t_bool		ft_visualisator(t_map map, t_lst *turn, t_lst *link);

#endif
