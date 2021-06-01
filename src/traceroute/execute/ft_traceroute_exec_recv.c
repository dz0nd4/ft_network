/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute_execute_recv.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/27 01:00:48 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_traceroute.h"

// static double   ft_traceroute_execute_recv_print_time(t_tr_time *time)
// {
//   double start = (time->start.tv_sec) * 1000 + (time->start.tv_usec) / 1000;
//   double stop = (time->stop.tv_sec) * 1000 + (time->stop.tv_usec) / 1000 ;
//   double dt = stop - start;
//   return dt;
// }

// int   ft_traceroute_exec_recv_print_flag(int code)
// {
//     static t_sock_icmp_type icmp[5] = {
//       { ICMP_UNREACH_NET, " !N" },
//       { ICMP_UNREACH_HOST, " !H" },
//       { ICMP_UNREACH_PROTOCOL, " !P" },
//       { ICMP_UNREACH_NEEDFRAG, " !F" },
//       { ICMP_UNREACH_SRCFAIL, " !S" },
//     };
//     int i;

//     i = -1;
//     while (++i < 5)
//       if (code == icmp[i].type_int) {
//         printf("%s", icmp[i].type_str);
//         return (FT_EXOK);
//       }
//     return (FT_EXFAIL);
// }

// int   ft_traceroute_exec_recv_print(t_tr_opts *opts, t_tr_from *from, t_tr_to to)
// {
//   char host_name[FT_NI_MAXHOST];
//   char *host_addr;

//   // t_tr_pack_hdr_icmp *hdr_icmp; 
//   // t_tr_pack_hdr_udp *hdr_udp;

//   // hdr_icmp = (t_tr_pack_hdr_icmp *)from->buffer;
//   // hdr_udp = (t_tr_pack_hdr_udp *)&hdr_icmp->icmp.icmp_ip;
	
//   double elapsed_time = ft_getelapsedtime(&to.time.start);

//   t_icmp *icmp = (t_icmp *)&from->buffer[FT_IPHDR_LEN];
//   t_udp *udp = (t_udp *)&icmp->icmp_ip;
  
//   t_uchar type, code;

//   type = icmp->icmp_type;
//   code = icmp->icmp_code;

// 	if ((type == ICMP_TIMXCEED && code == ICMP_TIMXCEED_INTRANS) ||
// 	    type == ICMP_UNREACH) {
//     host_addr = inet_ntoa(from->saddrin.sin_addr);

//     // if (!ft_strequ(ctx->from.ip_last, host_addr)) {
//     if(opts->probes == 0) {
//       // ft_strcpy(ctx->from.ip_last, host_addr);

//       // ft_tr_resolve(&from->saddrin, host_name);
//       ft_getnameinfo(&from->saddrin, host_name);
//       // host_addr = inet_ntoa(ctx->from.saddrin.sin_addr);
//       printf("%s (%s)  ", host_name, host_addr);
//     }


//     // if (from->cc == 0) {
//     //   printf("  *");
//     // } else {
//       printf("%0.2f ms ", elapsed_time);
//     // }
//     // printf(" [%s: %d bytes] ", ft_sock_get_icmp_type(icmp->icmp_type), from                                                 ->cc);
//     if (icmp->icmp_type != ICMP_TIMXCEED)
//       ft_traceroute_exec_recv_print_flag(icmp->icmp_code);
//     // if (opts->probes + 1 >= opts->probes_max)
//     //   printf("\n");
//     if (type == ICMP_UNREACH && opts->probes + 1 == opts->probes_max)
//       return (FT_EXOK);
//   }
//   return (FT_EXFAIL);
// }

int   ft_traceroute_exec_recv(t_tr_opts *opts, t_tr_sock *to, t_tr_sock *from)
{
  fd_set    fds;


  FD_ZERO(&fds);
  // ft_traceroute_execute_recv_init(from);
  
  FD_SET(from->fd, &fds);

  if (select(from->fd + 1, &fds, (fd_set *)0, (fd_set *)0, &from->tv))
    if((from->cc = ft_recvfrom(from->fd, from->data, from->datalen, &from->saddrin)))
      return (FT_EXOK);

  return (FT_EXFAIL);
}
