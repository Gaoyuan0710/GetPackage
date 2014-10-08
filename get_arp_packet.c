/*
 * =====================================================================================
 *
 *       Filename:  get_arp_packet.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年10月08日 16时19分59秒
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
#include <netinet/if_ether.h>
#include <net/if_arp.h>
#include <netpacket/packet.h>
#include <net/if.h>

#define BUFLINE 60

int main(int argc, char *argv[])
{
	int i, skfd, n;
	int number;
	char buf[ETH_FRAME_LEN] = {0};
	struct ethhdr *eth;
	struct ether_arp *arp;
	struct sockaddr_ll fromaddr;
	struct ifreq ifr;

	unsigned char src_mac[ETH_ALEN] = {0};

	if (2 != argc){
		printf ("Usage ; %s netdevName \n", argv[0]);

		return -1;
	}

	if (0 > (skfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ARP)))){
		perror("Create error");

		return -2;
	}

	bzero(&fromaddr, sizeof(fromaddr));
	bzero(&ifr, sizeof(ifr));
	strcpy(ifr.ifr_ifrn.ifrn_name, argv[1]);

	if (-1 == ioctl(skfd, SIOCGIFINDEX, &ifr)){
		perror("get dev index error:");

		return -3;
	}
	fromaddr.sll_ifindex = ifr.ifr_ifru.ifru_ivalue;
	printf ("interface index : %d\n", ifr.ifr_ifru.ifru_ivalue);

	if (-1 == ioctl(skfd, SIOCGIFHWADDR, &ifr)){
		perror("get dev MAC addr error");
		return -4;
	}

	memcpy(src_mac, ifr.ifr_ifru.ifru_hwaddr.sa_data, ETH_ALEN);
	printf ("MAC: ");

	for (number = 0; number < 6; number++){
		printf ("%02x", src_mac[number]);

		if (number + 1 != 6){
			printf ("-");
		}
	}
	printf("\n");

	fromaddr.sll_family = PF_PACKET;
	fromaddr.sll_protocol = htons(ETH_P_ARP);
	fromaddr.sll_hatype = ARPHRD_ETHER;
	fromaddr.sll_pkttype = PACKET_HOST;
	fromaddr.sll_halen = ETH_ALEN;

	memcpy(fromaddr.sll_addr, src_mac, ETH_ALEN);

	bind(skfd, (struct sockaddr *)&fromaddr, sizeof(struct sockaddr));

	while (1){
		memset(buf, 0, ETH_FRAME_LEN);
		n = recvfrom(skfd, buf, ETH_FRAME_LEN, 0, NULL, NULL);
		eth = (struct ethhdr *)buf;
		arp = (struct ether_arp *)(buf + 14);

		printf("Dest MAC:");

		for (i = 0; i < ETH_ALEN; i++){
			printf ("%02x-", eth->h_dest[i]);
		}
		printf("Sender MAC:");

		for (i = 0; i < ETH_ALEN; i++){
			printf ("%02x-", eth->h_source[i]);
		}
		printf ("\n");
		printf("Frame type:%0X\n", ntohs(eth->h_proto));

		if (ntohs(arp->arp_op) == 2){
			printf ("Get An replay!\n");
		}
		close(skfd);

	}
	return EXIT_SUCCESS;
}

