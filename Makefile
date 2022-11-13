# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skhali <skhali@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/15 05:19:02 by lunovill          #+#    #+#              #
#    Updated: 2022/11/07 19:03:27 by skhali           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

 #=============================================================================#
#								SOURCES											#
 #=============================================================================#

SRCS_DIR = sources
SRC_FILES =	builtins\
				cd\
				check_char\
				echo\
				env\
				env_mangement\
				exec\
				exec_single_builtin\
				exec_utils\
				exec_utils2\
				exit\
				export\
				export_utils\
				free_minishell\
				here_docs\
				init_minishell\
				init_minishell_utils\
				lst_add\
				lst_free\
				lst_init\
				lst_new\
				lst_print\
				lst_rmv\
				lst_utils\
				main\
				pwd\
				signals\
				tk_command\
				tk_delimiter\
				tk_delimiter_utils\
				tk_delimiter_utils2\
				tk_expansion \
				tk_recognition\
				tk_split_cmd\
				unset\

				

SRCS = $(addsuffix .c, $(SRC_FILES))

 #=============================================================================#
#									OBJETS										#
 #=============================================================================#

OBJS_DIR = objets
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
DEPS = $(SRCS:%.c=$(OBJS_DIR)/%.d)

 #=============================================================================#
#									LIBRARY										#
 #=============================================================================#

LIB_DIR = libft

 #=============================================================================#
#									COMPILATION									#
 #=============================================================================#

CC = gcc
CFLAGS = -Wall -Wextra -Werror
CDFLAGS = -MMD -MP
CIFLAGS = -Iincludes -I$(LIB_DIR)/includes
CLFLAGS = -lreadline -L$(LIB_DIR) -lft

 #=============================================================================#
#									MAKEFILE									#
 #=============================================================================#

NAME = minishell

all : $(NAME)

$(NAME) : $(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(CIFLAGS) $(OBJS) $(CLFLAGS) $(MLXLFLAGS) -o $(NAME)

$(OBJS_DIR) :
	$(MAKE) -C $(LIB_DIR)
	mkdir $(OBJS_DIR)

$(OBJS) : $(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) $(CDFLAGS) $(CIFLAGS) -c $< -o $@

clean :
	$(MAKE) clean -C $(LIB_DIR)
	rm -rf $(OBJS_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIB_DIR)
	rm -rf $(NAME)

re : fclean all

-include $(DEPS)

.PHONY: all clean fclean re
