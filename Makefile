# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/11 05:46:03 by dzonda            #+#    #+#              #
#    Updated: 2021/08/26 01:17:10 by user42           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# 	Target																																		 #
# **************************************************************************** #

NAME = ft_net

# **************************************************************************** #
# 	Directories																																 #
# **************************************************************************** #

SRCDIR = src
OBJDIR = obj
LIBDIR = libft
LIBSOCKDIR = libftsock

include $(SRCDIR)/src.mk 

SRCDIRS = $(foreach dir, $(SUBDIR), $(addprefix $(SRCDIR)/, $(dir)))
OBJDIRS = $(foreach dir, $(SUBDIR), $(addprefix $(OBJDIR)/, $(dir)))
INCLUDES = $(foreach dir, $(SRCDIRS), $(addprefix -I, $(dir)))

SRCS = $(foreach file, $(SUBFILE), $(addprefix $(SRCDIR)/, $(file)))
OBJS := $(subst $(SRCDIR),$(OBJDIR),$(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)

# **************************************************************************** #
# 	Config																																		 #
# **************************************************************************** #

CC = gcc
CFLAGS = -g3 #-Wall -Wextra -Werror -Wunused -Wunreachable-code
LDFLAGS = -Llibft
LDLIBS = -lft -lpcap -lpthread

MAKEFILE_NAME = Makefile-$(lastword $(subst /, ,$(NAME)))
VERBOSE = FALSE
HIDE = @
MAKE = make -C
RM = rm -rf
MKDIR = mkdir -p
ERRIGNORE = 2>/dev/null
SUDO = sudo
SETCAP = setcap cap_net_raw=pe

COLOR_RED = tput setaf 1
COLOR_GREEN = tput setaf 2
COLOR_YELLOW = tput setaf 3
COLOR_BLUE = tput setaf 4
COLOR_CYAN = tput setaf 6
COLOR_DISABLE = tput sgr0
BOLD_ENABLE = tput bold

ifeq ($(VERBOSE),TRUE)
	HIDE =  
endif

# **************************************************************************** #
# 	Functions 																																 #
# **************************************************************************** #

# Print step: $(1) step name, $(2) target name, $(3) color
define print_step
	$(HIDE)echo -n "$(MAKEFILE_NAME): "

	$(HIDE)$(3)
	$(HIDE)echo -n [$(1)]
	$(HIDE)$(COLOR_DISABLE)
	
	$(HIDE)echo " \t ->" $(2)
endef

# **************************************************************************** #
# 	Rules 																																		 #
# **************************************************************************** #

.PHONY: all clean fclean re lib libsock

all: lib $(NAME)

$(NAME): $(OBJDIRS) $(OBJS)
	$(call print_step, Linking , $@ , $(COLOR_GREEN))
	$(HIDE)$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	$(call print_step, Setcap , $@ , $(COLOR_GREEN))
	$(HIDE)$(SUDO) $(SETCAP) ./$(NAME)
-include $(DEPS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(call print_step, Building , $@ , $(COLOR_YELLOW))
	$(HIDE)$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -MMD

$(OBJDIRS):
	$(call print_step, Making , $(OBJDIRS) , $(COLOR_BLUE))
	$(HIDE)$(MKDIR) $(OBJDIRS) $(ERRIGNORE)

lib:
	$(HIDE)$(MAKE) $(LIBDIR)

libsock:
	$(HIDE)$(MAKE) $(LIBSOCKDIR)

clean:
	$(HIDE)$(MAKE) $(LIBDIR) clean
	$(HIDE)$(MAKE) $(LIBSOCKDIR) clean
	$(call print_step, Deleting , $(OBJDIR) , $(COLOR_RED))
	$(HIDE)$(RM) $(OBJDIR) $(ERRIGNORE)

fclean:
	$(HIDE)$(MAKE) $(LIBDIR) fclean
	$(HIDE)$(MAKE) $(LIBSOCKDIR) fclean
	$(call print_step, Deleting , $(OBJDIR) $(NAME) , $(COLOR_RED))
	$(HIDE)$(RM) $(OBJDIR) $(ERRIGNORE)
	$(HIDE)$(RM) $(NAME) $(ERRIGNORE)

re: fclean all
