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

char		*ft_strtrim(char const *s)
{
	char	*str;
	int		start;
	int		end;
	int		n;

	if (s == NULL)
		return (NULL);
	n = 0;
	start = 0;
	end = (int)ft_strlen((char *)s) - 1;
	while (s[start] == ' ' || s[start] == '\t' || s[start] == '\n')
		start = start + 1;
	while (end > 0 && (s[end] == ' ' || s[end] == '\t' || s[end] == '\n'))
		end = end - 1;
	if (end < start)
		return (NULL);
	else if ((str = ft_malloc(end - start + 2)) == NULL)
		return (NULL);
	while (start <= end)
		str[n++] = s[start++];
	str[n] = '\0';
	return (str);
}
