#ifndef __IP_H
#define __IP_H

#define UDP		0x11
#define	ICMP	0x01


/*
 *	This structure defines an ip header.
 */

__packed struct iphdr {

	unsigned ihl:4,
			 version:4;
	unsigned char	tos;
	unsigned short	tot_len;
	unsigned short	id;
	unsigned short	frag_off;
	unsigned char	ttl;
	unsigned char	protocol;
	unsigned short	check;
	unsigned long	saddr;
	unsigned long	daddr;
	/*The options start here. */
};//__attribute__ ((packed));

int ip_init(unsigned long ip);
int ip_rcv_packet(struct sk_buff *skb);
int ip_send(struct sk_buff *skb, unsigned long ip, unsigned char proto);
void ip_skb_reserve(struct sk_buff *skb);
unsigned long ip_get_source_ip(struct sk_buff *skb);

#endif /* __IP_H */
