/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sock_icmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/07/26 20:41:55 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_sock.h"

/*
 * ft_icmp_pr_code_unreach()
 *
 * Description:
 *    Get icmp type printable string
 * Returns:
 *    The elapsed time
 */
char *ft_icmp_pr_code_unreach(int code) {
  const t_map_istr icmp_code[FT_NR_ICMP_UNREACH] = {
      {ICMP_NET_UNREACH, "Network Unreachable"},
      {ICMP_HOST_UNREACH, "Host Unreachable"},
      {ICMP_PROT_UNREACH, "Protocol Unreachable"},
      {ICMP_PORT_UNREACH, "Port Unreachable	"},
      {ICMP_FRAG_NEEDED, "Fragmentation Needed/DF set"},
      {ICMP_SR_FAILED, "Source Route failed"},
      {ICMP_NET_UNKNOWN, "Network Unknown"},
      {ICMP_HOST_UNKNOWN, "Host Unknown"},
      {ICMP_HOST_ISOLATED, "Host Isolated"},
      {ICMP_NET_ANO, "Network Anonymous"},
      {ICMP_HOST_ANO, "Host Anonymous"},
      {ICMP_NET_UNR_TOS, "Network Unreachable TOS"},
      {ICMP_HOST_UNR_TOS, "Host Unreachable TOS"},
      {ICMP_PKT_FILTERED, "Packet filtered"},
      {ICMP_PREC_VIOLATION, "Precedence violation"},
      {ICMP_PREC_CUTOFF, "Precedence cut off"},
  };
  int i = -1;

  while (++i < FT_NR_ICMP_UNREACH)
    if (code == icmp_code[i].key) return (icmp_code[i].value);
  return ("Unknown Code");
}

/*
 * ft_icmp_pr_code_redir()
 *
 * Description:
 *    Get icmp type printable string
 * Returns:
 *    The elapsed time
 */
char *ft_icmp_pr_code_redir(int code) {
  const t_map_istr icmp_code[FT_NR_ICMP_REDIR] = {
      {ICMP_REDIR_NET, "Redirect Net"},
      {ICMP_REDIR_HOST, "Redirect Host"},
      {ICMP_REDIR_NETTOS, "Redirect Net for TOS"},
      {ICMP_REDIR_HOSTTOS, "Redirect Host for TOS"},
  };
  int i = -1;

  while (++i < FT_NR_ICMP_REDIR)
    if (code == icmp_code[i].key) return (icmp_code[i].value);
  return ("Unknown Code");
}

/*
 * ft_icmp_pr_code_exc()
 *
 * Description:
 *    Get icmp type printable string
 * Returns:
 *    The elapsed time
 */
char *ft_icmp_pr_code_exc(int code) {
  const t_map_istr icmp_code[FT_NR_ICMP_EXC] = {
      {ICMP_EXC_TTL, "TTL count exceeded"},
      {ICMP_EXC_FRAGTIME, "Fragment Reass time exceeded"},
  };
  int i = -1;

  while (++i < FT_NR_ICMP_EXC)
    if (code == icmp_code[i].key) return (icmp_code[i].value);
  return ("Unknown Code");
}

/*
 * ft_icmp_pr_type()
 *
 * Description:
 *    Get icmp type printable string
 * Returns:
 *    The elapsed time
 */
char *ft_icmp_pr_type(int type) {
  const t_map_istr icmp_type[FT_NR_ICMP_TYPES] = {
      {ICMP_ECHOREPLY, "Echo Reply"},
      {1, "ICMP Type 1"},
      {2, "ICMP Type 2"},
      {ICMP_DEST_UNREACH, "Destination Unreachable"},
      {ICMP_SOURCE_QUENCH, "Source Quench"},
      {ICMP_REDIRECT, "Redirect"},
      {6, "ICMP Type 6"},
      {7, "ICMP Type 7"},
      {ICMP_ECHO, "Echo"},
      {9, "ICMP Type 9"},
      {10, "ICMP Type 10"},
      {ICMP_TIME_EXCEEDED, "Time exceeded"},
      {ICMP_PARAMETERPROB, "Bad IP header"},
      {ICMP_TIMESTAMP, "Timestamp"},
      {ICMP_TIMESTAMPREPLY, "Timestamp reply"},
      {ICMP_INFO_REQUEST, "Information request"},
      {ICMP_INFO_REPLY, "Information reply"},
      {ICMP_ADDRESS, "Address mask request"},
      {ICMP_ADDRESSREPLY, "Address mask reply"},
  };
  int i = -1;

  while (++i < FT_NR_ICMP_TYPES)
    if (type == icmp_type[i].key) return (icmp_type[i].value);
  return ("Unknown Type");
}
