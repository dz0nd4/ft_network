# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    src.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/12 20:14:40 by dzonda            #+#    #+#              #
#    Updated: 2021/05/18 23:55:35 by dzonda           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

include src/gnl/src_gnl.mk
include src/is/src_is.mk
include src/lst/src_lst.mk
include src/mem/src_mem.mk
include src/put/src_put.mk
include src/str/src_str.mk
include src/to/src_to.mk

SUBDIR = \
			${SUBDIRS_GNL} \
			${SUBDIRS_IS} \
			${SUBDIRS_LST} \
			${SUBDIRS_STR} \
			${SUBDIRS_PUT} \
			${SUBDIRS_MEM} \
			${SUBDIRS_TO}

SUBFILE = \
			${SUBFILES_GNL} \
			${SUBFILES_IS} \
			${SUBFILES_LST} \
			${SUBFILES_STR} \
			${SUBFILES_PUT} \
			${SUBFILES_MEM} \
			${SUBFILES_TO}