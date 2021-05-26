/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sock_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:12:50 by dzonda            #+#    #+#             */
/*   Updated: 2021/05/26 11:54:01 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_netsock.h"

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
 * ft_sock_get_icmp_type()
 *
 * Description:
 *    Get icmp type printable string
 * Returns:
 *    The elapsed time
*/
char *ft_sock_get_icmp_type(int type)
{
        static t_sock_icmp_type icmp[12] = {
                { ICMP_UNREACH, "Destination unreachable" },
                { ICMP_SOURCEQUENCH, "Packet lost" },
                { ICMP_ROUTERADVERT, "Router advertisement" },
                { ICMP_ROUTERSOLICIT, "Router soliciation" },
                { ICMP_TIMXCEED, "Time exceeded" },
                { ICMP_PARAMPROB, "Bad IP header" },
                { ICMP_TSTAMP, "Timestamp request" },
                { ICMP_TSTAMPREPLY, "Timestamp reply" },
                { ICMP_IREQ, "Information request" },
                { ICMP_IREQREPLY, "Information reply" },
                { ICMP_MASKREQ, "Address mask request" },
                { ICMP_MASKREPLY, "Address mask reply" },
        };

        int i;

        i = -1;
        while (++i < 12)
                if (type == icmp[i].type_int)
                        return  (icmp[i].type_str);
        return ("Unknown type");
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
