/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzonda <dzonda@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 03:34:15 by dzonda            #+#    #+#             */
/*   Updated: 2021/02/18 16:25:27 by dzonda           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUT_H
# define FT_PUT_H

# include "../to/ft_to.h"

int		ft_putchar_fd(char c, int fd);
int		ft_putchar(int c);

void	ft_putendl_fd(const char *s, int fd);
void	ft_putendl(const char *s);

void	ft_putendlpad_fd(const char *s, size_t len, int fd);
void	ft_putendlpad(const char *s, size_t len);

void	ft_puthexa_fd(int nb, int fd);
void	ft_puthexa(int nb);

void	ft_puthexapad_fd(int nb, size_t len, int fd);
void	ft_puthexapad(int nb, size_t len);

void	ft_putnbr_fd(int n, int fd);
void	ft_putnbr(int n);

void	ft_putnbrendl_fd(int n, int fd);
void	ft_putnbrendl(int n);

void	ft_putstr_fd(const char *s, int fd);
void	ft_putstr(const char *s);

void	ft_putstrpad_fd(const char *s, size_t len, int fd);
void	ft_putstrpad(const char *s, size_t len);

#endif
