#include "types.h"
#include "skbuff.h"
#include "eth.h"
#include "mac.h"
#include "utils.h"

int eth_init(void)
{
	return s3c4510_eth_init();
}

int eth_send(struct sk_buff *skb, unsigned char *dest_addr, unsigned short proto)
{
	struct ethhdr *eth_hdr;
	unsigned char local_eth_addr[ETH_ALEN];

	eth_get_addr(local_eth_addr);

	eth_hdr = (struct ethhdr *)skb_push(skb, ETH_HLEN);

	memcpy((unsigned char *)eth_hdr->h_dest, dest_addr, ETH_ALEN);
	memcpy((unsigned char *)eth_hdr->h_source, local_eth_addr, ETH_ALEN);
	eth_hdr->h_proto = htons(proto);

	return s3c4510_eth_send(skb->data, skb->len);
}

int eth_rcv(struct sk_buff *skb)
{
	return s3c4510_eth_rcv(skb->data, &skb->len);
}

int eth_get_addr(unsigned char *addr)
{
	return s3c4510_eth_get_addr(addr);
}

void eth_skb_reserve(struct sk_buff *skb)
{
	skb_reserve(skb, ETH_HLEN);
}
