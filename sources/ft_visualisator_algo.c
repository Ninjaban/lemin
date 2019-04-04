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

#include <locale.h>
#include <curses.h>
#include "libft.h"
#include "error.h"
#include "internal.h"
#include "visualisator.h"

static void			ft_visualisator_init(WINDOW **window)
{
	initscr();
	start_color();
	*window = newwin(WINDOW_SIZE_Y, WINDOW_SIZE_X, 0, 0);
	cbreak();
	noecho();
	curs_set(0);
	wrefresh(*window);
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_RED, COLOR_BLACK);
}

static t_bool		ft_visualisator_draw_room(t_map map, WINDOW *window, t_bool color)
{
	t_lst		*tmp;
	t_salle		*salle;

	tmp = map.salles;
	while (tmp)
	{
		salle = tmp->data;
		if (salle->position.x <= 0 || salle->position.x >= WINDOW_SIZE_X || salle->position.y < 0 || salle->position.y >= WINDOW_SIZE_Y)
			return (FALSE);

		if (color && salle->position.y == map.start->position.y && salle->position.x == map.start->position.x)
			wattron(window, COLOR_PAIR(3));
		else if (color && salle->position.y == map.end->position.y && salle->position.x == map.end->position.x)
			wattron(window, COLOR_PAIR(5));
		mvwprintw(window, salle->position.y, salle->position.x - 1, "[%s]", salle->name);
		if (color)
		wattron(window, COLOR_PAIR(1));

		tmp = tmp->next;
	}
	wrefresh(window);
	return (TRUE);
}

static t_position	ft_visualisator_draw_link_path(t_position A, t_position B, t_bool mode)
{
	t_position		C;

	C.x = B.x - A.x;
	C.y = B.y - A.y;

	if ((mode) ? ABS(C.x) > ABS(C.y) : ABS(C.x) < ABS(C.y))
	{
		C.y = A.y;
		C.x = A.x + C.x / ((ABS(C.x)) ? ABS(C.x) : 1);
	}
	else
	{
		C.x = A.x;
		C.y = A.y + C.y / ((ABS(C.y)) ? ABS(C.y) : 1);
	}
	return (C);
}

static void			ft_visualisator_draw_link_set_queue(t_position (*queue)[QUEUE_SIZE], int n, int x, int y)
{
	(*queue)[n].x = x;
	(*queue)[n].y = y;
}

static t_bool		ft_visualisator_draw_link_print(t_position position, t_position (*queue)[QUEUE_SIZE], int nbr)
{
	ft_visualisator_draw_link_set_queue(queue, nbr, position.x, position.y);
	return (TRUE);
}

static t_position	ft_visualisator_draw_link_path_next(t_position A, t_uint nbr)
{
	t_position		C;

	if (nbr == 1)
	{
		C.y = A.y;
		C.x = A.x + 1;
	}
	else if (nbr == 2)
	{
		C.y = A.y + 1;
		C.x = A.x;
	}
	else if (nbr == 3)
	{
		C.y = A.y;
		C.x = A.x - 1;
	}
	else
	{
		C.y = A.y - 1;
		C.x = A.x;
	}
	return (C);
}

static t_bool		ft_visualisator_draw_link_check(t_position A, t_end_link B)
{
	if (A.x >= B.xmin && A.x <= B.xmax && A.y >= B.ymin && A.y <= B.ymax)
	{
		if ((A.x == B.xmin && A.y == B.ymin) || (A.x == B.xmax && A.y == B.ymax) ||
			(A.x == B.xmin && A.y == B.ymax) || (A.x == B.xmax && A.y == B.ymin))
			return (FALSE);
		return (TRUE);
	}
	return (FALSE);
}

static t_bool		ft_visualisator_draw_link_rec(t_position A, t_end_link B, char tab[WINDOW_SIZE_Y][WINDOW_SIZE_X], WINDOW *window, t_position (*queue)[QUEUE_SIZE], int nbr)
{
	t_position		C;

	if (ft_visualisator_draw_link_check(A, B))
		return (ft_visualisator_draw_link_print(A, queue, nbr));
	if (A.x <= MARGE_X || A.y < 0 || A.x >= WINDOW_SIZE_X || A.y >= WINDOW_SIZE_Y)
		return (FALSE);

	if (tab[A.y][A.x] != FALSE || mvwinch(window, A.y, A.x) != ' ')
		return (FALSE);
	tab[A.y][A.x] = TRUE;
	C = ft_visualisator_draw_link_path(A, B.end, TRUE);
	if (ft_visualisator_draw_link_rec(C, B, tab, window, queue, nbr + 1))
		return (ft_visualisator_draw_link_print(A, queue, nbr));
	C = ft_visualisator_draw_link_path(A, B.end, FALSE);
	if (ft_visualisator_draw_link_rec(C, B, tab, window, queue, nbr + 1))
		return (ft_visualisator_draw_link_print(A, queue, nbr));
	for (t_uint n = 1 ; n <= 4 ; ++ n)
		if (ft_visualisator_draw_link_rec(ft_visualisator_draw_link_path_next(A, n), B, tab, window, queue, nbr + 1))
			return (ft_visualisator_draw_link_print(A, queue, nbr));

	return (FALSE);
}

