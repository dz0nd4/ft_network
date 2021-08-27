/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trace_parse_opts.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/26 12:35:08 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

int ft_get_input(char *file, char **input) {
  int fd;
  char *tmp;
  char buf[4096];
  int nbuf;
  int length;

  fd = 0;
  tmp = NULL;
  ft_bzero(buf, 4096);
  nbuf = 0;
  length = 0;
  if (file != NULL && (fd = open(file, O_RDONLY)) == -1) return (0);
  while ((nbuf = read(fd, buf, 4096)) > 0) {
    tmp = ft_strnew(length);
    ft_memcpy(tmp, *input, length);
    ft_strdel(&(*input));
    *input = ft_strnew(length + nbuf);
    ft_memcpy(*input, tmp, length);
    ft_memcpy(*input + length, buf, nbuf);
    length += nbuf;
    ft_strdel(&tmp);
  }
  return (length);
}

/*
 * ft_nmap_opt_err_req_arg
 *
 * Description:
 *   error function for missing arg
 * Returns:
 *   FT_EXFAIL
 */
static int ft_nmap_opt_err_req_arg(t_arg *arg, const char *desc) {
  const char *opt;

  opt = arg->v[arg->i];
  fprintf(stderr, "Option `%s` (argc %d) requires an argument: `%s %s`", opt,
          arg->i, opt, desc);
  return (FT_EXFAIL);
}

/*
 * ft_nmap_opt_err_handle_arg
 *
 * Description:
 *   error function for invalid arg
 * Returns:
 *   FT_EXFAIL
 */
static int ft_nmap_opt_err_handle_arg(t_arg *arg) {
  const char *opt;
  const char *opt_arg;

  opt = arg->v[arg->i];
  opt_arg = arg->v[arg->i + 1];
  fprintf(stderr, "Cannot handle `%s' option with arg `%s' (argc %d)", opt,
          opt_arg, arg->i + 1);
  return (FT_EXFAIL);
}

/*
 * ft_nmap_opt_ports
 *
 * Description:
 *   -f: Start from the first_ttl hop (instead from 1)
 * Returns:
 *   FT_EXOK or FT_EXFAIL if hops greater than hops_max
 */
int ft_nmap_opt_ports(t_nmap_opts *opts, t_arg *arg) {
  char *opt_arg = NULL;
  char **ports = NULL;
  char **range = NULL;
  int i = -1;
  int r0, r1;

  // opt_arg = (char *)arg->v[arg->i + 1];
  if ((opt_arg = (char *)arg->v[arg->i + 1]) == NULL) {
    return (ft_nmap_opt_err_req_arg(arg, "ports"));
  }
  // printf("jeaare?\n");

  if ((ports = ft_strsplit(opt_arg, ',')) == NULL) {
    return (FT_EXFAIL);
  }

  opts->nports = 0;
  while (ports[++i]) {
    if ((range = ft_strsplit(ports[i], '-')) == NULL) return (FT_EXFAIL);

    if (range[0] && range[1]) {
      if (!ft_isdigitstr(range[0]) || !ft_isdigitstr(range[1]))
        return (FT_EXFAIL);
      if ((r0 = ft_atoi(range[0])) > (r1 = ft_atoi(range[1])))
        return (FT_EXFAIL);
      while (r0 <= r1) {
        opts->ports[opts->nports++] = r0++;
      }
    } else if (range[0] && ft_isdigitstr(range[0])) {
      opts->ports[opts->nports++] = ft_atoi(range[0]);
    } else {
      return (FT_EXFAIL);
    }

    ft_stradel(&range);
  }

  ft_stradel(&ports);

  arg->i += 2;

  return (FT_EXOK);
}

/*
 * ft_nmap_opt_ip
 *
 * Description:
 *   -m: Set the max number of hops (max TTL to be reached). Default is 30
 * Returns:
 *   FT_EXOK
 */
