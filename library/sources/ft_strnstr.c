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

static int	ft_cmp(const char *str, const char *src, size_t len)
{
	size_t	n;

	n = 0;
	while (str[n] == src[n] && str[n] && src[n] && n < len)
		n = n + 1;
	if (!src[n])
		return (str[n - 1] - src[n - 1]);
	return (str[n] - src[n]);
}

char		*ft_strnstr(const char *str, const char *src, size_t len)
{
	size_t	n;

	n = 0;
	if (!str || !src)
		return (NULL);
	if (!src[0])
		return ((char *)str);
	while (str[n])
	{
		while (str[n] && str[n] != src[0])
			n = n + 1;
		if (ft_cmp(str + n, src, len) == 0 && (n + ft_strlen(src)) <= len)
			return ((char *)(str + n));
		if (str[n])
			n = n + 1;
	}
	return (NULL);
}