static t_bool		ft_visualisator_draw_link_launch(t_position A, t_end_link B, char tab[WINDOW_SIZE_Y][WINDOW_SIZE_X], WINDOW *window, t_position (*queue)[QUEUE_SIZE], int nbr)
{
	t_position		C;
	t_position		D;

	if (ft_visualisator_draw_link_check(A, B))
		return (ft_visualisator_draw_link_print(A, queue, nbr));
	if (tab[A.y][A.x] != FALSE || mvwinch(window, A.y, A.x) == '*')
		return (FALSE);
	tab[A.y][A.x] = TRUE;

	C = ft_visualisator_draw_link_path(A, B.end, TRUE);
	D = ft_visualisator_draw_link_path(A, B.end, FALSE);
	if (mvwinch(window, A.y, A.x) != ' ')
	{
		if (ft_visualisator_draw_link_launch(C, B, tab, window, queue, nbr))
			return (TRUE);
		if (ft_visualisator_draw_link_launch(D, B, tab, window, queue, nbr))
			return (TRUE);
		for (t_uint i = 1; i <= 4; ++i)
			if (ft_visualisator_draw_link_launch(ft_visualisator_draw_link_path_next(A, i), B, tab, window, queue, nbr))
				return (TRUE);
	}
	else
	{
		if (ft_visualisator_draw_link_rec(C, B, tab, window, queue, nbr + 1))
			return (ft_visualisator_draw_link_print(A, queue, nbr));
		if (ft_visualisator_draw_link_rec(D, B, tab, window, queue, nbr + 1))
			return (ft_visualisator_draw_link_print(A, queue, nbr));
		for (t_uint i = 1; i <= 4; ++i)
			if (ft_visualisator_draw_link_rec(ft_visualisator_draw_link_path_next(A, i), B, tab, window, queue, nbr + 1))
				return (ft_visualisator_draw_link_print(A, queue, nbr));
	}
	return (FALSE);
}

static t_bool		ft_visualisator_draw_link_isadj(t_position A, t_position B)
{
	int		k;

	k = ABS((B.x - A.x)) + ABS((B.y - A.y));
	if (k == 1)
		return (TRUE);
	return (FALSE);
}

static void			ft_visualisator_draw_link_epur_move(t_position (*queue)[QUEUE_SIZE], int n, int i)
{
	while (n < QUEUE_SIZE)
	{
		ft_visualisator_draw_link_set_queue(queue, i, (*queue)[n].x, (*queue)[n].y);
		i = i + 1;
		n = n + 1;
	}
	while (i < QUEUE_SIZE)
		ft_visualisator_draw_link_set_queue(queue, i++, -1, -1);

}

static void			ft_visualisator_draw_link_epur(t_position (*queue)[QUEUE_SIZE])
{
	t_bool		doSomething;

	doSomething = TRUE;
	while (doSomething == TRUE)
	{
		doSomething = FALSE;
		for (int n = 0 ; n < QUEUE_SIZE && (*queue)[n].x != -1 && (*queue)[n].y != -1 && doSomething == FALSE ; ++ n)
			for (int i = 0 ; i < n - 1 && doSomething == FALSE ; ++ i)
			{
				if (ft_visualisator_draw_link_isadj((*queue)[n], (*queue)[i]))
				{
					ft_visualisator_draw_link_epur_move(queue, n, i + 1);
					doSomething = TRUE;
				}
			}
	}
}

static void			ft_visualisator_draw_link_draw(t_position queue[QUEUE_SIZE], int n, WINDOW *window)
{
	char		*c;
	int			x1;
	int			y1;
	int			x2;
	int			y2;

	c = "*";
	if (n > 0 && n < QUEUE_SIZE - 1 && queue[n + 1].x != -1 && queue[n + 1].y != -1)
	{
		x1 = (queue[n].x - queue[n - 1].x);
		y1 = (queue[n].y - queue[n - 1].y);
		x2 = (queue[n + 1].x - queue[n].x);
		y2 = (queue[n + 1].y - queue[n].y);
		if (ABS((queue[n].x - queue[n - 1].x)) && ABS((queue[n].x - queue[n + 1].x)))
			c = "─";
		else if (ABS((queue[n].y - queue[n - 1].y)) && ABS((queue[n].y - queue[n + 1].y)))
			c = "│";
		else if ((x1 == 1 && y1 == 0 && x2 == 0 && y2 == -1) ||
				(x1 == 0 && y1 == 1 && x2 == -1 && y2 == 0))
			c = "┘";
		else if ((x1 == 0 && y1 == -1 && x2 == 1 && y2 == 0) ||
				(x1 == -1 && y1 == 0 && x2 == 0 && y2 == 1))
			c = "┌";
		else if ((x1 == 1 && y1 == 0 && x2 == 0 && y2 == 1) ||
				(x1 == 0 && y1 == -1 && x2 == -1 && y2 == 0))
			c = "┐";
		else if ((x1 == 0 && y1 == 1 && x2 == 1 && y2 == 0) ||
				 (x1 == -1 && y1 == 0 && x2 == 0 && y2 == -1))
			c = "└";
	}
	mvwprintw(window, queue[n].y, queue[n].x, c);
}

