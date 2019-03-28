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

static int	count_size(int n)
{
	int		nbr;

	nbr = 0;
	if (n < 0)
		nbr = nbr + 1;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		nbr = nbr + 1;
		n = n / 10;
	}
	return (nbr);
}

static char	*complete_str(char *str, int n, char neg)
{
	int		i;

	i = 0;
	if (n == 0)
		str[i++] = '0';
	while (n != 0)
	{
		str[i++] = (ABS(n % 10)) + '0';
		n = n / 10;
	}
	if (neg == 1)
		str[i++] = '-';
	str[i] = '\0';
	return (str);
}

char		*ft_itoa(int n)
{
	char	*str;

	if ((str = ft_malloc(count_size(n) + 1)) == NULL)
		return (NULL);
	str = (n < 0) ? complete_str(str, n, 1) : complete_str(str, n, 0);
	if ((str = ft_revstr(str)) == NULL)
		return (NULL);
	return (str);
}
