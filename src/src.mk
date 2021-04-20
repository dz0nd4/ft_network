# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    src.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/29 23:36:16 by dzonda            #+#    #+#              #
#    Updated: 2021/04/20 16:42:48 by user42           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SUBDIR = \
			network \
			traceroute \
			traceroute/display \
			traceroute/exec \
			traceroute/parser \
			nmap \

SUBFILE = \
			network/ft_network.c \
			\
			traceroute/ft_traceroute.c \
			traceroute/ft_traceroute_init.c \
			traceroute/display/ft_traceroute_packet.c \
			traceroute/display/ft_traceroute_usage.c \
			traceroute/exec/ft_traceroute_exec_receive.c \
			traceroute/exec/ft_traceroute_exec_send.c \
			traceroute/exec/ft_traceroute_exec.c \
			traceroute/parser/ft_traceroute_args.c \
			traceroute/parser/ft_traceroute_opts.c \
			traceroute/parser/ft_traceroute_parser.c \
			traceroute/ft_traceroute_errors.c \
			\
			nmap/ft_nmap.c \
