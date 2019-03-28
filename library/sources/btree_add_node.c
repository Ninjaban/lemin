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

static int	ft_next(t_btree **tree, t_btree **next, void *item)
{
	if (*next)
	{
		*tree = *next;
		return (0);
	}
	else
	{
		*next = (t_btree *)item;
		return (1);
	}
}

void		btree_add_node(t_btree **root, void *item,
						int (*cmpf)(void *, void *))
{
	t_btree	*tree;
	int		exit;

	if (!root || !item || !cmpf)
		return ;
	exit = (!(*root)) ? 1 : 0;
	tree = *root;
	if (!(*root))
		*root = (t_btree *)item;
	while (exit == 0)
	{
		if (cmpf(tree, item) < 0)
			exit = ft_next(&tree, &tree->left, item);
		else
			exit = ft_next(&tree, &tree->right, item);
	}
}
