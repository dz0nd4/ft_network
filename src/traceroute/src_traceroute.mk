SUBDIRS_TRACEROUTE = \
			traceroute \
			traceroute/parse \
			traceroute/execute

SUBFILES_TRACEROUTE = \
			traceroute/ft_traceroute.c \
			\
			traceroute/parse/ft_trace_parse.c \
			traceroute/parse/ft_trace_opts.c \
			traceroute/parse/ft_trace_args.c \
			\
			traceroute/execute/ft_trace_exec.c \
			traceroute/execute/ft_trace_exec_init.c \
			traceroute/execute/ft_trace_exec_send.c \
			traceroute/execute/ft_trace_exec_recv.c \
			traceroute/execute/ft_trace_exec_pckt.c \
			traceroute/execute/ft_trace_exec_finish.c