

SRC =	\
		src/philo.c src/forks.c src/init_data.c src/tools.c src/libft_tools.c

HEADERS = include/philo.h
# Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo
CC = cc

OBJ_DIR = obj

OBJ =  $(patsubst %.c, obj/%.o , $(SRC))

NC			= '\e[0m'
HBLU		= '\e[1;94m'
BIN_DIR		= bin/
CFLAGS		= -Wall -Wextra -Werror
#   -fsanitize=thread
NAME		= philo

all : ${NAME}

${NAME} : ${OBJ}
	cc -g ${CFLAGS} ${OBJ} -o ${NAME}

obj/%.o : %.c $(HEADERS)
	mkdir -p $(dir $@)
	printf ${HBLU}"[%-37s] 🕝 \r"$(NC) "Compiling $(notdir $@)"
	$(CC) -g $(CFLAGS) -c $< -o $@

clean : 
	rm -rf ${OBJ_DIR}

fclean : clean
	rm -rf ${NAME} ${BIN_DIR}

re : fclean all

.PHONY : all re fclean clean 
.SILENT : all re fclean clean ${OBJ} ${NAME}