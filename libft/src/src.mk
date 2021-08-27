# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    src.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/12 20:14:40 by dzonda            #+#    #+#              #
#    Updated: 2021/07/25 11:25:52 by user42           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

include src/bits/src_bits.mk
include src/gnl/src_gnl.mk
include src/is/src_is.mk
include src/math/src_math.mk
include src/mem/src_mem.mk
include src/put/src_put.mk
include src/str/src_str.mk
include src/to/src_to.mk

SUBDIR = \
			${SUBDIRS_BITS} \
			${SUBDIRS_GNL} \
			${SUBDIRS_IS} \
			${SUBDIRS_STR} \
			${SUBDIRS_PUT} \
			${SUBDIRS_MATH} \
			${SUBDIRS_MEM} \
			${SUBDIRS_TO}

SUBFILE = \
			${SUBFILES_BITS} \
			${SUBFILES_GNL} \
			${SUBFILES_IS} \
			${SUBFILES_STR} \
			${SUBFILES_PUT} \
			${SUBFILES_MATH} \
			${SUBFILES_MEM} \
			${SUBFILES_TO}