# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    src.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/29 23:36:16 by dzonda            #+#    #+#              #
#    Updated: 2021/04/26 11:58:05 by user42           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SUBDIR = \
			network \
			traceroute \
			traceroute/display \
			traceroute/errors \
			traceroute/parser \
			traceroute/socket \
			nmap \

SUBFILE = \
			network/ft_network.c \
			\
			traceroute/ft_traceroute.c \
			traceroute/ft_traceroute_exec.c \
			traceroute/display/ft_traceroute_packet.c \
			traceroute/display/ft_traceroute_usage.c \
			traceroute/errors/ft_traceroute_errors_args.c \
			traceroute/errors/ft_traceroute_errors_opts.c \
			traceroute/errors/ft_traceroute_errors.c \
			traceroute/parser/ft_traceroute_args.c \
			traceroute/parser/ft_traceroute_opts.c \
			traceroute/parser/ft_traceroute_parser.c \
			traceroute/socket/ft_traceroute_socket_packet.c \
			traceroute/socket/ft_traceroute_socket_receive.c \
			traceroute/socket/ft_traceroute_socket_send.c \
			\
			nmap/ft_nmap.c \
