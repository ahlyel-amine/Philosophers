SRC				= src/philo.c src/forks.c src/init_data.c src/tools.c src/libc_tools.c
SRC_BONUS		= bonus/src_bonus/philo_bonus.c bonus/src_bonus/forks_bonus.c bonus/src_bonus/init_data_bonus.c bonus/src_bonus/tools_bonus.c bonus/src_bonus/libc_tools_bonus.c
HEADERS			= include/philo.h
HEADERS_BONUS	= bonus/include_bonus/philo_bonus.h
CC				= cc
OBJ				=  $(patsubst %.c, obj/%.o , $(SRC))
OBJ_BONUS		=  $(patsubst %.c, obj_bonus/%.o , $(SRC_BONUS))
NC				= '\e[0m'
HBLU			= '\e[1;94m'
OBJ_DIR 		= obj
OBJ_DIR_BONUS	= obj_bonus
CFLAGS			= -Wall -Wextra -Werror
NAME			= philo
NAME_BONUS		= philo_bonus

all : ${NAME}

${NAME} : ${OBJ}
	cc ${CFLAGS} ${OBJ} -o ${NAME}

obj/%.o : %.c $(HEADERS)
	mkdir -p $(dir $@)
	printf ${HBLU}"[%-37s] 🕝 \r"$(NC) "Compiling $(notdir $@)"
	$(CC) $(CFLAGS) -c $< -o $@

bonus : ${NAME_BONUS}

${NAME_BONUS}: ${OBJ_BONUS}
	cc ${CFLAGS} ${OBJ_BONUS} -o ${NAME_BONUS}

obj_bonus/%.o : %.c $(HEADERS_BONUS)
	mkdir -p $(dir $@)
	printf ${HBLU}"[%-37s] 🕝 \r"$(NC) "Compiling $(notdir $@)"
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf ${OBJ_DIR} ${OBJ_DIR_BONUS}

fclean : clean
	rm -rf ${NAME}
	rm -rf ${NAME_BONUS}

re : fclean all

.PHONY : all re fclean clean bonus
.SILENT : all re fclean clean ${OBJ} ${NAME} ${OBJ_BONUS} ${NAME_BONUS}