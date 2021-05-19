/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sock_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/19 19:31:26 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ping.h"

/*
 * ft_sock_cksum
 *
 * Description:
 *    One's complement function
 * Returns:
 *    
*/
unsigned short ft_sock_cksum(void *b, int len)
{
	unsigned short *buf = b;
	unsigned int sum=0;
	unsigned short result;

	for (sum = 0; len > 1; len -= 2)
		sum += *buf++;
	if (len == 1)
		sum += *(unsigned char*)buf;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	result = ~sum;
	return (result);
}

/*
 * ft_sock_gettime
 *
 * Description:
 *    Abstraction over gettimeofday function.
 * Returns:
 *    EXIT_SUCCESS or EXIT_FAILURE if gettimeofday fail
*/
int		ft_sock_gettime(t_timeval *tv)
{
	if (gettimeofday(tv, NULL) == -1) {
      fprintf(stderr, "gettimeofday\n");
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
	t_tr_time delay;
	double elapsedTime;

	ft_sock_gettime(&delay.start);
	while (1) {
		ft_sock_gettime(&delay.stop);
		elapsedTime = (delay.stop.tv_sec - delay.start.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (delay.stop.tv_usec - delay.start.tv_usec) / 1000.0;   // us to ms

		if (elapsedTime > 1000)
			return 1;
	}
	return 0;
}

 
#ifndef HEXDUMP_COLS
#define HEXDUMP_COLS 16
#endif
 
void hexdump(void *mem, unsigned int len)
{
        unsigned int i, j;
        
        for(i = 0; i < len + ((len % HEXDUMP_COLS) ? (HEXDUMP_COLS - len % HEXDUMP_COLS) : 0); i++)
        {
                /* print offset */
                if(i % HEXDUMP_COLS == 0)
                {
                        printf("0x%06x: ", i);
                }
 
                /* print hex data */
                if(i < len)
                {
                        printf("%02x ", 0xFF & ((char*)mem)[i]);
                }
                else /* end of block, just aligning for ASCII dump */
                {
                        printf("   ");
                }
                
                /* print ASCII dump */
                if(i % HEXDUMP_COLS == (HEXDUMP_COLS - 1))
                {
                        for(j = i - (HEXDUMP_COLS - 1); j <= i; j++)
                        {
                                if(j >= len) /* end of block, not really printing */
                                {
                                        putchar(' ');
                                }
                                else if(isprint(((char*)mem)[j])) /* printable char */
                                {
                                        putchar(0xFF & ((char*)mem)[j]);        
                                }
                                else /* other char */
                                {
                                        putchar('.');
                                }
                        }
                        putchar('\n');
                }
        }
}