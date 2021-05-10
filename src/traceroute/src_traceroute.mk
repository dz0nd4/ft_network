SUBDIRS_TRACEROUTE = \
			traceroute \
			traceroute/display \
			traceroute/errors \
			traceroute/parse \
			traceroute/socket \
			traceroute/execute

SUBFILES_TRACEROUTE = \
			traceroute/ft_traceroute.c \
			\
			traceroute/errors/ft_traceroute_errors_args.c \
			traceroute/errors/ft_traceroute_errors_opts.c \
			traceroute/errors/ft_traceroute_errors.c \
			\
			traceroute/execute/ft_traceroute_execute_init.c \
			traceroute/execute/ft_traceroute_execute_recv.c \
			traceroute/execute/ft_traceroute_execute_send.c \
			traceroute/execute/ft_traceroute_execute.c \
			\
			traceroute/parse/ft_traceroute_parse_args.c \
			traceroute/parse/ft_traceroute_parse_opts.c \
			traceroute/parse/ft_traceroute_parse.c \
			\
			traceroute/socket/ft_traceroute_socket_tools.c