
NAME = pipex

SRCS =	mandatory/childs.c 		\
		tools/ft_strlcpy.c		\
		tools/ft_split.c		\
		tools/ft_strlen.c		\
		tools/ft_strjoin.c		\
		tools/ft_strncmp.c		\
		tools/ft_memcpy.c		\
		tools/ft_strnstr.c		\

MANDATORY = mandatory/main.c	\

BONUS = bonus/main.c								\
		bonus/here_doc.c 							\
		bonus/child_process.c 						\
		bonus/get_next_line/get_next_line.c 		\
		bonus/get_next_line/get_next_line_utils.c	\

OBJS	=	${SRCS:.c=.o}

OBJMANDATORY = 	${MANDATORY:.c=.o}

OBJBONUS = 	${BONUS:.c=.o}

RM		=	rm -f

CC = cc

CFLAGS	=	-Wall -Wextra -Werror

all:		${NAME}

${NAME}:	${OBJS} ${OBJMANDATORY}
			${CC} ${OBJS} ${OBJMANDATORY} -o 	${NAME}

bonus:	${OBJS} ${OBJBONUS}
		${CC} ${CFLAGS} ${OBJS} ${OBJBONUS} -o ${NAME}

clean:
		${RM} ${OBJS} ${OBJBONUS} ${OBJMANDATORY}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		clean fclean all re