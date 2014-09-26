/*
 * =====================================================================================
 *
 *       Filename:  simplesniffer.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年09月26日 13时10分03秒
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
#include <ctype.h>

#define MAXBYTES2CAPTURE 2048

void processPacket(u_char *arg, const struct pcap_pkthdr *pkthdr, 	  
			const u_char *packet)
{
	int i = 0, *counter = (int *)arg;

	printf ("Packet number :%d\n", ++(*counter));
	printf ("Received Packet Size : %d\n", pkthdr->len);
	printf ("Payload:\n");
	
	for (i = 0, i < pkthdr->len; i++)
	{
		if (isprint(packet[i]))
		{
			printf ("%c", packet[i]);
		}
		else
		{
			printf (".");
		}

		if ((i % 6 == 0  && i != 0) || i == pkthdr->len - 1)
		{
			printf ("\n");
		}
	}

	return ;
}

int main(int argc, char *argv[])
{
	int i = 0, count = 0;
	char errbuf[PCAP_ERR]



	return EXIT_SUCCESS;
}

