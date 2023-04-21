# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: flip <marvin@42.fr>                          +#+                      #
#                                                    +#+                       #
#    Created: 2023/04/22 00:00:50 by flip          #+#    #+#                  #
#    Updated: 2023/04/22 00:07:32 by flip          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		:=	pipex
FLAGS		:= 	-Wall -Wextra -Werror
LIBFT		:= 	./libft/libft.a
HEADERS		:= 	-I ./includes -I ./libft
SRCS		:= 	main.c \

SRCDIR 		:= 	./src
OBJDIR 		:= 	./obj
OBJS		:= 	$(addprefix $(OBJDIR)/,$(SRCS:.c=.o))
SRCS		:= 	$(addprefix $(SRCDIR)/,$(SRCS))

DEBUG		:= 	-fsanitize=address

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

all: $(NAME) $(NAME_BONUS)

$(NAME): $(OBJS)
	@$(MAKE) -C libft
	@$(CC) $^ $(LIBFT) $(HEADERS) -o $(NAME)
	@echo $(Green) $(Bold) Pipex ✅ $(Text_Off)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(FLAGS) -o $@ -c $< $(HEADERS)

run:	$(NAME)

clean:
	@rm -rf $(OBJDIR) $(OBJDIR_BONUS)
	@$(MAKE) -C libft clean
	@echo $(Yellow) Cleaned object files! $(Text_Off)

fclean:	clean
	@rm -f $(NAME) $(NAME_BONUS) $(LIBFT)
	@$(MAKE) -C libft fclean
	@echo $(Yellow) Cleaned executable(s)! $(Text_Off)

re:	fclean all

.PHONY:	all, clean, fclean, re
