SUBDIRS_PING = \
			ping \
			ping/execute \
			ping/options \
			ping/socket

SUBFILES_PING = \
			ping/ft_ping.c \
			ping/ft_ping_errors.c \
			\
			ping/execute/ft_ping_exec.c \
			ping/execute/ft_ping_exec_send.c \
			ping/execute/ft_ping_exec_recv.c \
			ping/execute/ft_ping_exec_print.c \
			ping/execute/ft_ping_exec_signal.c \
			\
			ping/options/ft_ping_opts.c \
			ping/options/ft_ping_opts_parse.c \
			\
			ping/socket/ft_sock_recv.c \
			ping/socket/ft_sock_to.c \
			ping/socket/ft_sock_tools.c