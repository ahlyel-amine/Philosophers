SRC				= src_bonus/philo_bonus.c src_bonus/forks_bonus.c src_bonus/init_data_bonus.c src_bonus/tools_bonus.c src_bonus/libc_tools_bonus.c
HEADERS			= include_bonus/philo_bonus.h
CC				= cc
OBJ				= $(patsubst %.c, obj_bonus/%.o , $(SRC))
NC				= '\e[0m'
HBLU			= '\e[1;94m'
OBJ_DIR 		= obj_bonus
CFLAGS			= -Wall -Wextra -Werror
NAME			= philo_bonus

all : ${NAME}

${NAME} : ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -o ${NAME}

obj_bonus/%.o : %.c $(HEADERS)
	mkdir -p $(dir $@)
	printf ${HBLU}"[%-37s] 🕝 \r"$(NC) "Compiling $(notdir $@)"
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf ${OBJ_DIR}

fclean : clean
	rm -rf ${NAME}

re : fclean all

.PHONY : all re fclean clean bonus
.SILENT : all re fclean clean ${OBJ}  ${NAME}