/*
 * =====================================================================================
 *
 *       Filename:  arpsniffer.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年09月26日 17时22分33秒
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
#include <pcap.h>
#include <string.h>
#include <arpa/inet.h>

#define ARP_REQUEST 1
#define ARP_REPLY   2

typedef struct arphdr{
	u_int16_t hardType;
	u_int16_t protocolType;
	u_char hardLen;
	u_char protocolLen;
	u_int16_t oper;
	u_char sendHardAdr[6];
	u_char sendIPAdr[4];
	u_char targetHardAdr[6];
	u_char targetIPAdr[4];
}arphdr_t;

#define MAXBYTES2CAPTURE 2048


int main(int argc, char *argv[])
{
	int i =0;
	struct bpf_program filter;
	struct pcap_pkthdr pkthdr;
	struct ip *iphdr = NULL;
	struct tcphdr &tcphdr = NULL;
	char errbuf[PCAP_ERRBUF_SIZE];
	const unsigned char *packet = NULL;
	pcap_t *descr = NULL;
	bpf_u_int32 netaddr = 0, mask = 0;
	arphdr_t *arpheader = NULL;

	memset (errbuf, 0, PCAP_ERRBUF_SIZE);

	if (argc != 2){
		printf ("Usage:arpsniffer <interface>\n");
		
		exit (-1);
	}

	descr = pcap_open_live(argv[1], MAXBYTES2CAPTURE, 0, 512, errbuf);

	if (pcap_lookupnet(argv[1], &netaddr, &mask, errbuf) == -1)
	{
		fprintf(stderr, "ERROR:pcap_lookipnet():%s\n", errbuf);

		exit(-1);
	}

	if (pcap_compile(descr, &filter, "arp", 1, mask) == -1){
		fprintf(stderr, "Error in pcap_compile(): %s\n", pcap_geterr(descr));

		exit(-2);
	}

	if (pcap_setfilter(descr, &filter) == -1){
		fprintf(stderr, "Error in pcap_setfilter():%s\n", pcap_geterr(descr));

		exit(-3);
	}

	while (1){
		if ((packet = pcap_next(descr, &pkthdr)) == NULL){
			fprintf(stderr, "Error in pcap+next()\n", errbuf);

			exit (-4);
		}

		arpheader = (struct arphdr *)(packet + 14);
		
		printf ("\n\nReceived Packet Size: %d bytes\n", pkthdr->len);
		printf ("Hardware type: %s\n", (ntohs(arpheader->hardType) == 1 ? "Ethernet" : "Unknow"));
 		printf ("Protocol type : %s\n", (ntohs(arpheader->protocolType) == 0x0800) ? "Ethernet" : "Unknow");
		printf ("Operation: %s\n", (ntohs(arpheader->oper) == ARP_REPLY )? "ARP Request": "ARP Reply");
		
		if (ntohs(arpheader->hardType) == 1 && ntohs(arpheader->protocolType) == 0x0800){
			printf ("Send MAX:");
			
			for (i = 0; i < 6; i++){
				printf ("%02x:", arpheader->sendHardAdr[i]);
			}

			printf ("\nSend IP:");

			for (i = 0; i < 4; i++){
				printf ("%d.", arpheader->sendIPAdr);
			}

			printf ("");
		}
	}



	return EXIT_SUCCESS;
}

