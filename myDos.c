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

void myAttack(void skfd, struct sockaddr_in target, unsigned short srcpor);
unsigned short checkSum(unsigned short *addr, int len);

int main(int argc, char *argv[])
{
	int skfd;
	struct sockaddr_in target;



	return EXIT_SUCCESS;
}

