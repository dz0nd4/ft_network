# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/10 21:08:47 by dzonda            #+#    #+#              #
#    Updated: 2021/05/10 17:10:18 by user42           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #


NAME = libft.a
SRCDIR = src
OBJDIR = obj

MAKEFILE_NAME = Makefile-$(lastword $(subst /, ,$(NAME)))

CC = gcc
CFLAGS = -Wall -Wextra -Werror
SUBDIR = \
			bits \
			gnl \
			is \
			lst \
			mem \
			put \
			str \
			to

SUBFILE = \
			bits/ft_align_bits.c \
			bits/ft_rotate.c \
			bits/ft_shift.c \
			bits/ft_swap.c \
			gnl/ft_get_input.c \
			gnl/get_next_line.c \
			put/putchar_fd.c \
			put/putnbr.c \
			put/puthexapad_fd.c \
			put/putstrpad_fd.c \
			put/putendlpad_fd.c \
			put/putendl.c \
			put/putchar.c \
			put/putstr.c \
			put/putendlpad.c \
			put/putnbrendl.c \
			put/puthexa_fd.c \
			put/putnbr_fd.c \
			put/putstrpad.c \
			put/puthexa.c \
			put/puthexapad.c \
			put/putnbrendl_fd.c \
			put/putendl_fd.c \
			put/putstr_fd.c \
			is/isdigit.c \
			is/isblank.c \
			is/isascii.c \
			is/isprint.c \
			is/isalpha.c \
			is/islower.c \
			is/isupper.c \
			is/isspace.c \
			is/isalnum.c \
			is/isdir.c \
			is/isreg.c \
			is/ft_isdigitstr.c \
			lst/lstdelone.c \
			lst/lstmap.c \
			lst/lstadd.c \
			lst/lstiter.c \
			lst/lstnew.c \
			lst/lstdel.c \
			str/strchr.c \
			str/strncat.c \
			str/strclr.c \
			str/strnstr.c \
			str/strdel.c \
			str/strstr.c \
			str/strcat.c \
			str/strequ.c \
			str/stradup.c \
			str/strjoin.c \
			str/strsplit.c \
			str/striteri.c \
			str/wordlen.c \
			str/strnequ.c \
			str/strlen.c \
			str/strrev.c \
			str/strncmp.c \
			str/strdup.c \
			str/strrchr.c \
			str/strnew.c \
			str/strcmp.c \
			str/strmapi.c \
			str/stralen.c \
			str/strtrim.c \
			str/strsub.c \
			str/wordcount.c \
			str/bzero.c \
			str/strcpy.c \
			str/strmap.c \
			str/strlcat.c \
			str/strncpy.c \
			str/stradel.c \
			str/striter.c \
			str/strequal.c \
			to/atoi.c \
			to/itoa.c \
			to/nbrlen.c \
			to/toupper.c \
			to/tolower.c \
			mem/memcpy.c \
			mem/memcmp.c \
			mem/memalloc.c \
			mem/memccpy.c \
			mem/memmove.c \
			mem/memrev.c \
			mem/memset.c \
			mem/memchr.c \
			mem/memdel.c

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

.PHONY: all clean fclean re 

all: $(NAME)

$(NAME): $(OBJDIRS) $(OBJS)
	$(HIDE)echo $(MAKEFILE_NAME): "Linking \t ->" $@
	$(HIDE)ar rcs $(NAME) $(OBJS)

-include $(DEPS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo $(MAKEFILE_NAME): "Building \t ->" $@
	$(HIDE)$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -MMD

$(OBJDIRS):
	@echo $(MAKEFILE_NAME): "Making \t ->" $(OBJDIRS)
	$(HIDE)$(MKDIR) $(OBJDIRS) $(ERRIGNORE)

clean:
	$(HIDE)$(RM) $(OBJDIR) $(ERRIGNORE)
	@echo $(MAKEFILE_NAME): Clean done !

fclean:
	$(HIDE)$(RM) $(OBJDIR) $(ERRIGNORE)
	$(HIDE)$(RM) $(NAME) $(ERRIGNORE)
	@echo $(MAKEFILE_NAME): Fclean done !

re: fclean all
