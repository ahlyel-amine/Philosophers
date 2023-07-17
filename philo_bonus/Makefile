SRC =	\
		src_bonus/philo_bonus.c src_bonus/forks_bonus.c src_bonus/init_data_bonus.c src_bonus/tools_bonus.c src_bonus/libc_tools_bonus.c

HEADERS = include_bonus/philo_bonus.h
# Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo Hallo
CC = gcc

OBJ_DIR = obj_bonus

OBJ =  $(patsubst %.c, obj_bonus/%.o , $(SRC))

NC			= '\e[0m'
HBLU		= '\e[1;94m'
BIN_DIR		= bin_bonus/
CFLAGS		=  # -fsanitize=thread
NAME		= philo_bonus

all : ${NAME}

${NAME} : ${OBJ}
	cc -g ${CFLAGS} ${OBJ} -o ${NAME}

obj_bonus/%.o : %.c $(HEADERS)
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