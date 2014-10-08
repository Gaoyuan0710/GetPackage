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
	int i, sffd, n;
	char buf[E]

	return EXIT_SUCCESS;
}

