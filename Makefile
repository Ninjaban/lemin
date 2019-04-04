#  ----------------------------------------------------------------------------+
#                                                                              |
#   .------..------..------..------..------..------..------..------..------.   |
#   |P.--. ||R.--. ||E.--. ||V.--. ||I.--. ||S.--. ||I.--. ||O.--. ||N.--. |   |
#   | :/\: || :(): || (\/) || :(): || (\/) || :/\: || (\/) || :/\: || :(): |   |
#   | (__) || ()() || :\/: || ()() || :\/: || :\/: || :\/: || :\/: || ()() |   |
#   | '--'P|| '--'R|| '--'E|| '--'V|| '--'I|| '--'S|| '--'I|| '--'O|| '--'N|   |
#   `------'`------'`------'`------'`------'`------'`------'`------'`------'   |
#                                                                              |
#    Created by Jonathan Carra.                                                |
#    Copyright (c) 2019 Prévision. All rights reserved.                        |
#  ----------------------------------------------------------------------------+

NAME_LEMI	=	lem-in
NAME_VISU	=	visualisateur

LIB			=	libft.a

SRC_LEMI	=	main.c \
				ft_reader.c \
				ft_path.c \
				ft_algo.c
SRC_VISU	=	visualisator_main.c \
				ft_visualisator_reader.c \
				ft_visualisator_algo.c

DIRSRC		=	sources/
DIRINC		=	include/
DIRLIB		=	library/
DIROBJ		=	objects/

LIBS		=	$(LIB:%=$(DIRLIB)%)

OBJS_LEMI	=	$(addprefix $(DIROBJ), $(SRC_LEMI:.c=.o))
OBJS_VISU	=	$(addprefix $(DIROBJ), $(SRC_VISU:.c=.o))

CFLAGS		=	-Wall -Wextra -Werror -I./$(DIRINC) -I./$(DIRLIB)$(DIRINC) -g3
LFLAGS		=	-lncursesw

CC			=	gcc
RM			=	rm -rf
ECHO		=	printf
MAKE		=	make -sC

CLEAN		=	"                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         "
LEN			=	$$(/bin/echo -n $(NAME) | wc -c)
DELTA		=	$$(echo "$$(tput cols)-32-$(LEN)"|bc)
NB			=	$(words $(SRC))
INDEX		=	0
SHELL		=	/bin/bash

all				:	$(DIROBJ) $(NAME_LEMI) $(NAME_VISU)

$(NAME_LEMI)	:	data_lemi $(OBJS_LEMI)
	@$(eval OBJ_LEN=$(shell echo "$(NAME)" | wc -c))
	@$(eval CLEAN_LEN=$(shell echo "$$(tput cols)-6-$(OBJ_LEN)"|bc))
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS_LEMI) $(LIBS)
	@$(ECHO) "\r\033[38;5;040m✓ MAKE $(NAME)%.*s\033[0m\033[0m\n" $(CLEAN_LEN) $(CLEAN)
data_lemi		:
	@$(eval LEN=$(shell echo $$(/bin/echo -n $(NAME_LEMI) | wc -c)))
	@$(eval DELTA=$(shell echo $$(echo "$$(tput cols)-32-$(LEN)"|bc)))
	@$(eval NB=$(shell echo $(words $(SRC_LEMI))))
	@$(eval INDEX=0)
	@$(eval NAME=$(shell echo $(NAME_LEMI)))

$(NAME_VISU)	:	data_visu $(OBJS_VISU)
	@$(eval OBJ_LEN=$(shell echo "$(NAME)" | wc -c))
	@$(eval CLEAN_LEN=$(shell echo "$$(tput cols)-6-$(OBJ_LEN)"|bc))
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS_VISU) $(LIBS) $(LFLAGS)
	@$(ECHO) "\r\033[38;5;040m✓ MAKE $(NAME)%.*s\033[0m\033[0m\n" $(CLEAN_LEN) $(CLEAN)
data_visu		:
	@$(eval LEN=$(shell echo $$(/bin/echo -n $(NAME_VISU) | wc -c)))
	@$(eval DELTA=$(shell echo $$(echo "$$(tput cols)-32-$(LEN)"|bc)))
	@$(eval NB=$(shell echo $(words $(SRC_VISU))))
	@$(eval INDEX=0)
	@$(eval NAME=$(shell echo $(NAME_VISU)))


$(DIROBJ)%.o	:	$(DIRSRC)%.c | $(DIROBJ)
	@$(eval DONE=$(shell echo $$(($(INDEX)*20/$(NB)))))
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB)))))
	@$(eval TO_DO=$(shell echo $$((20-$(INDEX)*20/$(NB) - 1))))
	@$(eval COLOR=$(shell list=(20 21 26 27 32 33 38 39 44 45 50 51); index=$$(($(PERCENT) * $${#list[@]} / 100)); echo "$${list[$$index]}"))
	@$(ECHO) "\r\033[38;5;%dm⌛ [%s]: %2d%% `printf '█%.0s' {0..$(DONE)}`%*s❙%*.*s\033[0m\033[0m" $(COLOR) $(NAME) $(PERCENT) $(TO_DO) "" $(DELTA) $(DELTA) "$(shell echo "$@" | sed 's/^.*\///')"
	@$(CC) $(CFLAGS) -MMD -c $< -o $@
	@$(eval OBJ_LEN=$(shell echo "$$(echo "$@" | sed 's/^.*\///')" | wc -c))
	@$(eval CLEAN_LEN=$(shell echo "$$(tput cols)-1-$(OBJ_LEN)"|bc))
	@$(ECHO) "\r\033[38;5;%dm✓ %s\033[0m\033[0m%.*s\n\033[38;5;%dm⌛ [%s]: %2d%% `printf '█%.0s' {0..$(DONE)}`%*s❙%*.*s\033[0m\033[0m"  $(COLOR) "$(shell echo "$@" | sed 's/^.*\///')"  $(CLEAN_LEN) $(CLEAN) $(COLOR) $(NAME) $(PERCENT) $(TO_DO) "" $(DELTA) $(DELTA) "$(shell echo "$@" | sed 's/^.*\///')"
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))


$(DIROBJ)		:
	@$(MAKE) $(DIRLIB)
	@mkdir -p $(DIROBJ)

clean			:
	@$(MAKE) $(DIRLIB) clean
	@if [ -e $(DIROBJ) ];											\
	then															\
		$(RM) $(DIROBJ);											\
		$(ECHO) "\033[38;5;202m✗ Objects\033[0m\033[0m\n";			\
	fi;

fclean			:	clean
	@$(MAKE) $(DIRLIB) fclean
	@if [ -e $(NAME_LEMI) ];										\
	then															\
		$(RM) $(NAME_LEMI);											\
		$(ECHO) "\033[38;5;196m✗ $(NAME_LEMI)\033[0m\033[0m\n";		\
	fi;
	@if [ -e $(NAME_VISU) ];										\
	then															\
		$(RM) $(NAME_VISU);											\
		$(ECHO) "\033[38;5;196m✗ $(NAME_VISU)\033[0m\033[0m\n";		\
	fi;

re				:	fclean all

.PHONY			:	all fclean clean re data_lemi data_visu
