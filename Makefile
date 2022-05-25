NAME	=	minishell

INC_D	=	./includes/
PARSE_D	=	parser
BUILT_D	=	builtin
HEAD	=	${INC_D}minishell.h

CC		=	gcc
RM		=	rm -rf
FLAGS	=	-Wall -Werror -Wextra
RDL_MAC	=	-lreadline -L${HOME}/.brew/opt/readline/lib -I${HOME}/.brew/opt/readline/include

SRCS	=	${PARSE_D}/del_symbol.c \
			${PARSE_D}/free_pointerpointer.c \
			${PARSE_D}/ft_lstadd_back.c \
			${PARSE_D}/ft_lstclear.c \
			${PARSE_D}/ft_lstmap.c \
			${PARSE_D}/ft_lstnew.c \
			${PARSE_D}/ft_lstsize.c \
			${PARSE_D}/ft_memcpy.c \
			${PARSE_D}/ft_putstr_fd.c \
			${PARSE_D}/ft_split.c \
			${PARSE_D}/ft_strdup.c \
			${PARSE_D}/ft_strjoin.c \
			${PARSE_D}/ft_strlcpy.c \
			${PARSE_D}/ft_strlen.c \
			${PARSE_D}/ft_substr.c \
			${PARSE_D}/is_special_word.c \
			${PARSE_D}/parser.c \
			${PARSE_D}/path.c \
			${PARSE_D}/split_on_commands.c \
			${PARSE_D}/substitute.c \
			${PARSE_D}/syntax_split_handlers.c \
			${PARSE_D}/syntax_split.c \
			${PARSE_D}/var.c \
			${PARSE_D}/ft_itoa.c \
			${PARSE_D}/split_on_commands_utils1.c \
			${PARSE_D}/split_on_commands_utils2.c \
			\
			${BUILT_D}/export_var_ident.c \
			${BUILT_D}/ft_env.c \
			${BUILT_D}/echo.c \
			${BUILT_D}/ft_putchar_fd.c \
			${BUILT_D}/ft_putendl_fd.c \
			${BUILT_D}/ft_pwd.c \
			${BUILT_D}/ft_strncmp.c \
			${BUILT_D}/ft_atoi.c \
			${BUILT_D}/ft_cd.c \
			${BUILT_D}/ft_unset.c \
			${BUILT_D}/ft_export.c \
			${BUILT_D}/ft_unset_for_export.c \
			${BUILT_D}/check_env_name_is_valid.c \
			${BUILT_D}/builtin_caller.c \
			${BUILT_D}/exit.c \
			\
			ft_strcmp.c \
			exec.c \
			env_dup.c \
			ft_signal.c \
			main.c \
			redirects.c \
			open_file_builtin.c \

OBJS	=	${SRCS:.c=.o}

.PHONY:	all clean fclean readline

all: ${NAME}

.c.o:
	${CC} -c ${FLAGS} -I${HEAD} $< -o ${<:.c=.o}

${NAME}: ${OBJS} ${HEAD}
	${CC} -g ${RDL_MAC} -I${INC_D} ${OBJS} -o ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all
