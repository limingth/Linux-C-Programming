#include "types.h"
#include "skbuff.h"
#include "eth.h"
#include "arp.h"
#include "utils.h"

#define ARP_CACHE_SIZE   16

typedef struct arp_entry {
	unsigned char ar_ha[ETH_ALEN];
	unsigned long ar_ip;
} arp_entry;

static arp_entry arp_entrys;
static arp_entry arp_cache[ARP_CACHE_SIZE];
static int arp_chche_cur = 0;

int arp_init(void)
{
	memset(&arp_entrys, 0, sizeof(arp_entry));
	memset(arp_cache, 0, sizeof(arp_entry) * ARP_CACHE_SIZE);

	return 0;
}

int arp_add_entry(unsigned char *ha, unsigned long ip)
{
	memcpy(arp_entrys.ar_ha, ha, ETH_ALEN);
	arp_entrys.ar_ip = htonl(ip);

	return 0;
}

int arp_add_cache(unsigned char *ha, unsigned long ip)
{
	int i;

	for (i = 0; i < ARP_CACHE_SIZE; i++) {
		if (ip == arp_cache[i].ar_ip)
			break;
	}

	if (i == ARP_CACHE_SIZE) {
		i = arp_chche_cur;
		arp_chche_cur = (arp_chche_cur + 1) % ARP_CACHE_SIZE;
	}

	memcpy(arp_cache[i].ar_ha, ha, ETH_ALEN);
	arp_cache[i].ar_ip = ip;

	return 0;
}

int arp_send_req(unsigned long ip)
{
	struct sk_buff *skb;
	struct arphdr *arp_req;	
	unsigned char broadcast[ETH_ALEN] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};	

	skb = alloc_skb(ETH_HLEN + sizeof(struct arphdr));
	eth_skb_reserve(skb);
	arp_req = (struct arphdr *)skb_put(skb, sizeof(struct arphdr));

	arp_req->ar_hrd = htons(ARPHRD_ETHER);
	arp_req->ar_pro = htons(ETH_P_IP);
	arp_req->ar_hln = 0x06;
	arp_req->ar_pln = 0x04;
	arp_req->ar_op = htons(ARPOP_REQUEST);	
	memcpy((unsigned char *)arp_req->ar_sha, arp_entrys.ar_ha, ETH_ALEN);
	arp_req->ar_sip = arp_entrys.ar_ip;	
	memset((unsigned char *)arp_req->ar_tha, 0x00, ETH_ALEN);
	arp_req->ar_tip = htonl(ip);

	eth_send(skb, broadcast, ETH_P_ARP);

	return 0;
}

int arp_send_rsp(struct arphdr *arp_hdr)
{
	struct sk_buff *skb;
	struct arphdr *arp_rsp;	
	
	skb = alloc_skb(ETH_HLEN + sizeof(struct arphdr));
	eth_skb_reserve(skb);
	arp_rsp = (struct arphdr *)skb_put(skb, sizeof(struct arphdr));

	arp_rsp->ar_hrd = htons(ARPHRD_ETHER);
	arp_rsp->ar_pro = htons(ETH_P_IP);
	arp_rsp->ar_hln = 0x06;
	arp_rsp->ar_pln = 0x04;
	arp_rsp->ar_op = htons(ARPOP_REPLY);
	memcpy((unsigned char *)arp_rsp->ar_sha, arp_entrys.ar_ha, ETH_ALEN);
	arp_rsp->ar_sip = arp_hdr->ar_tip;
	memcpy((unsigned char *)arp_rsp->ar_tha, (unsigned char *)arp_hdr->ar_sha, ETH_ALEN);
	arp_rsp->ar_tip = arp_hdr->ar_sip;

	eth_send(skb, arp_hdr->ar_sha, ETH_P_ARP);

	return 0;
}

int arp_get_eth_addr(unsigned long ip, unsigned char *ha)
{
	int i;

	for (i = 0; i < ARP_CACHE_SIZE; i++) {
		if (htonl(ip) == arp_cache[i].ar_ip) {
			memcpy(ha, arp_cache[i].ar_ha, ETH_ALEN);
			break;
		}
	}

	if (i == ARP_CACHE_SIZE) {
		arp_send_req(ip);
		return -1;
	}

	return 0;
}

int arp_rcv_packet(struct sk_buff *skb)
{
	struct arphdr *arp_hdr = (struct arphdr *)(skb->data);

	if (arp_hdr->ar_tip != arp_entrys.ar_ip)
		return 0;

	if (arp_hdr->ar_op == htons(ARPOP_REQUEST))
		arp_send_rsp(arp_hdr);
	arp_add_cache(arp_hdr->ar_sha, arp_hdr->ar_sip);

	return 0;
}
