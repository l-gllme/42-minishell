# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lguillau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/14 14:27:36 by lguillau          #+#    #+#              #
#    Updated: 2022/03/16 14:42:03 by lguillau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES	=	minishell.c \
		tools/tools.c \
		tools/split.c \
		tools/str_tools.c \
		tools/errors.c \
		gnl/get_next_line.c \
		gnl/get_next_line_utils.c \
		builtins/pwd.c \
		builtins/exit.c \

S_PATH	=	srcs/
O_PATH	=	objs/
I_PATH	=	includes/

SRCS	=	${addprefix ${S_PATH}, ${FILES}}
OBJS	=	${addprefix ${O_PATH}, ${FILES:.c=.o}}

NAME	=	minishell

CC	=	clang

RM	=	rm -rf

CFLAGS	=	-Wall -Wextra -Werror

${O_PATH}%.o:	${S_PATH}%.c
		@mkdir -p ${dir $@}
		@${CC} ${CFLAGS} -c $< -o $@ -I ${I_PATH}
		@echo "${YELLOW}Compiling${S} ${IGREY}$<${S} \033[1;33m->${S} ${SBLUE}$@${S}"

${NAME}:	${OBJS}
		@${CC} ${OBJS} ${CFLAGS} -o ${NAME} -lreadline -I ${I_PATH}
		@echo ""
		@echo "${CYAN}Building${S} ${IGREY}$@${S}"
		@echo ""
		@echo "\033[3;32mCompilation is completed !${S}"

all:		${NAME}

clean:
		@${RM} ${O_PATH}
		@echo "${RED}Removing${S} ${IGREY}${O_PATH}${S}"

fclean:		clean
		@${RM} ${NAME}
		@echo "${RED}Removing${S} ${IGREY}${NAME}${S}"

space:
		@echo ""

re:		fclean space  all

.PHONY:		all clean fclean re bonus

S	=	\033[0m
BOLD	=	\033[1m
UNDER	=	\033[4m
REV	=	\033[7m

# Colors
GREY	=	\033[30m
RED	=	\033[31m
GREEN	=	\033[32m
YELLOW	=	\033[33m
BLUE	=	\033[34m
PURPLE	=	\033[35m
CYAN	=	\033[36m
WHITE	=	\033[37m

SGREY	=	\033[90m
SRED	=	\033[91m
SGREEN	=	\033[92m
SYELLOW	=	\033[93m
SBLUE	=	\033[94m
SPURPLE	=	\033[95m
SCYAN	=	\033[96m
SWHITE	=	\033[97m

# Colored backgrounds
IGREY	=	\033[40m
IRED	=	\033[41m
IGREEN	=	\033[42m
IYELLOW	=	\033[43m
IBLUE	=	\033[44m
IPURPLE	=	\033[45m
ICYAN	=	\033[46m
IWHITE	=	\033[47m
