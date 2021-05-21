/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sock_time.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/21 15:11:00 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_netsock.h"

/*
 * ft_sock_gettime
 *
 * Description:
 *    Abstraction over gettimeofday function.å
 * Returns:
 *    EXIT_SUCCESS or EXIT_FAILURE if gettimeofday fail
*/
int		ft_sock_gettime(t_timeval *tv)
{
	if (gettimeofday(tv, NULL) == -1) {
      // fprintf(stderr, "gettimeofday\n");
      return(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/*
 * ft_sock_delay
 *
 * Description:
 *    Simple delay function.
 * Returns:
 *    The number of data read or -1
*/
int		ft_sock_delay()
{
  t_timeval start;
  t_timeval stop;
	double elapsedTime;

	ft_sock_gettime(&start);
	while (1) {
		ft_sock_gettime(&stop);
		elapsedTime = (stop.tv_sec - start.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (stop.tv_usec - start.tv_usec) / 1000.0;   // us to ms

		if (elapsedTime > 1000)
			return 1;
	}
	return 0;
}

/*
 * ft_sock_timediff()
 *
 * Description:
 *    Subtract 2 timeval structs to get the elapsed time.
 * Returns:
 *    The elapsed time
*/
double     ft_sock_timediff(t_timeval *out, t_timeval *in)
{
    double elapsedTime = (out->tv_sec - in->tv_sec) * 1000.0;      
    elapsedTime += (out->tv_usec - in->tv_usec) / 1000.0;  
    return elapsedTime;
}

/*
 * ft_sock_getelapsedtime()
 *
 * Description:
 *    Subtract 2 timeval structs to get the elapsed time.
 * Returns:
 *    The elapsed time
*/
double     ft_sock_getelapsedtime(t_timeval *in)
{
        t_timeval out;

        ft_sock_gettime(&out);
    return (ft_sock_timediff(&out, in));
}
