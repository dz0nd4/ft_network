/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmap_conf_scan.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/22 19:39:59 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

int ft_nmap_config_scan(char *ip) {
  fprintf(stdout,
          "\n Scan Configuration \n"
          " ------------------------------------------------ \n");

  fprintf(stdout, "Target IP address: %s \n\n", ip);

  // fprintf(stdout, " ------------------------------------------------
  // \n\n\n");
  return (FT_EXOK);
}
