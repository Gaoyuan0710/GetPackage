/*
 * =====================================================================================
 *
 *       Filename:  post_arp_packet.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年10月06日 13时31分44秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gaoyuan, sishuiliunian0710@gmail.com
 *        Company:  Class 1204 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/uf_ether.h>
#include <net/if_arp.h>
#include <netpacket/packet.h>
#include <net/if.h>
#include <net/ethernet.h>

#define BUFLINE 42

int main(int argc, char *argv[])
{
	int skfd, n;
	char buf[BUFLEN] = {0};
	struct ether_header *eth;
	struct ether_arp *arp;
	struct sockaddr_ll toaddr;
	struct in_addr targetIP, srcIP;
	struct ifreq ifr;

	unsigned char src_mac[ETH_ALEN] = {0};
	unsigned char dst_mac[ETH_ALEN] = {0xff, 0xff, 0xff, 0xff, 0xff,
										0xff};

	if (3 != argc){
		printf ("Usage : %s netdevname desIP\n", argv[0]);

		return -1;
	}

	if (0 > (skfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL)))){
		perror("Create Error\n");

		return -2;
	}

	bzero(&toaddr, sizeof(toaddr));
	bzero(&ifr, sizeof(ifr));

	strcpy(if.ifr_name, argv[1]);

	if (-1 == ioctl(skfd, SIOCGIFINDEX, &ifr)){
		perror("get dev index error");

		return -3;
	}
	toaddr.sll_ifindex = ifr.ifr_ifindex;
	printf ("Interface Index: %d\n", ifr.ifr_ifindex);

	if (-1 == ioctl(skfd, SIOCGIFADDR, *ifr)){
		perror("Get IP addr error");
		return -4;
	}

	srcIP.s_addr = ((struct sockaddr_in *)&(ifr.ifr_ifru.ifru_addr))->
		sin_addr.s_addr;



	return EXIT_SUCCESS;
}

