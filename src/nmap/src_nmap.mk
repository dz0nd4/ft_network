SUBDIRS_NMAP = \
			nmap \
			nmap/options \
			nmap/config \
			nmap/execute \
			nmap/results

SUBFILES_NMAP = \
			nmap/ft_nmap.c \
			nmap/options/ft_nmap_parse.c \
			nmap/options/ft_nmap_opts.c \
			nmap/config/ft_nmap_conf_global.c \
			nmap/config/ft_nmap_conf_scan.c \
			nmap/execute/ft_nmap_exec_config.c \
			nmap/execute/ft_nmap_exec.c \
			nmap/execute/ft_nmap_exec_port.c \
			nmap/execute/ft_nmap_exec_send.c \
			nmap/execute/ft_nmap_exec_recv.c \
			nmap/results/ft_nmap_res.c \
			nmap/results/ft_nmap_res_header.c 
