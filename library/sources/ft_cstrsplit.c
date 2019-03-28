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

static int	count_word(char const *s, char const c)
{
	int		n;
	int		word;

	n = 0;
	word = 0;
	while (s[n])
	{
		word = word + 1;
		while (s[n] && s[n] != c)
			n = n + 1;
		if (s[n] == c && s[n + 1] == '\0')
			word = word + 1;
		if (s[n])
			n = n + 1;
	}
	return (word);
}

static int	size_word(char const *s, char const c, int n)
{
	int		len;

	len = 0;
	while (s[n + len] && s[n + len] != c)
		len = len + 1;
	return (len);
}

static char	**complete_tab(char const *s, char const c, char **tab)
{
	int		n;
	int		i;
	int		j;
	char	bool;

	n = 0;
	i = 0;
	bool = 0;
	while (s[n] || (n > 0 && !s[n] && s[n - 1] == c))
	{
		if ((tab[i] = ft_malloc(size_word(s, c, n) + 1)) == NULL)
		{
			write(2, "malloc2", 7);
			return (NULL);
		}
		j = 0;
		while (s[n] && s[n] != c)
			tab[i][j++] = s[n++];
		tab[i++][j] = '\0';
		if (s[n])
			n = n + 1;
		if (bool == 1)
			break;
		if (!s[n])
			bool = 1;
	}
	return (tab);
}

char		**ft_cstrsplit(char const *s, char const c)
{
	char	**tab;
	int		word;

	if (s == NULL)
		return (NULL);
	word = count_word(s, c);
	if ((tab = ft_malloc(sizeof(char *) * (word + 1))) == NULL)
	{
		write(2, "malloc1", 7);
		return (NULL);
	}
	while (word >= 0)
		tab[word--] = NULL;
	if ((tab = complete_tab(s, c, tab)) == NULL)
		return (NULL);
	return (tab);
}
