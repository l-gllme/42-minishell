# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lguillau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/14 14:27:36 by lguillau          #+#    #+#              #
#    Updated: 2022/05/25 12:42:46 by jtaravel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES	=	minishell.c \
		tools/split.c \
		tools/supersplit.c \
		tools/ft_split_by_string.c \
		tools/tools.c \
		tools/str_tools.c \
		tools/ft_itoa.c \
		tools/str_tools_2.c \
		tools/str_tools_3.c \
		tools/errors.c \
		tools/ft_strcpy.c \
		builtins/cd.c \
		builtins/cd_2.c \
		builtins/export.c \
		builtins/export_1.c \
		builtins/export_2.c \
		builtins/export_3.c \
		builtins/export_4.c \
		builtins/pwd.c \
		builtins/exit.c \
		builtins/env.c \
		builtins/echo.c \
		builtins/unset.c \
		parsing/parsing.c \
		parsing/stock_line.c \
		parsing/in_out_parse.c \
		parsing/check_syntax.c \
		parsing/parsing_tools.c \
		parsing/parsing_tools_2.c \
		parsing/get_cmd.c \
		parsing/parse_cmd.c \
		parsing/check_in_env.c \
		parsing/check_in_env_2.c \
		parsing/check_in_env_1.c \
		parsing/check_in_env_tools.c \
		parsing/check_in_env_tools_2.c \
		parsing/check_in_env_tools_3.c \
		parsing/check_in_env_2_2.c \
		exec/ft_exec.c \
		exec/ft_exec_2.c \
		exec/ft_exec_pipes.c \
		exec/ft_exec_pipes_2.c \
		exec/ft_exec_pipes_3.c \
		exec/ft_exec_one.c \
		exec/ft_exec_one_2.c \
		exec/ft_exec_in.c \
		exec/ft_exec_in_2.c \
		exec/ft_exec_out.c \
		exec/ft_is_builtin.c \
		exec/check_outfile.c \
		exec/ft_here_doc.c \
		exec/ft_here_doc_2.c \
		lst/ft_lst.c \
		lst/ft_superlst.c \
		lst/ft_superlst_2.c \
		lst/ft_lst_2.c \
		gnl/get_next_line.c \
		gnl/get_next_line_utils.c \
		env/env_lst.c \
		env/env_lst_2.c \

S_PATH	=	srcs/
O_PATH	=	objs/
I_PATH	=	includes/

SRCS	=	${addprefix ${S_PATH}, ${FILES}}
OBJS	=	${addprefix ${O_PATH}, ${FILES:.c=.o}}

NAME	=	minishell

CC	=	clang

RM	=	rm -rf

CFLAGS	=	-Wall -Wextra -Werror -g3

${O_PATH}%.o:	${S_PATH}%.c
		@mkdir -p ${dir $@}
		@${CC} ${CFLAGS} -c $< -o $@ -I ${I_PATH}
		@echo "${CYAN}Compiling${S} ${IGREY}$<${S} ${YELLOW}➡️  ${S}${SBLUE}$@${S}"

${NAME}:	${OBJS}
		@${CC} ${OBJS} ${CFLAGS} -o ${NAME} -lreadline -I ${I_PATH}
		@echo "${PURPLE}\n███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗\n████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║\n██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║\n██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║\n██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n${S}"
		@echo ""
		@echo "${PURPLE}Building${S} ${IGREY}$@${S} 🔨"
		@echo ""
		@echo "\033[3;92mCompilation is completed !${S} 🎉"

all:		${NAME}

clean:
		@${RM} ${O_PATH}
		@echo "${SRED}Removing${S} ${IGREY}${O_PATH}${S} 🗑️"

fclean:		clean
		@${RM} ${NAME}
		@echo "${SRED}Removing${S} ${IGREY}${NAME}${S} 🗑️"

space:
		@echo ""

re:		fclean space  all

.PHONY:		all clean fclean re bonus

S	=	\033[0m
BOLD	=	\033[1m
ITALIC	=	\033[3m
UNDER	=	\033[4m
TEST	=	\033[5m
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
