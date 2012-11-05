#include "skbuff.h"
#include "eth.h"
#include "ip.h"
#include "arp.h"
#include "icmp.h"
#include "udp.h"
#include "utils.h"

static unsigned long local_ip = 0;

unsigned short ip_fast_csum(unsigned char * iph, unsigned int ihl)
{
	unsigned int sum, tmp1;
	
	// ip_fast_csum
	__asm {						
	ldr	sum, [iph], #4		
	ldr	tmp1, [iph], #4
	sub	ihl, ihl, #5
	adds	sum, sum, tmp1
	ldr	tmp1, [iph], #4
	adcs	sum, sum, tmp1
	ldr	tmp1, [iph], #4
	adcs	sum, sum, tmp1
l:	ldr	tmp1, [iph], #4
	adcs	sum, sum, tmp1
	tst	ihl, #15
	subne	ihl, ihl, #1
	bne	l
	adc	sum, sum, #0
	adds	sum, sum, sum, lsl #16
	addcs	sum, sum, #0x10000
	mvn	sum, sum
	mov	sum, sum, lsr #16	
	};
	
	return sum;
} 

int ip_init(unsigned long ip)
{
	local_ip = ip;
	return 0;
}

int ip_rcv_packet(struct sk_buff *skb)
{
	struct iphdr *ip_hdr = (struct iphdr *)(skb->data);

	if (ntohl(ip_hdr->daddr) == local_ip)
	{
		skb->len = ntohs(ip_hdr->tot_len);
		skb_pull(skb, sizeof(struct iphdr));

		if (ip_hdr->protocol == UDP)
			udp_rcv_packet(skb);
		if(ip_hdr->protocol == ICMP)
			icmp_rcv_packet(skb);			
	}

	return 0;
}

int ip_send(struct sk_buff *skb, unsigned long ip, unsigned char proto)
{
	struct iphdr *ip_hdr;
	static unsigned short ip_id = 32;	
	unsigned char dest_eth_addr[ETH_ALEN];	

	if (arp_get_eth_addr(ip, dest_eth_addr))
		return -1;

	ip_hdr = (struct iphdr *)skb_push(skb, sizeof(struct iphdr));

	ip_hdr->ihl = 5;
	ip_hdr->version = 4;
	ip_hdr->tos = 0;
//	ip_hdr->tot_len = htons(32);
		ip_hdr->tot_len = htons(skb->len);	
	ip_hdr->id = htons(ip_id++);
	ip_hdr->frag_off = 0;
	ip_hdr->ttl = 20;
	ip_hdr->protocol = proto;
	ip_hdr->check = 0;
	ip_hdr->saddr = htonl(local_ip);
	ip_hdr->daddr = htonl(ip);	
	ip_hdr->check = ip_fast_csum((unsigned char *)ip_hdr,ip_hdr->ihl);

	eth_send(skb, dest_eth_addr, ETH_P_IP);

	return 0;
}

void ip_skb_reserve(struct sk_buff *skb)
{
	eth_skb_reserve(skb);
	skb_reserve(skb, sizeof(struct iphdr));
}

unsigned long ip_get_source_ip(struct sk_buff *skb)
{
	struct iphdr *ip_hdr;
	
	ip_hdr = (struct iphdr *)(skb->buf + ETH_HLEN);
	return ntohl(ip_hdr->saddr);
}
