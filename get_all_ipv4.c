/*
 * =====================================================================================
 *
 *       Filename:  get_all_ipv4.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年10月04日 20时23分40秒
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
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	int socket, n;
	int i;
	char buffer[2048];
	struct ethhdr *eth;
	struct iphdr *iph;

	if (0 > (socket = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_IP)))){
		perror("socket");

		return -1;
	}
	
	while (1){
		printf ("==========================================");

		n = recvfrom(socket, buffer, sizeof(buffer), 0, NULL. NULL);
		printf ("%d bytes read\n", n);

		eth = (struct ethhdr *)buffer;
		printf ("Dest MAC addr ");

		for (i = 0; i < 6; i++){
			printf(":%02x", eth->h_dest[i]);
		}
		printf ("Source MAC addr ");
		for (i = 0; i < 6; i++){
			printf(":%02x", eth->h_source[i]);
		}

		iph = (struct iphdr *)(buffer + sizeof(struct ethhdr));

		if (iph->version == 4 && iph->ihl == 5){
			printf ("Source host:%s\n", inet_ntop(iph->saddr));
			printf ("Dest host:%s\n", inet_ntop(iph->daddr));
		}
	}

	return EXIT_SUCCESS;
}

