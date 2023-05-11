# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: flip <marvin@42.fr>                          +#+                      #
#                                                    +#+                       #
#    Created: 2023/04/22 00:00:50 by flip          #+#    #+#                  #
#    Updated: 2023/05/11 19:51:50 by flip          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		:=	pipex
FLAGS		:= 	-Wall -Wextra -Werror
LIBFT		:= 	./libft/libft.a
# MEM_METRICS	:=	./memory_metrics/memory_metrics.a
HEADERS		:= 	-I ./includes -I ./libft
SRCS		:= 	main.c \
				pipex_parsing.c \
				pipex_execution.c \
				pipex_processes.c \
				pipex_pipes.c \
				pipex_utilities.c \
				pipex_error_handling.c \

SRCDIR 		:= 	./src
OBJDIR 		:= 	./obj
OBJS		:= 	$(addprefix $(OBJDIR)/,$(SRCS:.c=.o))
SRCS		:= 	$(addprefix $(SRCDIR)/,$(SRCS))

# DEBUG		:=
# Colors #############################################
Black		= "\033[0;30m"		# Black
Red			= "\033[0;31m"		# Red
Green		= "\033[0;32m"		# Green
Yellow		= "\033[0;33m"		# Yellow
Blue		= "\033[0;34m"		# Blue
Purple		= "\033[0;35m"		# Purple
Cyan		= "\033[0;36m"		# Cyan
White		= "\033[0;37m"		# White
Text_Off	= "\033[0m"			# Text Style Off
Bold		= "\033[1m"			# Text Style Bold
######################################################

ifdef DEBUG
	CC += -g -fsanitize=address
endif

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C libft
	@$(MAKE) -C memory_metrics
	@$(CC) $^ $(LIBFT) $(MEM_METRICS) $(HEADERS) -o $(NAME)
	@echo $(Green) $(Bold) Pipex compiled succesfully ✅ $(Text_Off)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(FLAGS) -o $@ -c $< $(HEADERS)

run:	all

clean:
	@rm -rf $(OBJDIR)
	@echo $(Yellow) Pipex: cleaned object files! $(Text_Off)
	@$(MAKE) -C libft clean
	@$(MAKE) -C memory_metrics clean

fclean:	clean
	@rm -f $(NAME) $(LIBFT) $(MEM_METRICS)
	@echo $(Yellow) Pipex: cleaned executable! $(Text_Off)
	@$(MAKE) -C libft fclean
	@$(MAKE) -C memory_metrics fclean

re:	fclean all

.PHONY:	all, clean, fclean, re
