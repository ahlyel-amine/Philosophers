SRC				= src/philo.c src/forks.c src/init_data.c src/tools.c src/libc_tools.c
HEADERS			= include/philo.h
CC				= cc
OBJ				=  $(patsubst %.c, obj/%.o , $(SRC))
NC				= '\e[0m'
HBLU			= '\e[1;94m'
OBJ_DIR 		= obj
CFLAGS			= -Wall -Wextra -Werror
#  -fsanitize=thread
NAME			= philo

all : ${NAME}

${NAME} : ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -o ${NAME}

obj/%.o : %.c $(HEADERS) Makefile
	mkdir -p $(dir $@)
	printf ${HBLU}"[%-37s] 🕝 \r"$(NC) "Compiling $(notdir $@)"
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf ${OBJ_DIR}

fclean : clean
	rm -rf ${NAME}

re : fclean all

.PHONY : all re fclean clean
.SILENT : all re fclean clean ${OBJ} ${NAME}