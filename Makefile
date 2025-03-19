.PHONY: all clean fclean re f fclear c clear lib

NAME			=		philo
CC				=		cc
CFLAGS			=		-Wall -Wextra -Werror -MMD -MP -g3 -pthread
CFLAGSS			=		-Weverything -Wno-padded
NPD				=		--no-print-directory
MAKE			:=		$(MAKE) -j $(NPD)
RM				=		rm -fr
AR				=		ar -rcs


# Color
GREEN			=		\033[0;32m
BLUE			=		\033[0;34m
RED				=		\033[0;31m
YELLOW			=		\033[0;33m
RESET			=		\033[0m


#############################################################################################
#																							#
#										// Directories										#
#																							#
#############################################################################################


# Directories
D_SRC			=		src/
D_OBJ			=		1object/
D_INC			=		inc/

# Source Directories
D_UTILIS		=		utils/

#############################################################################################
#																							#
#										// SOURCE											#
#																							#
#############################################################################################


INC				=		ft_philo.h

SRC				=		main.c					\
						ft_diogenes_of_sinope.c	\
						ft_sim.c				\
						ft_state.c

SRC_UTILS		=		ft_clear.c			\
						ft_init.c			\
						ft_param.c			\
						ft_print_status.c	\
						ft_sim_utils.c		\
						ft_time.c


#############################################################################################
#																							#
#										// OBJECT											#
#																							#
#############################################################################################


# All src in his Src Directories
SRCS			=		$(addprefix $(D_SRC), $(SRC))						\
						$(addprefix $(D_SRC)$(D_UTILIS), $(SRC_UTILS))


# Changing all source directories to object directories
OBJS			=		$(subst $(D_SRC), $(D_OBJ), $(SRCS:.c=.o))
D_OBJS			=		$(subst $(D_SRC), $(D_OBJ), $(SRCS))
DEPS			=		$(SRCS:%.c=%.d)

INCS			=		$(addprefix $(D_INC), $(INC))



#############################################################################################
#																							#
#										// COMPILATION										#
#																							#
#############################################################################################


all				:
			$(MAKE) $(NAME)
			$(MAKE) $(D_OBJ)

$(NAME)			:	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(D_OBJ)%.o		:	$(D_SRC)%.c $(INCS) Makefile
			@mkdir -p $(dir $@)
			$(CC) $(CFLAGS) -c $< -o $@ -I $(D_INC)


#############################################################################################
#																							#
#								    // CLEAN  FCLEAN  RE									#
#																							#
#############################################################################################


clean 			:
			$(RM) $(D_OBJ)


fclean 			:
			$(RM) $(NAME)
			$(RM) $(D_OBJ)


re 				:	 fclean all


#############################################################################################
#																							#
#										Allias												#
#																							#
#############################################################################################


c				:	clear
clear			:	clean

f				:	fclean
fclear			:	fclean

 -include $(DEPS)
