/*
 * =====================================================================================
 *
 *       Filename:  my_ping.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年10月10日 20时51分47秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gaoyuan, sishuiliunian0710@gmail.com
 *        Company:  Class 1204 of Computer Science and Technology
 *
 * =====================================================================================
 */

#ifndef MY_PING_H_
#define MY_PING_H_
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/ip_icmp.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <pthread.h>

struct sockaddr_in dst_addr;
struct sockaddr_in recv_addr;
struct timeval tvrecv;
char icmp_pkt[1024] = {0};
char recv_pkt[1024] = {0};
int sockfd = 0, bytes = 56, nsend_pkt = 0, nrecv_pkt = 0;
pid_t pid;

void statistice();
void *send_ping();
void *recv_ping();
void tv_sub(struct timeval *out, struct timeval *in);
int pack(int send_pkt);
int unpack(char *recv_pkt, int size);
int in_chksum(unsigned short *buf, int size);

#endif