static t_bool		ft_visualisator_draw_link_init(t_position A, t_end_link B, char tab[WINDOW_SIZE_Y][WINDOW_SIZE_X], WINDOW *window)
{
	t_position		queue[QUEUE_SIZE];

	for (int i = 0 ; i < QUEUE_SIZE ; ++ i)
		ft_visualisator_draw_link_set_queue(&queue, i, -1, -1);

	for (t_uint i = 0 ; i < WINDOW_SIZE_Y ; ++ i)
		ft_memset(tab[i], FALSE, WINDOW_SIZE_X);
	if (!ft_visualisator_draw_link_launch(A, B, tab, window, &queue, 0))
		return (FALSE);

	ft_visualisator_draw_link_epur(&queue);

	for (int i = 0 ; i < QUEUE_SIZE && queue[i].x != -1 && queue[i].y != -1 ; ++ i)
		ft_visualisator_draw_link_draw(queue, i, window);
	return (TRUE);
}

static t_bool		ft_visualisator_draw_link(t_lst *link, WINDOW *window)
{
	char		tab[WINDOW_SIZE_Y][WINDOW_SIZE_X];
	t_lst		*tmp;
	t_link		*data;
	t_end_link	B;

	tmp = link;
	while (tmp)
	{
		data = tmp->data;

		B.end = data->B->position;
		B.xmin = B.end.x - 2;
		B.xmax = B.end.x + (int)ft_strlen(data->B->name) + 1;
		B.ymin = B.end.y - 1;
		B.ymax = B.end.y + 1;

		ft_visualisator_draw_link_init(data->A->position, B, tab, window);

		tmp = tmp->next;
	}
	return (TRUE);
}

static t_bool		ft_visualisator_menu(WINDOW *window)
{
	t_pchar		menu[MENU_SIZE] = {"Suivant", "Précédent", "Quitter"};
	int			choix;
	int			highlight;

	highlight = 0;
	mvwvline(window, 0, MARGE_X - 1, ACS_VLINE, WINDOW_SIZE_Y);
	nodelay(window, FALSE);
	notimeout(window, FALSE);
	keypad(window, TRUE);
	while (1)
	{
		for (int i = 0 ; i < MENU_SIZE ; ++ i)
		{
			if (i == highlight)
				wattron(window, A_REVERSE);
			mvwprintw(window, i + 1, 2, menu[i]);
			wattroff(window, A_REVERSE);
		}
//		sleep(1);
		wrefresh(window);
		choix = wgetch(window);
//		FT_DEBUG("Choix : %d Enter %d", choix, KEY_ENTER);

		if (choix == KEY_UP)
			highlight = (highlight - 1 >= 0) ? highlight - 1 : highlight;
		else if (choix == KEY_DOWN)
			highlight = (highlight + 1 < MENU_SIZE) ? highlight + 1 : highlight;
		else if (choix == 10 && highlight == MENU_EXIT)
			return (TRUE);
	}
//	FT_DEBUG("Choix : %d", choix);
	return (TRUE);
}

static t_bool		ft_visualisator_main(t_map map, t_lst *turn, t_lst *link, WINDOW *window)
{
	(void)turn;
	if (!ft_visualisator_draw_room(map, window, FALSE))
		return (FALSE);
	if (!ft_visualisator_draw_link(link, window))
		return (FALSE);
	if (!ft_visualisator_draw_room(map, window, TRUE))
		return (FALSE);
	if (!ft_visualisator_menu(window))
		return (FALSE);
	wrefresh(window);
	return (TRUE);
}

extern t_bool		ft_visualisator(t_map map, t_lst *turn, t_lst *link)
{
	WINDOW		*window;

	setlocale(LC_ALL, "fr_FR.UTF-8");
	ft_visualisator_init(&window);
	ft_visualisator_main(map, turn, link, window);
	delwin(window);
	endwin();
	return (TRUE);
}