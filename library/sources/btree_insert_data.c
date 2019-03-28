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

void	btree_insert_data(t_btree **root, void *item,
							int (*cmpf)(void *, void *))
{
	t_btree	*tree;
	int		exit;

	exit = 0;
	tree = *root;
	if (tree && cmpf)
		while (exit == 0)
		{
			if (cmpf(tree->item, item) < 0)
			{
				if (tree->left != NULL)
					tree = tree->left;
				else
					tree->left = btree_create_node(item);
			}
			else
			{
				if (tree->right != NULL)
					tree = tree->right;
				else
					tree->right = btree_create_node(item);
			}
		}
}
