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
#include <netinet/if_ether.h>
#include <net/if_arp.h>
#include <netpacket/packet.h>
#include <net/if.h>
#include <net/ethernet.h>
#include <arpa/inet.h>

#define BUFLINE 42

int main(int argc, char *argv[])
{
	int skfd, n;
	int i;
	char buf[BUFLINE] = {0};
	struct ether_header *eth;                //以太网报头结构信息
	struct ether_arp *arp;                   //arp 报头信息
	struct sockaddr_ll toaddr;               //表示与设备无关的物理层地址结构
	struct in_addr targetIP, srcIP;         
	struct ifreq ifr;                        //用来配置ip地址等接口信息


	unsigned char src_mac[ETH_ALEN] = {0};   //ETH_ALEN MAC 地址长度
	unsigned char dst_mac[ETH_ALEN] = {0xff, 0xff, 0xff, 0xff, 0xff,
										0xff};

	if (3 != argc){
		printf ("Usage : %s netdevname desIP\n", argv[0]);

		return -1;
	}

	if (0 > (skfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL)))){ //发送接收以太网数据帧
		perror("Create Error\n");

		return -2;
	}

	bzero(&toaddr, sizeof(toaddr));
	bzero(&ifr, sizeof(ifr));

	strcpy(ifr.ifr_name, argv[1]);

	if (-1 == ioctl(skfd, SIOCGIFINDEX, &ifr)){
		perror("get dev index error");

		return -3;
	}
	toaddr.sll_ifindex = ifr.ifr_ifindex;
	printf ("Interface Index: %d\n", ifr.ifr_ifindex);

	if (-1 == ioctl(skfd, SIOCGIFADDR, &ifr)){
		perror("Get IP addr error");
		return -4;
	}

	srcIP.s_addr = ((struct sockaddr_in *)&(ifr.ifr_ifru.ifru_addr))->
		sin_addr.s_addr;

	printf ("IP addr: %s\n", inet_ntoa(((struct sockaddr_in *)&(ifr.ifr_ifru.ifru_addr)
						)->sin_addr));


	if (-1 == ioctl(skfd, SIOCGIFHWADDR, &ifr)){
		perror("get dev MAC addr error:");

		return -1;
	}

	memcpy(src_mac, ifr.ifr_ifru.ifru_hwaddr.sa_data, ETH_ALEN);
	printf ("MAC:");

	for (i = 0; i < 6; i++){
		printf ("%02x", src_mac[i]);

		if (i + 1 != 6){
			printf("-");
		}
	}
	printf ("\b\n");

	eth = (struct ether_header *)buf;
	memcpy(eth->ether_dhost, dst_mac, ETH_ALEN);
	memcpy(eth->ether_shost, src_mac, ETH_ALEN);
	eth->ether_type = htons(ETHERTYPE_ARP);

	arp = (struct arphdr *)(buf + sizeof(struct ether_header));
	arp->arp_hrd = htons(ARPHRD_ETHER);
	arp->arp_pro = htons(ETHERTYPE_IP);

	arp->arp_hln = ETH_ALEN;
	arp->arp_pln = 4;

	arp->arp_op = htons(ARPOP_REQUEST);

	memcpy(arp->arp_sha, src_mac, ETH_ALEN);
	memcpy(arp->arp_spa, &srcIP, 4);

	inet_pton(AF_INET, argv[2], &targetIP);
	memcpy(arp->arp_tpa, &targetIP, 4);

	toaddr.sll_family = PF_PACKET;
	n = sendto(skfd, buf, BUFLINE, 0, (struct sockaddr *) & toaddr, sizeof(toaddr));

	close(skfd);


	return EXIT_SUCCESS;
}

