SRCS		= main.c input.c philosophers.c routine.c one_philo.c

OBJS		= ${SRCS:.c=.o}

HEAD		= philo.h

NAME		= philo

CC			= cc

RM			= rm -f

CFLAGS		=  -Wall -Werror -Wextra 

%.o:	%.c ${HEAD}
		${CC} ${CFLAGS} -c $< -o $@

all:		${NAME}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
