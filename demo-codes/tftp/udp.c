#include "skbuff.h"
#include "eth.h"
#include "ip.h"
#include "udp.h"
#include "tftp.h"
#include "utils.h"

int udp_init(void)
{
	return 0;
}

int udp_rcv_packet(struct sk_buff *skb)
{
	struct udphdr *udp_hdr = (struct udphdr *)(skb->data);

	skb->len = ntohs(udp_hdr->len);
	skb_pull(skb, sizeof(struct udphdr));

	if (ntohs(udp_hdr->dest) == TFTP)
		tftp_rcv_packet(skb);

	return 0;
}

int udp_send(struct sk_buff *skb, unsigned long ip,
	unsigned short source, unsigned short dest)
{
	struct udphdr *udp_hdr;

	udp_hdr = (struct udphdr *)skb_push(skb, sizeof(struct udphdr));
	udp_hdr->source = htons(source);
	udp_hdr->dest = htons(dest);
	udp_hdr->len = htons(12);
	udp_hdr->check = 0;

	ip_send(skb, ip, UDP);

	return 0;
}

void udp_skb_reserve(struct sk_buff *skb)
{
	ip_skb_reserve(skb);
	skb_reserve(skb, sizeof(struct udphdr));
}

unsigned short udp_get_source_port(struct sk_buff *skb)
{
	struct udphdr *udp_hdr;
	
	udp_hdr = (struct udphdr *)(skb->buf + ETH_HLEN + sizeof(struct iphdr));
	return ntohs(udp_hdr->source);
}
