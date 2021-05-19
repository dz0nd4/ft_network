# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/10 21:08:47 by dzonda            #+#    #+#              #
#    Updated: 2021/05/19 15:09:01 by user42           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #


NAME = libft
VERSION = 2.1
EXTENSION = a

MAKEFILE_NAME = Makefile-$(lastword $(subst /, ,$(NAME)))

BIN = $(NAME)-$(VERSION).$(EXTENSION)
SRCDIR = src
OBJDIR = obj

CC = gcc
CFLAGS = -Wall -Wextra -Werror

include $(SRCDIR)/src.mk 

SRCDIRS = $(foreach dir, $(SUBDIR), $(addprefix $(SRCDIR)/, $(dir)))
OBJDIRS = $(foreach dir, $(SUBDIR), $(addprefix $(OBJDIR)/, $(dir)))
INCLUDES = $(foreach dir, $(SRCDIRS), $(addprefix -I, $(dir)))

SRCS = $(foreach file, $(SUBFILE), $(addprefix $(SRCDIR)/, $(file)))
OBJS = $(subst $(SRCDIR),$(OBJDIR),$(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)

VERBOSE = FALSE
ifeq ($(VERBOSE),TRUE)
	HIDE =  
else
	HIDE = @
endif
RM = rm -rf
MKDIR = mkdir -p
ERRIGNORE = 2>/dev/null
LN = ln -fs

.PHONY: all clean fclean re 

all: $(NAME)

$(NAME): $(OBJDIRS) $(OBJS)
	$(HIDE)echo $(MAKEFILE_NAME): [Linking] $@
	$(HIDE)ar rcs $(BIN) $(OBJS)
	$(HIDE)$(LN) $(BIN) $(NAME).$(EXTENSION)

-include $(DEPS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo $(MAKEFILE_NAME): [Building] $@
	$(HIDE)$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -MMD

$(OBJDIRS):
	@echo $(MAKEFILE_NAME): Making $(OBJDIRS)
	$(HIDE)$(MKDIR) $(OBJDIRS) $(ERRIGNORE)

clean:
	@echo $(MAKEFILE_NAME): Deleting $(OBJDIR)
	$(HIDE)$(RM) $(OBJDIR) $(ERRIGNORE)
	@echo $(MAKEFILE_NAME): Clean done !

fclean:
	@echo $(MAKEFILE_NAME): Deleting $(BIN) $(OBJDIR)
	$(HIDE)$(RM) $(OBJDIR) $(ERRIGNORE)
	$(HIDE)$(RM) $(BIN) $(ERRIGNORE)
	$(HIDE)$(RM) $(NAME).$(EXTENSION) $(ERRIGNORE)
	@echo $(MAKEFILE_NAME): Fclean done !

re: fclean all
