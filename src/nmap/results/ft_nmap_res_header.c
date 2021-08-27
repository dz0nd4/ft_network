/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmap_res_header.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/08/18 17:21:42 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

void ft_nmap_res_header(int state) {
  if (state == FT_TRUE)
    fprintf(stdout, "Open ports:\n");
  else
    fprintf(stdout, "Closed/Filtered/Unfiltered ports:\n");
  fprintf(stdout, "%s %15s %15s %15s\n", "Port", "Service Name", "Results",
          "Conclusion");
  fprintf(stdout,
          "--------------------------------------------------------------------"
          "-----------\n");
}
