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
**	Crée un nouveau header de plage au début de la plage obtenus par mmap. La
**	position du header sera @addr, la taille de la plage (avec les headers) sera
**	@size et @zonelen correspond à la taille de la première zone de la plage.
**
**	Ajoute ensuite cette nouvelle plage à la fin de la liste des plages.
**
**	@param addr
**	@param size
**	@param zonelen
**	@return
*/

static void		ft_newhead(void *addr, size_t size, size_t zonelen)
{
	t_head		*head;

	head = addr;
	head->size = size;
	head->next = NONE;
	head->zones = ft_newzone(addr + sizeof(t_head),
							 addr + size - zonelen, zonelen);
	g_mem->addr = head;
}

/*
**	initialise la variable globale
*/

void			ft_mem_init(size_t len)
{
	t_mem	*mem;
	void	*plage;
	size_t	size;

	mem = mmap(0, (size_t)getpagesize(), PROT_READ | PROT_WRITE,
				MAP_PRIVATE | MAP_ANON, -1, 0);
	mem->addr = NONE;
	mem->sz = getpagesize();

	g_mem = mem;

	size = ft_getsize(len);
	if ((plage = mmap(0, size, PROT_READ | PROT_WRITE,
					  MAP_PRIVATE | MAP_ANON, -1, 0)) != (void *)-1)
		ft_newhead(plage, size, len);
}
