#ifndef __UDP_H
#define __UDP_H

#define TFTP 0x45

/*
 *	This structure defines an udp header.
 */

__packed struct udphdr {
	unsigned short	source;
	unsigned short	dest;
	unsigned short	len;
	unsigned short	check;
};//__attribute__ ((packed));

int udp_init(void);
int udp_rcv_packet(struct sk_buff *skb);
int udp_send(struct sk_buff *skb, unsigned long ip,
	unsigned short source, unsigned short dest);
void udp_skb_reserve(struct sk_buff *skb);
unsigned short udp_get_source_port(struct sk_buff *skb);

#endif /* __UDP_H */
