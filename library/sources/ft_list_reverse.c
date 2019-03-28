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

void	ft_list_reverse(t_lst **begin_list)
{
	t_lst	*last;
	t_lst	*next;
	t_lst	*tmp;

	if (begin_list && *begin_list)
	{
		last = *begin_list;
		if (last->next != NULL)
		{
			next = last->next;
			last->next = NULL;
			while (next->next != NULL)
			{
				tmp = next->next;
				next->next = last;
				last = next;
				next = tmp;
			}
		}
	}
}
