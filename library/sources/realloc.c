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

#include "_malloc.h"

/*
**	mnalloc une nouvelle zone puis copie le contenu de ptr dedans
*/

static void	*realloc_copy(void *ptr, size_t size, size_t n)
{
	void *naddr;

	if (!(naddr = malloc(size)))
		return (NULL);
	ft_memcpy(naddr, ptr, n);
	return (naddr);
}

/*
**	si !zone => NULL
**	si ya de la place, agrandit / rétrécit le chiffre dans le header
**	sinon, déplace, puis free
*/

static void	*realloc_exec(void *ptr, size_t size)
{
	t_zone	*cursor;
	void	*addr;

	if (!(cursor = ft_fetch_zone(ptr)))
		return (NULL);
	if (ft_zone_fit(size, cursor))
	{
		cursor->size = size;
		addr = cursor->addr;
	}
	else
	{
		if (!(addr = realloc_copy(ptr, size, cursor->size)))
			return (NULL);
		ft_free(cursor->addr);
		cursor->addr = addr;
	}
	return (addr);
}

/*
**	si size = 0 => ft_free(ptr)
**	si !ptr => malloc(size)
**	sinon => realloc exec
*/

void		*ft_realloc(void *ptr, size_t size)
{
	void	*new_zone;

	if (!size)
	{
		ft_free(ptr);
		return (NULL);
	}
	if (!ptr)
		new_zone = malloc(size);
	else
		new_zone = realloc_exec(ptr, size);
	return (new_zone);
}
