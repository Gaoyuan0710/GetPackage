/*
 * =====================================================================================
 *
 *       Filename:  tcpsyndos.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年09月26日 20时21分13秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gaoyuan, sishuiliunian0710@gmail.com
 *        Company:  Class 1204 of Computer Science and Technology
 *
 * =====================================================================================
 */

#ifdef __USER_BSD
#include <netinet/ip.h>
#define __FAVOR_BSD

#include <netinet/tcp.h>
#include <pcap.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define TCPSYNLEN 20
#define MAXBYTES2CAPTURE 2048

typedef struct pseudoheader{
	uint32_t src;
	uint32_t dst;
	u_char zero;
	u_char protocol;
	uint16_t tcplen;
}tcp_phdr_t;

typedef unsigned short u_int16;
typedef unsigned long  u_int32;

int 
int main(int argc, char *argv[])
{


	return EXIT_SUCCESS;
}

