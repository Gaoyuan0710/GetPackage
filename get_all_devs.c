/*
 * =====================================================================================
 *
 *       Filename:  get_all_devs.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年09月25日 21时00分56秒
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
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	pcap_if_t *alldevs;
	pcap_if_t *device;
	char errbuf[PCAP_ERRBUF_SIZE];

	if(pcap_findalldevs(&alldevs, errbuf) == -1)
	{
		fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
		exit(EXIT_FAILURE);
	}

	device = alldevs;
	for(; device != NULL; device = device->next)
	{
		printf("Device name: %s\n", device->name);
		printf("Description: %s\n", device->description);
	}

	pcap_freealldevs(alldevs);

	return 0;
}
