/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmap_exec_port.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/26 13:40:04 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

int ft_nmap_exec_port_scan(t_nmap_ctx *ctx, t_nmap_opts opts, t_sockaddr_in in,
                           t_nmap_resps *res_scan, int scan) {
  struct pollfd pfd;

  ft_memset(&pfd, 0, sizeof(pfd));
  t_nmap_res *res = &ctx->res[ctx->iport];

  // res->res_scan[iscan].key = scan;
}

int ft_nmap_exec_dev_init(t_nmap_dev *dev) {
  ft_memset(dev, 0, sizeof(*dev));

  // dev->name = ctx->sdev;
  // dev->addr = ctx->saddr;

  if (ft_pcap_lookupnet(dev->name, &dev->net, &dev->mask) == FT_EXFAIL)
    return (FT_EXFAIL);
  if (ft_pcap_open_live(&dev->handle, dev->name) == FT_EXFAIL)
    return (FT_EXFAIL);
  // if (ft_pcap_compile_setfilter(dev->handle, dev->addr, dev->net) ==
  // FT_EXFAIL)
  //   return (FT_EXFAIL);
  return (FT_EXOK);
}

// int ft_nmap_exec_port2(t_nmap_resp *resp) {
//   int iscan = -1;
//   int cc = 0;
//   t_nmap_dev dev;

//   // pthread_mutex_lock(&g_mutex);
//   // dev.name = resp->dev;
//   // dev.addr = resp->addr;

//   // if (ft_nmap_exec_dev_init(&dev) == FT_EXFAIL) return (FT_EXFAIL);
//   // if (ft_pcap_lookupnet(ctx->sdev, &net, &mask) == FT_EXFAIL ||
//   //     ft_pcap_open_live(&handle, ctx->sdev) == FT_EXFAIL ||
//   //     ft_pcap_compile_setfilter(handle, ctx->saddr, net) == FT_EXFAIL)
//   //   return (FT_EXFAIL);
//   // pthread_mutex_unlock(&g_mutex);

//   // t_nmap_res *res = &ctx->res[ctx->iport];

//   // res->port = scan->in.sin_port;

//   while (++iscan < FT_NMAP_SCAN_MAX) {
//     if (resp->scan & (1 << iscan)) {
//       resp->res_scan[iscan].key = 1 << iscan;
//       if (resp->res_scan[iscan].key > FT_NMAP_SCAN_XMAS)
//         resp->res_scan[iscan].proto = FT_NMAP_UDP;

//       // pfd.fd = pcap_get_selectable_fd(handle);
//       // pfd.events = POLLIN;
//       // pfd.revents = 0;

//       ft_nmap_exec_send2(*resp, iscan);

//       ft_nmap_exec_recv2(resp, iscan);

//       // ft_nmap_exec_send(*ctx, opts, in, (1 << iscan));
//       // ft_nmap_exec_recv(ctx, opts, 1 << iscan, iscan, dev.handle);
//       // if (poll(&pfd, 1, 2000)) {
//       //   cc = pcap_dispatch(handle, 1, &ft_nmap_exec_recv_handle,
//       //                      (t_uchar *)&res->res_scan[iscan]);
//       // } else {
//       //   printf("timeout...\n");
//       // }
//     }
//   }

//   // int conclusion = -1;
//   int i = -1;

//   resp->conclusion = -1;

//   while (++i < FT_NMAP_SCAN_MAX) {
//     if (resp->res_scan[i].key) {
//       // printf("here\n");
//       printf("state: %d\n", resp->res_scan[i].state);
//       if (resp->res_scan[i].state > resp->conclusion)
//         resp->conclusion = resp->res_scan[i].state;
//     }
//   }
//   // if (resp->conclusion == FT_NMAP_OPEN)
//   //   ctx->res_open[(ctx->ires_open)++] = *res;
//   // else
//   //   ctx->res_close[(ctx->ires_close)++] = *res;

//   // printf("Closing...\n");
//   // pcap_close(dev.handle);
//   return (FT_EXOK);
// }

// int ft_nmap_exec_port(t_nmap_ctx *ctx, t_nmap_opts opts, t_sockaddr_in in) {
//   int iscan = -1;
//   int cc = 0;
//   t_nmap_dev dev = {0};

//   // pcap_t *handle = NULL;

//   // pthread_mutex_lock(&g_mutex);
//   // dev.name = ctx->sdev;
//   // dev.addr = ctx->saddr;

//   // // if (ft_nmap_exec_dev_init(&dev) == FT_EXFAIL) return (FT_EXFAIL);
//   // if (ft_pcap_lookupnet(ctx->sdev, &dev.net, &dev.mask) == FT_EXFAIL ||
//   //     ft_pcap_open_live(&dev.handle, ctx->sdev) == FT_EXFAIL ||
//   //     ft_pcap_compile_setfilter(dev.handle, ctx->saddr, dev.net) ==
//   //     FT_EXFAIL)
//   //   return (FT_EXFAIL);
//   // pthread_mutex_unlock(&g_mutex);

//   t_nmap_res *res = &ctx->res[ctx->iport];

//   res->port = in.sin_port;

//   while (++iscan < FT_NMAP_SCAN_MAX) {
//     if (opts.scan & (1 << iscan)) {
//       res->res_scan[iscan].key = 1 << iscan;
//       if (res->res_scan[iscan].key > FT_NMAP_SCAN_XMAS)
//         res->res_scan[iscan].proto = FT_NMAP_UDP;

//       // pfd.fd = pcap_get_selectable_fd(handle);
//       // pfd.events = POLLIN;
//       // pfd.revents = 0;

//       ft_nmap_exec_send(*ctx, opts, in, (1 << iscan));
//       ft_nmap_exec_recv(ctx, opts, 1 << iscan, iscan, dev.handle);
//       // if (poll(&pfd, 1, 2000)) {
//       //   cc = pcap_dispatch(handle, 1, &ft_nmap_exec_recv_handle,
//       //                      (t_uchar *)&res->res_scan[iscan]);
//       // } else {
//       //   printf("timeout...\n");
//       // }
//     }
//   }

//   // int conclusion = -1;
//   int i = -1;

//   res->conclusion = -1;

//   while (++i < FT_NMAP_SCAN_MAX) {
//     if (res->res_scan[i].key) {
//       // printf("here\n");
//       if (res->res_scan[i].state > res->conclusion)
//         res->conclusion = res->res_scan[i].state;
//     }
//   }
//   if (res->conclusion == FT_NMAP_OPEN)
//     ctx->res_open[(ctx->ires_open)++] = *res;
//   else
//     ctx->res_close[(ctx->ires_close)++] = *res;

//   // printf("Closing...\n");
//   // pcap_close(dev.handle);
//   return (FT_EXOK);
// }