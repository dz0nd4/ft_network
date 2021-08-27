/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmap_exec_recv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/26 18:03:06 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

int ft_nmap_exec_res_syn(t_tcphdr *tcp, int timeout) {
  // printf("ressyn %d\n", timeout);
  if (timeout == FT_TRUE)
    return (FT_NMAP_FILTERED);
  else if (tcp->syn && tcp->ack)
    return (FT_NMAP_OPEN);
  else if (tcp->rst && tcp->ack)
    return (FT_NMAP_CLOSE);
  return (FT_NMAP_FILTERED);
}

int ft_nmap_exec_res_null(t_tcphdr *tcp, int timeout) {
  if (timeout == FT_TRUE) return (FT_NMAP_OPEN_FILTERED);
  if (tcp->rst && tcp->ack) return (FT_NMAP_CLOSE);
  return (FT_NMAP_OPEN);
}

int ft_nmap_exec_res_ack(t_tcphdr *tcp, int timeout) {
  if (timeout == FT_TRUE) return (FT_NMAP_FILTERED);
  if (tcp->rst) return (FT_NMAP_UNFILTERED);
  return (FT_NMAP_FILTERED);
}

int ft_nmap_exec_res_fin(t_tcphdr *tcp, int timeout) {
  if (timeout == FT_TRUE) return (FT_NMAP_OPEN_FILTERED);
  if (tcp->rst && tcp->ack) return (FT_NMAP_CLOSE);
  return (FT_NMAP_OPEN);
}

int ft_nmap_exec_res_xmas(t_tcphdr *tcp, int timeout) {
  if (timeout == FT_TRUE) return (FT_NMAP_OPEN_FILTERED);
  if (tcp->rst) return (FT_NMAP_CLOSE);
  return (FT_NMAP_OPEN);
}

int ft_nmap_exec_res_udp(t_tcphdr *tcp, int timeout) {
  // printf("resudp\n");
  if (timeout == FT_TRUE) return (FT_NMAP_OPEN_FILTERED);
  return (FT_NMAP_OPEN);
}

int ft_nmap_exec_res_dispatch(int scan, t_tcphdr *tcp, int timeout) {
  const t_nmap_resps_d res_scan_d[FT_NMAP_SCAN_MAX] = {
      {FT_NMAP_SCAN_SYN, ft_nmap_exec_res_syn},
      {FT_NMAP_SCAN_NULL, ft_nmap_exec_res_null},
      {FT_NMAP_SCAN_ACK, ft_nmap_exec_res_ack},
      {FT_NMAP_SCAN_FIN, ft_nmap_exec_res_fin},
      {FT_NMAP_SCAN_XMAS, ft_nmap_exec_res_xmas},
      {FT_NMAP_SCAN_UDP, ft_nmap_exec_res_udp}};
  int i = -1;

  while (++i < FT_NMAP_SCAN_MAX) {
    if (scan == res_scan_d[i].scan_key) break;
  }

  return (res_scan_d[i].scan_dist(tcp, timeout));
}

void ft_nmap_exec_recv_handle(t_uchar *user, const t_pcap_pkthdr *pkthdr,
                              const t_uchar *pkt) {
  t_nmap_resps *res_scan = NULL;
  t_ethhdr *eth = NULL;
  t_iphdr *ip = NULL;
  t_tcphdr *tcp = NULL;
  // printf("Proccessing packet for scan : %d !\n", res_scan->key);

  res_scan = (t_nmap_resps *)user;
  eth = (t_ethhdr *)pkt;
  ip = (t_iphdr *)(pkt + ETH_HLEN);
  if (ip->protocol == IPPROTO_TCP) {
    tcp = (t_tcphdr *)((void *)pkt + sizeof(t_ethhdr) + sizeof(t_iphdr));

    res_scan->state = ft_nmap_exec_res_dispatch(res_scan->key, tcp, FT_FALSE);
  }
  return;
}

