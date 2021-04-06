
#include "ft_traceroute.h"
#define __USE_BSD	/* use bsd'ish ip header */
#include <sys/socket.h>	/* these headers are for a Linux system, but */
#include <netinet/in.h>	/* the names on other systems are easy to guess.. */
#include <netinet/ip.h>
#define __FAVOR_BSD	/* use bsd'ish tcp header */
#include <netinet/tcp.h>
#include <unistd.h>
#include<errno.h>
#include<time.h>

struct sockaddr_in source,dest;
char *address;

void print_ip_header(unsigned char* Buffer, int Size)
{
	unsigned short iphdrlen;
		
	// struct iphdr *iph = (struct iphdr *)Buffer;
	// iphdrlen =iph->ihl*4;
	
	// memset(&source, 0, sizeof(source));
	// source.sin_addr.s_addr = iph->saddr;

 	struct ip *iph = (struct ip *)Buffer;

	memset(&source, 0, sizeof(source));
	source.sin_addr.s_addr = iph->ip_dst.s_addr;

	char *str = inet_ntoa(source.sin_addr);

	// if(strcmp(address, str) == 0)
	// 	return;
   
	strcpy(address, str);
	printf("%s\n", str);
}

void print_icmp_packet(unsigned char* Buffer , int Size)
{
	unsigned short iphdrlen = 0;
	printf("icmp packet received !\n");

	// struct iphdr *iph = (struct iphdr *)Buffer;
	// iphdrlen = iph->ihl*4;
	
 	struct ip *iph = (struct ip *)Buffer;

	struct icmphdr *icmph = (struct icmphdr *)(Buffer + iphdrlen);
			
	print_ip_header(Buffer, sizeof(iph));		
	memset(&Buffer, 0, sizeof(Buffer));
}

int main()
{
	struct sockaddr saddr;
	int saddr_size;
	int count=0;
	int fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	unsigned char *buf = (unsigned char *)malloc(65536);
	int data_size;

	address = (char *) malloc(50 * sizeof(char));
	address[0] = '\0';
	while (1) {
		saddr_size = sizeof(saddr);
		if ((data_size = recvfrom(fd, buf, 65536, 0, &saddr, &saddr_size)) > 0) {
			// printf("icmp packet received: %s\n", buf);
			print_icmp_packet(buf, sizeof(buf));
		}
	}
	return 0;
}