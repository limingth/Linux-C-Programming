#ifndef __ICMP_H
#define	__ICMP_H

#include "skbuff.h"
#include "ip.h"

__packed struct icmphdr
{
	unsigned char type;
	unsigned char code;
	unsigned short check;
};

int icmp_rcv_packet(struct sk_buff *skb);

#endif