int ft_nmap_exec_recv3(t_nmap_resps *resps) {
  struct pollfd pfd;
  int cc = 0;
  int count = 0;
  t_nmap_dev dev = {0};

  // t_nmap_res *res = &ctx->res[ctx->iport];

  // pthread_mutex_lock(&g_mutex);
  // dev.name = resp->dev;
  // dev.addr = resp->addr;
  if (resps->key > FT_NMAP_SCAN_XMAS) resps->proto = FT_NMAP_UDP;
  // if (ft_nmap_exec_dev_init(&dev) == FT_EXFAIL) return (FT_EXFAIL);
  pthread_mutex_lock(&g_mutex);
  if (ft_getaddrin_raw(&resps->in, resps->ip) == FT_EXFAIL) {
    fprintf(stderr, "Failed to resolve \"%s\"\n", resps->ip);
    return (FT_EXFAIL);
  }
  resps->in.sin_port = resps->port;

  if (ft_pcap_lookupdev(&dev.name) == FT_EXFAIL ||
      ft_getifaddr((const char *)dev.name, &dev.addr) == FT_EXFAIL ||
      ft_pcap_lookupnet(dev.name, &dev.net, &dev.mask) == FT_EXFAIL ||
      ft_pcap_open_live(&dev.handle, dev.name) == FT_EXFAIL ||
      ft_pcap_compile_setfilter(dev.handle, dev.addr, dev.net,
                                resps->in.sin_port) == FT_EXFAIL)
    return (FT_EXFAIL);

  resps->addr = dev.addr;

  pthread_mutex_unlock(&g_mutex);

  pfd.fd = pcap_get_selectable_fd(dev.handle);

  // if (bind(pfd.fd, ))

  if (pfd.fd == -1) {
    fprintf(stderr, "err %s\n", pcap_geterr(dev.handle));
  } else {
    // printf("fd: %d\n", pfd.fd);
  }
  pfd.events = POLLIN;
  pfd.revents = 0;

  ft_nmap_exec_send3(*resps);

  while (!cc && count < 2) {
    if (poll(&pfd, 1, 1000)) {
      if (pfd.revents & POLLIN)
        cc = pcap_dispatch(dev.handle, 1, &ft_nmap_exec_recv_handle,
                           (t_uchar *)resps);

      break;
    } else {
      count += 1;
    }
  }

  // printf("count %d\n", count);
  // printf("herrre \n");

  if (count == 2)
    resps->state = ft_nmap_exec_res_dispatch(resps->key, NULL, FT_TRUE);
  pcap_close(dev.handle);

  return (FT_EXOK);
}

// int ft_nmap_exec_recv2(t_nmap_resp *resp, int iscan) {
//   struct pollfd pfd;
//   int cc = 0;
//   int count = 0;
//   t_nmap_dev dev = {0};

//   // t_nmap_res *res = &ctx->res[ctx->iport];

//   // pthread_mutex_lock(&g_mutex);
//   // dev.name = resp->dev;
//   // dev.addr = resp->addr;

//   // if (ft_nmap_exec_dev_init(&dev) == FT_EXFAIL) return (FT_EXFAIL);
//   pthread_mutex_lock(&g_mutex);
//   if (ft_pcap_lookupdev(&dev.name) == FT_EXFAIL ||
//       ft_getifaddr((const char *)dev.name, &dev.addr) == FT_EXFAIL ||
//       ft_pcap_lookupnet(dev.name, &dev.net, &dev.mask) == FT_EXFAIL ||
//       ft_pcap_open_live(&dev.handle, resp->dev) == FT_EXFAIL ||
//       ft_pcap_compile_setfilter(dev.handle, resp->addr, dev.net,
//                                 resp->in.sin_port) == FT_EXFAIL)
//     return (FT_EXFAIL);

//   pthread_mutex_unlock(&g_mutex);

//   pfd.fd = pcap_get_selectable_fd(dev.handle);

//   // if (bind(pfd.fd, ))

