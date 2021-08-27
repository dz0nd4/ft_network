/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmap_res.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/26 13:43:08 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_nmap.h"

// char *ft_getservbyport(int port, char *protocol) {
//   struct servent *service;
//   service = getservbyport(htons(port), protocol);
//   if (service == NULL) return ("Unassigned");
//   return (service->s_name);
// }

char *ft_nmap_exec_port_state(int state) {
  t_map_istr port_states[FT_NMAP_PORT_STATE] = {
      {FT_NMAP_CLOSE, "Close"},
      {FT_NMAP_UNFILTERED, "Unfiltered"},
      {FT_NMAP_OPEN_FILTERED, "Open|Filtered"},
      {FT_NMAP_FILTERED, "Filtered"},
      {FT_NMAP_OPEN, "Open"}};
  int i = -1;

  while (++i < FT_NMAP_PORT_STATE)
    if (state == port_states[state].key) break;

  return (port_states[state].value);
}

char *ft_nmap_exec_res_scan_state(int state) {
  t_map_istr scan_state[FT_NMAP_SCAN_MAX] = {
      {FT_NMAP_SCAN_SYN, "SYN"},   {FT_NMAP_SCAN_NULL, "NULL"},
      {FT_NMAP_SCAN_ACK, "ACK"},   {FT_NMAP_SCAN_FIN, "FIN"},
      {FT_NMAP_SCAN_XMAS, "XMAS"}, {FT_NMAP_SCAN_UDP, "UDP"}};
  int i = -1;

  while (++i < FT_NMAP_SCAN_MAX)
    if (state == scan_state[i].key) break;

  return (scan_state[i].value);
}

int ft_nmap_resport(t_nmap_res res) {
  int iscan = -1;

  fprintf(stdout, "%d", res.port);
  fprintf(stdout, "%15s\t", ft_getservbyport(res.port, "tcp"));
  while (++iscan < FT_NMAP_SCAN_MAX) {
    if (res.res_scan[iscan].key != 0) {
      fprintf(stdout, "%s(%s) ",
              ft_nmap_exec_res_scan_state(res.res_scan[iscan].key),
              ft_nmap_exec_port_state(res.res_scan[iscan].state));
    }
  }
  // printf("%d\n", res.conclusion);
  fprintf(stdout, "%15s\n", ft_nmap_exec_port_state(res.conclusion));
}

int ft_nmap_resport2(t_nmap_resp resp) {
  int iscan = -1;
  // fprintf(stdout, "%d\n", resps->in.sin_port);
  t_nmap_resps *resps = (t_nmap_resps *)&resp.res_scan[iscan];

  fprintf(stdout, "%d", resp.port);  //.res_scan[iscan].in.sin_port);
  fprintf(stdout, "%15s\t", ft_getservbyport(resp.port, "tcp"));
  while (++iscan < FT_NMAP_SCAN_MAX) {
    if (resp.res_scan[iscan].key != 0) {
      fprintf(stdout, "%s(%s) ",
              ft_nmap_exec_res_scan_state(resp.res_scan[iscan].key),
              ft_nmap_exec_port_state(resp.res_scan[iscan].state));
    }
  }
  // printf("%d\n", res.conclusion);
  fprintf(stdout, "%15s\n", ft_nmap_exec_port_state(resp.conclusion));
}

int ft_nmap_result2(t_nmap_ctx ctx, t_nmap_opts opts) {
  // t_nmap_resp *res = &ctx.res[0];

  int j = -1;

  while (++j < opts.nports) {
    t_nmap_resp *resp = &ctx.resp[j];
    resp->conclusion = -1;

    int i = -1;
    while (++i < FT_NMAP_SCAN_MAX) {
      t_nmap_resps *resps = &resp->res_scan[i];

      if (resps->key) {
        printf("state: %d\n", resps->state);
        if (resps->state > resp->conclusion) resp->conclusion = resps->state;
      }
    }

    if (resp->conclusion == FT_NMAP_OPEN)
      ctx.resp_open[(ctx.ires_open)++] = *resp;
    else
      ctx.resp_close[(ctx.ires_close)++] = *resp;
  }

  int i = -1;

  if (ctx.ires_open) {
    ft_nmap_res_header(FT_TRUE);
    // fprintf(stdout, "Open ports:\n");
    // fprintf(stdout, "%s %15s %15s %15s\n", "Port", "Service Name", "Results",
    //         "Conclusion");
    // fprintf(stdout, "-------------------------------------\n");
    while (++i < ctx.ires_open) {
      ft_nmap_resport2(ctx.resp_open[i]);
    }
    fprintf(stdout, "\n");
  }

  i = -1;
  if (ctx.ires_close) {
    ft_nmap_res_header(FT_FALSE);

    // fprintf(stdout, "Closed/Filtered/Unfiltered ports:\n");
    // fprintf(stdout, "%s %15s %15s %15s\n", "Port", "Service Name", "Results",
    //         "Conclusion");
    // fprintf(stdout, "-------------------------------------\n");
    while (++i < ctx.ires_close) {
      ft_nmap_resport2(ctx.resp_close[i]);
    }
    fprintf(stdout, "\n");
  }
  // while (++i < opts.nports) {
  //   ft_nmap_resport(ctx.res[i]);
  // }

  return (FT_EXOK);
}

int ft_nmap_result(t_nmap_ctx ctx, t_nmap_opts opts) {
  int i = -1;
  t_nmap_res *res = &ctx.res[0];

  if (ctx.ires_open) {
    ft_nmap_res_header(FT_TRUE);
    // fprintf(stdout, "Open ports:\n");
    // fprintf(stdout, "%s %15s %15s %15s\n", "Port", "Service Name", "Results",
    //         "Conclusion");
    // fprintf(stdout, "-------------------------------------\n");
    while (++i < ctx.ires_open) {
      ft_nmap_resport(ctx.res_open[i]);
    }
    fprintf(stdout, "\n");
  }

  i = -1;
  if (ctx.ires_close) {
    ft_nmap_res_header(FT_FALSE);

    // fprintf(stdout, "Closed/Filtered/Unfiltered ports:\n");
    // fprintf(stdout, "%s %15s %15s %15s\n", "Port", "Service Name", "Results",
    //         "Conclusion");
    // fprintf(stdout, "-------------------------------------\n");
    while (++i < ctx.ires_close) {
      ft_nmap_resport(ctx.res_close[i]);
    }
    fprintf(stdout, "\n");
  }
  // while (++i < opts.nports) {
  //   ft_nmap_resport(ctx.res[i]);
  // }

  return (FT_EXOK);
}
