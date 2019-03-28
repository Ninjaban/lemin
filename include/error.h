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

#ifndef ERROR_H
# define ERROR_H

# include <stdio.h>
# include <inttypes.h>
# include <stdint.h>
# include <stdarg.h>

# ifndef	DEBUG_MODE
#  define	DEBUG_MODE		TRUE
#  define	WARNING_MODE	TRUE
#  define	ERROR_MODE		TRUE
# endif

#define FT_DEBUG(in_context, ...)																																		\
	do {																																								\
		if (DEBUG_MODE)																																					\
			(void) fprintf (stderr, "\033[38;5;14mDEBUG\033[0m:\033[38;5;244m%s\033[0m:\033[38;5;227m%" PRIu64 "\033[0m:\033[38;5;40m%s\033[0m: " in_context "\n",		\
					__FILE__, (uint64_t)__LINE__, __func__,																												\
					__VA_ARGS__);																																		\
	} while (0)

#define FT_WARNING(in_context, ...)																																		\
	do {																																								\
		if (WARNING_MODE)																																				\
			(void) fprintf (stderr, "\033[38;5;114mWARNING\033[0m:\033[38;5;244m%s\033[0m:\033[38;5;227m%" PRIu64 "\033[0m:\033[38;5;40m%s\033[0m: " in_context "\n",	\
					__FILE__, (uint64_t)__LINE__, __func__,																												\
					__VA_ARGS__);																																		\
	} while (0)

#define FT_ERROR(in_context, ...)																																		\
	do {																																								\
		if (ERROR_MODE)																																					\
			(void) fprintf (stderr, "\033[38;5;160mERROR\033[0m:\033[38;5;244m%s\033[0m:\033[38;5;227m%" PRIu64 "\033[0m:\033[38;5;40m%s\033[0m: " in_context "\n",		\
					__FILE__, (uint64_t)__LINE__, __func__,																												\
					__VA_ARGS__);																																		\
	} while (0)

#endif