//   if (pfd.fd == -1) {
//     fprintf(stderr, "err %s\n", pcap_geterr(dev.handle));
//   } else {
//     // printf("fd: %d\n", pfd.fd);
//   }
//   pfd.events = POLLIN;
//   pfd.revents = 0;

//   while (!cc && count < 2) {
//     if (poll(&pfd, 1, 1000)) {
//       if (pfd.revents & POLLIN)
//         cc = pcap_dispatch(dev.handle, 1, &ft_nmap_exec_recv_handle,
//                            (t_uchar *)&resp->res_scan[iscan]);

//       break;
//     } else {
//       count += 1;
//     }
//   }

//   // printf("count %d\n", count);
//   // printf("herrre \n");

//   if (count == 2)
//     resp->res_scan[iscan].state =
//         ft_nmap_exec_res_dispatch(resp->res_scan[iscan].key, NULL, FT_TRUE);
//   pcap_close(dev.handle);

//   return (FT_EXOK);
// }

// int ft_nmap_exec_recv(t_nmap_ctx *ctx, t_nmap_opts opts, int scan, int iscan,
//                       pcap_t *handle) {
//   struct pollfd pfd;
//   int cc = 0;
//   int count = 0;
//   t_nmap_dev dev = {0};

//   t_nmap_res *res = &ctx->res[ctx->iport];

//   pthread_mutex_lock(&g_mutex);
//   dev.name = ctx->sdev;
//   dev.addr = ctx->saddr;

//   // if (ft_nmap_exec_dev_init(&dev) == FT_EXFAIL) return (FT_EXFAIL);
//   pthread_mutex_lock(&g_mutex);

//   if (ft_pcap_lookupnet(ctx->sdev, &dev.net, &dev.mask) == FT_EXFAIL ||
//       ft_pcap_open_live(&dev.handle, ctx->sdev) == FT_EXFAIL ||
//       ft_pcap_compile_setfilter(dev.handle, ctx->saddr, dev.net, res->port)
//       ==
//           FT_EXFAIL)
//     return (FT_EXFAIL);
//   pthread_mutex_unlock(&g_mutex);

//   pfd.fd = pcap_get_selectable_fd(dev.handle);

//   // if (bind(pfd.fd, ))

//   if (pfd.fd == -1) {
//     fprintf(stderr, "err %s\n", pcap_geterr(dev.handle));
//   } else {
//     printf("fd: %d\n", pfd.fd);
//   }
//   pfd.events = POLLIN;
//   pfd.revents = 0;

//   while (!cc && count < 2) {
//     if (poll(&pfd, 1, 1000)) {
//       if (pfd.revents & POLLIN)
//         cc = pcap_dispatch(dev.handle, 1, &ft_nmap_exec_recv_handle,
//                            (t_uchar *)&res->res_scan[iscan]);

//       break;
//     } else {
//       count += 1;
//     }
//   }

//   // printf("count %d\n", count);

//   if (count == 2)
//     res->res_scan[iscan].state =
//         ft_nmap_exec_res_dispatch(res->res_scan[iscan].key, NULL, FT_TRUE);
//   pcap_close(dev.handle);

//   return (FT_EXOK);
// }
// // void ft_nmap_execute_recv(t_uchar *user, const t_pcap_pkthdr *pkthdr,
// //                           const t_uchar *pkt) {
// //   t_nmap_resps *res_scan = NULL;
// //   t_ethhdr *eth = NULL;
// //   t_iphdr *ip = NULL;
// //   t_tcphdr *tcp = NULL;

// //   res_scan = (t_nmap_resps *)user;
// //   printf("Proccessing packet for scan : %d !\n", res_scan->key);
// //   eth = (t_ethhdr *)pkt;
// //   ip = (t_iphdr *)(pkt + ETH_HLEN);
// //   if (ip->protocol == IPPROTO_TCP) {
// //     tcp = (t_tcphdr *)((void *)pkt + sizeof(t_ethhdr) + sizeof(t_iphdr));

// //     res_scan->state = ft_nmap_exec_res_dispatch(res_scan->key, tcp);
// //   }
// //   return;
// // }
