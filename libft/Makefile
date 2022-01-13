# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/10 21:08:47 by dzonda            #+#    #+#              #
#    Updated: 2022/02/11 17:15:00 by dzonda           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# 	Target																																		 #
# **************************************************************************** #

NAME = libft
VERSION = 2.3.6
EXTENSION = a
BIN = $(NAME)-$(VERSION).$(EXTENSION)

# **************************************************************************** #
# 	Directories																																 #
# **************************************************************************** #

SRCDIR = src
OBJDIR = obj

include $(SRCDIR)/src.mk 
SRCDIRS = $(foreach dir, $(SUBDIR), $(addprefix $(SRCDIR)/, $(dir)))
OBJDIRS = $(foreach dir, $(SUBDIR), $(addprefix $(OBJDIR)/, $(dir)))
INCLUDES = $(foreach dir, $(SRCDIRS), $(addprefix -I, $(dir)))

SRCS = $(foreach file, $(SUBFILE), $(addprefix $(SRCDIR)/, $(file)))
OBJS = $(subst $(SRCDIR),$(OBJDIR),$(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)

# **************************************************************************** #
# 	Config																																		 #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LN = ln -fs

MAKEFILE_NAME = Makefile-$(lastword $(subst /, ,$(NAME)))
VERBOSE = FALSE
HIDE = @
RM = rm -rf
MKDIR = mkdir -p
ERRIGNORE = 2>/dev/null

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
	$(HIDE)printf "$(MAKEFILE_NAME): "

	$(HIDE)$(3)
	$(HIDE)printf "[$(1)]"
	$(HIDE)$(COLOR_DISABLE)
	
	$(HIDE)printf " \t -> $(2) \n"
endef

# **************************************************************************** #
# 	Rules 																																		 #
# **************************************************************************** #

.PHONY: all clean fclean re

all: $(BIN)

$(BIN): $(OBJDIRS) $(OBJS)
	$(call print_step, Linking , $@ , $(COLOR_GREEN))
	$(HIDE)ar rcs $(BIN) $(OBJS)
	$(call print_step, Symlink , $(NAME).$(EXTENSION) , $(COLOR_CYAN))
	$(HIDE)$(LN) $(BIN) $(NAME).$(EXTENSION)

-include $(DEPS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(call print_step, Building , $@ , $(COLOR_YELLOW))
	$(HIDE)$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -MMD

$(OBJDIRS):
	$(call print_step, Making , $(OBJDIRS) , $(COLOR_BLUE))
	$(HIDE)$(MKDIR) $(OBJDIRS) $(ERRIGNORE)

clean:
	$(call print_step, Deleting , $(OBJDIR) , $(COLOR_RED))
	$(HIDE)$(RM) $(OBJDIR) $(ERRIGNORE)

fclean:
	$(call print_step, Deleting , $(OBJDIR) $(BIN) $(NAME).$(EXTENSION), $(COLOR_RED))
	$(HIDE)$(RM) $(OBJDIR) $(ERRIGNORE)
	$(HIDE)$(RM) $(BIN) $(ERRIGNORE)
	$(HIDE)$(RM) $(NAME).$(EXTENSION) $(ERRIGNORE)

re: fclean all
