/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 20:13:22 by dzonda            #+#    #+#             */
/*   Updated: 2021/07/25 11:30:44 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char *ft_strjoin(const char *s1, const char *s2) {
  int i;
  int j;
  char *str;

  i = 0;
  j = 0;
  str = NULL;
  if (s1 == NULL || s2 == NULL) return (NULL);
  if ((str = ft_strnew(ft_strlen(s1) + ft_strlen(s2))) == NULL) return (NULL);
  while (s1[i] != '\0') str[j++] = s1[i++];
  i = -1;
  while (s2[i] != '\0') str[j++] = s2[i++];
  return (str);
}
