# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fvan-wij <marvin@42.fr>                      +#+                      #
#                                                    +#+                       #
#    Created: 2023/05/09 11:06:08 by fvan-wij      #+#    #+#                  #
#    Updated: 2023/05/09 12:00:13 by fvan-wij      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		:=	memory_metrics.a
FLAGS		:= 	-Wall -Wextra -Werror
HEADERS		:= 	-I ./includes
SRCS		:= 	memory_metrics.c \

SRCDIR 		:= 	./src
OBJDIR 		:= 	./obj
OBJS		:= 	$(addprefix $(OBJDIR)/,$(SRCS:.c=.o))
SRCS		:= 	$(addprefix $(SRCDIR)/,$(SRCS))

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

all: $(NAME)

$(NAME): $(OBJS)
	@ar -rcs $(NAME) $(OBJS)
	@echo $(Green) $(Bold) Memory_metrics compiled succesfully ✅ $(Text_Off)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(FLAGS) -o $@ -c $< $(HEADERS)

run:	all

clean:
	@rm -rf $(OBJDIR)
	@echo $(Yellow) Memory_metrics cleaned object files! $(Text_Off)

fclean:	clean
	@rm -f $(NAME)
	@echo $(Yellow) Memory_metrics cleaned archive! $(Text_Off)

re:	fclean all

.PHONY:	all, clean, fclean, re
