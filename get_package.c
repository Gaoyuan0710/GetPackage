/*
 * =====================================================================================
 *
 *       Filename:  get_package.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年09月25日 11时15分16秒
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
#include <time.h>

#define PACK_SIZE 1280

int main(int argc, char *argv[])
{
	char errbuf[PCAP_ERRBUF_SIZE], *devStr;
	struct pcap_pkthdr packet;
	const u_char *ptkStr;
	pcap_t *device;

	devStr = pcap_lookupdev(errbuf);

	if (devStr)
	{
		printf ("Success : device is %s\n", devStr);
	}
	else
	{
		printf ("error : %s\n", errbuf);

		exit(-1);
	}

	device = pcap_open_live(devStr, PACK_SIZE, 1, 0, errbuf);

	if (!device)
	{
		printf ("pcap_open_live error: %s\n", errbuf);

		exit(-2);
	}

	ptkStr = pcap_next(device, &packet);

	if (! ptkStr)
	{
		printf ("Don't get any packets\n");

		exit (-3);
	}

	printf ("Packet length :%d\n", packet.len);
	printf ("Numbers of bytes : %d\n", packet.caplen);
	printf ("Recv time : %s\n", ctime((const time_t *) &packet.ts.tv_sec));


	pcap_close(device);

	return EXIT_SUCCESS;
}

