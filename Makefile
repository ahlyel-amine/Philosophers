

SRC =	\
		src/philo.c 

HEADERS = include/philo.h lib/libft/include/libft.h

CC = cc

OBJ_DIR = obj

OBJ =  $(patsubst %.c, obj/%.o , $(SRC))

NC			= '\e[0m'
HBLU		= '\e[1;94m'
BIN_DIR		= bin/
CFLAGS		= -Wall -Wextra -Werror -fsanitize=thread
NAME		= philo

all : ${NAME}

${NAME} : ${OBJ}
	make -C lib/libft
	cc -g ${CFLAGS} ${OBJ} lib/libft/bin/libft.a -o ${NAME}

obj/%.o : %.c $(HEADERS)
	mkdir -p $(dir $@)
	printf ${HBLU}"[%-37s] 🕝 \r"$(NC) "Compiling $(notdir $@)"
	$(CC) -g $(CFLAGS) -c $< -o $@

clean : 
	make clean -C lib/libft
	rm -rf ${OBJ_DIR}

fclean : clean
	make fclean -C lib/libft
	rm -rf ${NAME} ${BIN_DIR}

re : fclean all

.PHONY : all re fclean clean 
.SILENT : all re fclean clean ${OBJ} ${NAME}