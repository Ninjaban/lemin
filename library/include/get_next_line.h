
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include "libft.h"

int		get_next_line(const int fd, char **line);

# define BUFF_SIZE		(4096)
# define SUCCESS_READ   (1)
# define FINISH			(0)
# define ERROR			(-1)
# define ENDLINE		('\n')

#endif
