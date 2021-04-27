# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    src.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/29 23:36:16 by dzonda            #+#    #+#              #
#    Updated: 2021/04/27 13:00:25 by user42           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SUBDIR = \
			network \
			traceroute \
			traceroute/display \
			traceroute/errors \
			traceroute/parse \
			traceroute/socket \
			nmap \

SUBFILE = \
			network/ft_network.c \
			\
			traceroute/ft_traceroute.c \
			traceroute/ft_traceroute_parse.c \
			traceroute/ft_traceroute_execute.c \
			traceroute/display/ft_traceroute_display_infos.c \
			traceroute/display/ft_traceroute_display_packet.c \
			traceroute/display/ft_traceroute_display_usage.c \
			traceroute/errors/ft_traceroute_errors_args.c \
			traceroute/errors/ft_traceroute_errors_opts.c \
			traceroute/errors/ft_traceroute_errors.c \
			traceroute/parse/ft_traceroute_parse_args.c \
			traceroute/parse/ft_traceroute_parse_opts.c \
			traceroute/socket/ft_traceroute_socket_packet.c \
			traceroute/socket/ft_traceroute_socket_receive.c \
			traceroute/socket/ft_traceroute_socket_send.c \
			\
			nmap/ft_nmap.c \