int ft_nmap_opt_ip(t_nmap_opts *opts, t_arg *arg) {
  if (arg->v[arg->i + 1] == NULL) return (FT_EXFAIL);

  ft_memcpy(opts->ip[opts->nip], arg->v[arg->i + 1], FT_NMAP_BUFFER_DEFAULT);
  opts->nip += 1;
  arg->i += 2;

  return (FT_EXOK);
}

/*
 * ft_nmap_opt_file
 *
 * Description:
 *   -q: Set the number of probes per each hop. Default is 3
 * Returns:
 *   FT_EXOK
 */
int ft_nmap_opt_file(t_nmap_opts *opts, t_arg *arg) {
  int i = -1;
  int cc = 0;
  char *input = NULL;
  char **ainput = NULL;

  if ((opts->file = arg->v[arg->i + 1]) == NULL) {
    return (FT_EXFAIL);
  }

  if ((cc = ft_get_input(opts->file, &input)) == 0) {
    return (FT_EXFAIL);
  }

  if ((ainput = ft_strsplit(input, '\n')) == NULL) {
    ft_strdel(&input);
    return (FT_EXFAIL);
  }

  while (ainput[opts->nip] != NULL && ft_strlen(ainput[opts->nip])) {
    ft_memcpy(opts->ip[opts->nip], ainput[opts->nip], FT_NMAP_BUFFER_DEFAULT);
    opts->nip += 1;
  }

  ft_strdel(&input);
  ft_stradel(&ainput);

  arg->i += 2;

  return (FT_EXOK);
}

/*
 * ft_nmap_opt_speedup
 *
 * Description:
 *   -q: Set the number of probes per each hop. Default is 3
 * Returns:
 *   FT_EXOK
 */
int ft_nmap_opt_speedup(t_nmap_opts *opts, t_arg *arg) {
  const char *opt_arg;

  opt_arg = arg->v[arg->i + 1];
  if (opt_arg == NULL) return (ft_nmap_opt_err_req_arg(arg, "speedup"));
  if (!ft_isdigitstr(opt_arg)) return (ft_nmap_opt_err_handle_arg(arg));
  opts->speedup = ft_atoi(opt_arg);

  arg->i += 2;

  return (FT_EXOK);
}

/*
 * ft_nmap_opt_scan
 *
 * Description:
 *   -q: Set the number of probes per each hop. Default is 3
 * Returns:
 *   FT_EXOK
 */
int ft_nmap_opt_scan(t_nmap_opts *opts, t_arg *arg) {
  const t_map_istr nmap_scan[FT_NMAP_SCAN_MAX] = {
      {FT_NMAP_SCAN_SYN, "SYN"},   {FT_NMAP_SCAN_NULL, "NULL"},
      {FT_NMAP_SCAN_ACK, "ACK"},   {FT_NMAP_SCAN_FIN, "FIN"},
      {FT_NMAP_SCAN_XMAS, "XMAS"}, {FT_NMAP_SCAN_UDP, "UDP"},
  };
  int scans = -1;
  int key = -1;
  const char *scan = NULL;
  const char *opt_arg;
  char **scans_arg = NULL;

  if ((opt_arg = arg->v[arg->i + 1]) == NULL)
    return (ft_nmap_opt_err_req_arg(arg, "scan"));

  if ((scans_arg = ft_strsplit(opt_arg, '-')) == NULL) return (FT_EXFAIL);

  // printf("here\n");
  opts->scan = 0;
  while (scans_arg[++scans]) {
    key = -1;
    while (++key < FT_NMAP_SCAN_MAX) {
      if (ft_strequ(nmap_scan[key].value, scans_arg[scans])) {
        opts->scan |= nmap_scan[key].key;
        break;
      }
    }
  }

  if (key == FT_NMAP_SCAN_MAX) {
    return (ft_nmap_opt_err_handle_arg(arg));
  }

  arg->i += 2;

  return (FT_EXOK);
}

/*
 * ft_nmap_opt_help
 *
 * Description:
 *   -h:
 * Returns:
 *   FT_EXOK
 */
int ft_nmap_opt_help(t_nmap_opts *opts, t_arg *arg) {
  return (ft_nmap_usage());
}