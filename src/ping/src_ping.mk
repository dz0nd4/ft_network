SUBDIRS_PING = \
			ping \
			ping/execute \
			ping/options \
			ping/socket \
			ping/errors

SUBFILES_PING = \
			ping/ft_ping.c \
			\
			ping/execute/ft_ping_exec.c \
			ping/execute/ft_ping_exec_send.c \
			ping/execute/ft_ping_exec_recv.c \
			ping/execute/ft_ping_exec_print.c \
			ping/execute/ft_ping_exec_signal.c \
			ping/execute/ft_ping_exec_stats.c \
			\
			ping/options/ft_ping_opts.c \
			ping/options/ft_ping_opts_parse.c \
			\
			ping/socket/ft_sock_recv.c \
			ping/socket/ft_sock_to.c \
			ping/socket/ft_sock_tools.c \
			\
			ping/errors/ft_ping_err_exec.c \
			ping/errors/ft_ping_err_opts.c \
			ping/errors/ft_ping_err_usage.c

