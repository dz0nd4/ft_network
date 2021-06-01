SUBDIRS_TRACEROUTE = \
			traceroute \
			traceroute/parse \
			traceroute/execute

SUBFILES_TRACEROUTE = \
			traceroute/ft_traceroute.c \
			\
			traceroute/parse/ft_traceroute_parse.c \
			traceroute/parse/ft_traceroute_parse_options.c \
			traceroute/parse/ft_traceroute_parse_arguments.c \
			traceroute/parse/ft_traceroute_parse_errors.c \
			\
			traceroute/execute/ft_traceroute_exec.c \
			traceroute/execute/ft_traceroute_exec_init.c \
			traceroute/execute/ft_traceroute_exec_send.c \
			traceroute/execute/ft_traceroute_exec_recv.c \
			traceroute/execute/ft_traceroute_exec_pckt.c \
			traceroute/execute/ft_traceroute_exec_finish.c