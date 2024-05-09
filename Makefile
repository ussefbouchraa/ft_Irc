# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/07 01:27:20 by ebelfkih          #+#    #+#              #
#    Updated: 2024/05/05 18:56:25 by ybouchra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= ircserv

SRC				= main.cpp					\
				utils/helpers.cpp			\
				utils/errors.cpp			\
				classes/Server.cpp			\
				classes/Client.cpp			\
				classes/Message.cpp			\
				classes/Channel.cpp			\
				classes/Command.cpp			\
					
DIR_SRC		= src/
DIR_OBJ		= obj/
DIR_INC		= inc/
OBJ			= ${SRC:%.cpp=${DIR_OBJ}%.o}
CXX			= c++
DEP			= ${OBJ:%.o=%.d}
CPPFLAGS	= -Wall -Wextra -Werror -MMD -g3 -D_GLIBCXX_DEBUG -std=c++98 -c -I ${DIR_INC} 
RM 			= rm -f
RMDIR		= rm -rf

all: ${NAME}

${NAME} : ${OBJ}
	${CXX} $^ -o $@

${OBJ} : ${DIR_OBJ}%.o: ${DIR_SRC}%.cpp
	mkdir -p ${@D}
	${CXX} ${CPPFLAGS} $< -o $@

-include ${DEP}

clean:
	${RMDIR} ${DIR_OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re