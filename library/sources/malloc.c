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

#include <stdio.h>
#include "_malloc.h"

/*
**	Initialise la variable global g_mem à NULL par défault
*/

t_mem		*g_mem = NONE;

/*
**	Revois le nombre d'octets non utiliser dans la plage.
**
**	addr est le header de la plage où chercher.
*/

static size_t	ft_getsizeless(t_head *addr)
{
	t_zone	*zone;

	zone = addr->zones;
	if (zone != NONE)
	{
		while (zone->next != NONE)
			zone = zone->next;
		return ((size_t)(zone->addr - (void *)(zone + 1)));
	}
	return (addr->size);
}

/*
**	verifie si il est possible de reserver dans les plages déjà crée une zone de
**	taille @len.
**
**	@addr est la première plage crée.
**
**	La fonction getnextzone cherche dans toutes les plages crée sans exeption.
**
**	@param addr
**	@param len
**	@return
*/

static void		*ft_getnextzone(t_head *addr, size_t len)
{
	t_zone	*zone;

	zone = addr->zones;
	if (addr->zones == NONE && addr->size - HEADER_MAX >= len)
		return ((void *)addr + addr->size - len);
	if (addr->size > len && ft_getsizeless(addr) >= sizeof(t_zone))
		while (zone != NONE)
		{
			if (zone->next != NONE && len <=
				(size_t)(zone->addr - (zone->next->addr + zone->next->size)))
			{
				return (zone->next->addr + zone->next->size);
			}
			else if (zone->next == NONE && len + sizeof(t_zone) <=
			(size_t)((zone->addr) - (void *)(zone + 1)))
			{
				return (zone->addr - len);
			}
			zone = zone->next;
		}
	return ((addr->next != NONE) ? ft_getnextzone(addr->next, len) : NULL);
}

/*
**	Recherche à nouveau dans toutes les plages @addr le pointeur sur la zone
**	précédent la nouvelle zone @ptr.
**
**	Une fois trouvé, crée la nouvelle zone via structzone, en envoyant le header
**	précédant la nouvelle zone à créer, la nouvelle zone à créer @ptr, et sa
**	taille @len.
**
**	@param addr
**	@param ptr
**	@param len
*/

static void		ft_addzone(t_head *addr, void *ptr, size_t len)
{
	t_head		*tmp;
	t_zone		*ztmp;

	tmp = addr;
	while (tmp != NONE)
	{
		ztmp = tmp->zones;
		if (tmp->zones == NONE && (void *)tmp + tmp->size - len == ptr)
		{
			tmp->zones = ft_newzone((void *)tmp + sizeof(t_head), ptr, len);
			return ;
		}
		while (ztmp != NONE)
		{
			if (((ztmp->next != NONE) ? ztmp->next->addr + ztmp->next->size :
					ztmp->addr - len) == ptr)
			{
				ft_structzone(ztmp, ptr, len);
				return ;
			}
			ztmp = ztmp->next;
		}
		tmp = tmp->next;
	}
}

/*
**	Vérifie si la global g_mem existe, si non, la crée.
**
**	Vérifie si une nouvelle zone de taille @len peut etre ajouté dans les plages
**	déjà crée.
**
**	Si oui, appelle addzone(); pour crée une nouvelle zone de taille @len dans
**	les plages existante.
**
**	Si non, appelle crée une nouvelle plage à l'aide de getsize() et de mmap(),
**	puis ajoute une header de plage et crée la nouvelle zone à l'aide de
**	newhead();.
**
**	@param len
**	@return
*/

void			*ft_malloc(size_t len)
{
	void		*addr;

	if (g_mem == NONE)
	{
		ft_mem_init(len);
		return (g_mem->addr->zones->addr);
	}
	if (g_mem->addr != NONE && (addr = ft_getnextzone(g_mem->addr, len)))
		ft_addzone(g_mem->addr, addr, len);
	else
		return (NULL);
	return (addr);
}
