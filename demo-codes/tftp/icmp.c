#include "utils.h"
#include "console.h"
#include "eth.h"
#include "skbuff.h"
#include "ip.h"
#include "icmp.h"

static unsigned long client_ip;

static int icmp_send_echo(struct sk_buff *skb)
{
	struct icmphdr *icmp_hdr, *icmp_echo;	
	unsigned int tmp, sum, i, cnt;		
			
	cnt = skb->len;
	if(cnt%2)
		cnt++;
				
	icmp_hdr = (struct icmphdr *)(skb->data);
	skb = alloc_skb(ETH_FRAME_LEN);
	ip_skb_reserve(skb);		//reserve for eth and ip stack	
	icmp_echo = (struct icmphdr *)skb_put(skb, cnt);	
	
	icmp_echo->type = 0;
	icmp_echo->code = 0;
	sum = 0;			
	for(i=1; i<cnt/2+1; i++)
	{	
		tmp = *((unsigned short *)(&icmp_hdr->check)+i);
		*((unsigned short *)(&icmp_echo->check)+i) = tmp;
		sum += tmp;		
	}
	i = sum>>16;
	icmp_echo->check = 0xffffu-(sum&0xffff)-i;	
	
	ip_send(skb, client_ip, ICMP);

	return 0;
}

static int icmp_rcv_echo(struct sk_buff *skb)
{
	client_ip = ip_get_source_ip(skb);
		
	icmp_send_echo(skb);
	
	return 0;
}

int icmp_rcv_packet(struct sk_buff *skb)
{
	struct icmphdr *icmp_hdr = (struct icmphdr *)(skb->data);
	
	switch(icmp_hdr->type)
	{
		case 8:
		icmp_rcv_echo(skb);
	}
	
	return 0;
}