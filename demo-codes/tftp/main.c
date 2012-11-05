#include "types.h"
#include "bios.h"
#include "skbuff.h"
#include "eth.h"
#include "arp.h"
#include "ip.h"
#include "udp.h"
#include "console.h"
#include "utils.h"

int DownLoadEnd;
int DownLoadOnly;
unsigned long LoadLength;	
unsigned long load_addr = 0x8000;

int net_handle(void)
{
	struct sk_buff *skb;
	struct ethhdr *eth_hdr;

	skb = alloc_skb(ETH_FRAME_LEN);

	if (eth_rcv(skb) != -1) {

		eth_hdr = (struct ethhdr *)(skb->data);
		skb_pull(skb, ETH_HLEN);

		if (ntohs(eth_hdr->h_proto) == ETH_P_ARP)
			arp_rcv_packet(skb);

		else if(ntohs(eth_hdr->h_proto) == ETH_P_IP)
		 	ip_rcv_packet(skb);
	}

	free_skb(skb);

	return 0;
}

int tftp_main(unsigned long ip, unsigned long addr, int method)
{
	unsigned char eth_addr[ETH_ALEN];
	unsigned char *s = (unsigned char *)&ip;

//	console_init();
	printf("Mini TFTP Server 1.0 (IP : %d.%d.%d.%d PORT: %d)\n", s[3], s[2], s[1], s[0], TFTP);

	load_addr = addr;	
	DownLoadEnd = 0;
	DownLoadOnly = method;
	LoadLength = 0;
	
	puts("Load image file from host\n");
	printf("Type tftp -i %d.%d.%d.%d put filename at the host PC\n", s[3], s[2], s[1], s[0]);
	puts("Press ESC key to exit\n");	

	eth_init();
	eth_get_addr(eth_addr);
	arp_init();
	ip_init(ip);	
	udp_init();

	arp_add_entry(eth_addr, ip);	

	while (1) {

		net_handle();		
		if (kbhit()&&(getch()==KEY_ESC))
		{
			putch('\n');
			return 0;
		}
		if(DownLoadEnd)
			return LoadLength;
	}	
}

int	pIrqStart = 0;
int	pIrqFinish = 0;
int	pIrqHandler	= 0;