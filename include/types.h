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

#ifndef TYPES_H
# define TYPES_H

# include <stdint.h>

# define TRUE		1
# define FALSE		0

typedef char				t_bool;
typedef void *				t_pvoid;
typedef char *				t_pchar;
typedef unsigned char *		t_puchar;
typedef unsigned int		t_uint;
typedef long long			t_long;

typedef struct
{
	t_uint			size;
	t_pvoid			bytes;
} t_buffer;

#define BUFFER_CLEAR(target)					{ (target).size = 0; (target).bytes = NULL; }
#define BUFFER_SETUP(target, size, bytes)		{ (target).size = (size); (target).bytes = (bytes); }
#define BUFFER_CHECK(target)					{ (((target).size != 0) && ((target).bytes != NULL)) }

typedef struct		s_position
{
	int					x;
	int					y;
}					t_position;

#endif
