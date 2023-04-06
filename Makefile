
NAME = pipex

SRCS =	mandatory/main.c 		\
		mandatory/childs.c 		\
	 	tools/ft_strlcpy.c		\
		tools/ft_split.c		\
		tools/ft_strlen.c		\
		tools/ft_strjoin.c		\
		tools/ft_strncmp.c		\
		tools/ft_memcpy.c		\
		tools/ft_strnstr.c

OBJS	=	${SRCS:.c=.o}

RM		=	rm -f

CC = cc

CFLAGS	=	-Wall -Wextra -Werror

all:		${NAME}

${NAME}:	${OBJS}
			${CC}  ${OBJS} -o  ${NAME}

clean:
		${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		clean fclean all re